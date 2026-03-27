/* The plan is to get a rgb ascii art of my username AND make it bounce
off the terminal edges like a DVD screen. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> // to get the console dimensions
#include <unistd.h>    // for stdout and STDOUT_FILENO
#include <signal.h> // for sign handler

typedef struct { // struct to hold the Logo's properties and the ascii art itself
    char *art[4]; // the ascii art Logo is 4 lines long, so we can store it in an array of 4 strings
    int x, y;
    int dx, dy; // dx and dy are directions, not speeds
} Logo;
void handle_sigint(int sig);

int main() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); /* From now on, we can use w.ws_row and w.ws_col to get the
    number of rows and columns in the terminal, respectively. */

    char *noct_art[] = { // defining the ascii art for the logo
        "   _  __         __",
        "  / |/ /__  ____/ /_",
        " /    / _ \\/ __/ __/",
        "/_/|_/\\___/\\__/\\__/"
    };

    // declaring values
    int x = 0, y = 0; // initial position of the logo (updated below to center it)

    int r = 255, g = 0, b = 0; // starting rgb color (red)
    int phase = 0; // smooth color transition phase (0-5 for R->Y->G->C->B->M->R)
    int speed = 15; // how fast the color changes (higher is faster, max 255 for smoothness)

    x = (w.ws_col - 20) / 2; // start in the middle of the terminal
    y = (w.ws_row - 4) / 2;

    printf("\033[H\033[J"); // clear the terminal screen and move the cursor to the top-left corner

    Logo noct; // creating our single entity to hold the Logo and its properties
    noct.x = x;  // logo position and movement
    noct.y = y;
    noct.dx = 1, noct.dy = 1; // setting directions

    #define TRAIL 6 // defines the length of the trail (how many previous positions to show)
    // basically "every time you see TRAIL, replace it with 6 before compiling"

    int trail_x[TRAIL]; // array to hold the x positions of the trail, used for fading effect
    int trail_y[TRAIL];
    for (int i = 0; i < TRAIL; i++) { // initialize the trail positions to the starting position of the logo
        trail_x[i] = noct.x;
        trail_y[i] = noct.y;
    }

    for (int i = 0; i < 4; i++) {
        noct.art[i] = noct_art[i]; // copy the ASCII art lines into the Logo struct
    }

    // fadeout factors per trail step — never changes, so defined once outside the loop
    float fadeout[TRAIL] = {1.0, 0.6, 0.3, 0.15, 0.07, 0.03};
    signal(SIGINT, handle_sigint); // restore cursor on Ctrl+C

    printf("\033[?25l"); // hide the cursor

    // main loop to keep the logo bouncing on the edges of the console and changing colors
    while (1) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // re-fetch dimensions for terminal resize support

        // move the logo: new position = old position + direction
        noct.x += noct.dx;
        noct.y += noct.dy;
        if (noct.x <= 1 || noct.x + 20 >= w.ws_col) noct.dx *= -1; // bounce horizontally
        if (noct.y <= 1 || noct.y + 4  >= w.ws_row) noct.dy *= -1; // bounce vertically

        // erase oldest trail position
        int old_x = trail_x[TRAIL - 1];
        int old_y = trail_y[TRAIL - 1];
        for (int i = 0; i < 4; i++) {
            printf("\033[%d;%dH%*s", old_y + i, old_x, 20, " ");
        }

        // shift trail back one step
        for (int i = TRAIL - 1; i > 0; i--) {
            trail_x[i] = trail_x[i - 1];
            trail_y[i] = trail_y[i - 1];
        }

        // insert current position at the front
        trail_x[0] = noct.x;
        trail_y[0] = noct.y;

        // smooth rgb color transition: R->Y->G->C->B->M->R
        switch (phase) {
            case 0: g += speed; if (g >= 255) { g = 255; phase = 1; } break; // R->Y
            case 1: r -= speed; if (r <= 0)   { r = 0;   phase = 2; } break; // Y->G
            case 2: b += speed; if (b >= 255) { b = 255; phase = 3; } break; // G->C
            case 3: g -= speed; if (g <= 0)   { g = 0;   phase = 4; } break; // C->B
            case 4: r += speed; if (r >= 255) { r = 255; phase = 5; } break; // B->M
            case 5: b -= speed; if (b <= 0)   { b = 0;   phase = 0; } break; // M->R
        }

        // print trail from oldest to newest for proper layering (oldest = most faded, newest = brightest)
        for (int t = TRAIL - 1; t >= 0; t--) {
            int rr = r * fadeout[t];
            int gg = g * fadeout[t];
            int bb = b * fadeout[t];
            for (int i = 0; i < 4; i++) {
                printf("\033[%d;%dH\033[38;2;%d;%d;%dm%s\033[0m",
                    trail_y[t] + i,
                    trail_x[t],
                    rr, gg, bb,
                    noct.art[i]);
            }
        }

        fflush(stdout);    // ensure output is printed immediately
        usleep(100000);    // sleep 100ms to control update rate
    }

    return 0;
}
void handle_sigint(int sig) {
    printf("\033[?25h"); // restore cursor before exiting
    exit(0);
}
