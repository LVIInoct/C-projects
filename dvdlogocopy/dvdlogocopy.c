/* The plan is to get a rgb ascii art of my username AND make it bounce
off the terminal edges like a DVD screen. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> // to get the console dimensions
#include <unistd.h> // for stdout and STDOUT_FILENO

typedef struct { // struct to hold the Logo's properties and the ascii art itself
    char *art[4]; // the ascii art Logo is 4 lines long, so we can store it in an array of 4 strings
    int x, y;
    int dx, dy; // dx and dy are a variation for movement
} Logo;


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
    int Logo_w = 20; // The character count of the widest line
    int Logo_h = 4;  // The number of lines
    int x, y = 0; // Initial Logo of the logo (we will update this later to start in the middle of the terminal)

    int r = 255, g = 0, b = 0; // starting rgb color (red)
    int phase = 0; // smooth color transition phase (0-5 for R->Y->G->C->B->M->R)
    int speed = 15; // how fast the color changes (higher is faster, max 255 for smoothness)

    x = (w.ws_col - Logo_w) / 2; // Start in the middle of the terminal
    y = (w.ws_row - Logo_h) / 2;
    
    printf("\033[H\033[J"); // Clear the terminal screen and move the cursor to the top-left corner

    Logo noct; // creating our single entity to hold the Logo and its properties
    noct.x = x;  // Logo position and movement
    noct.y = y;
    noct.dx = 1; // Set horizontal speed
    noct.dy = 1; // Set vertical speed

    for(int i = 0; i < 4; i++) {
    noct.art[i] = noct_art[i]; // Copy the ASCII art lines into the Logo struct
}
    // main loop to keep the logo bouncing on the edges of the console and changing colors
    while (1){
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // rewriting dimensions of terminal for resizing support
        // here, we use a movement formula: new Logo = old Logo + speed (dx or dy). 
        noct.x += noct.dx; // move horizontally
        noct.y += noct.dy; // move vertically
        if (noct.x <= 1 || noct.x + 20 >= w.ws_col) noct.dx *= -1;
        if (noct.y <= 1 || noct.y + 4 >= w.ws_row) noct.dy *= -1;

        //rgb and avoiding black/white colors + smooth transitions (i know this is a mess but it works and i dont care)
        switch (phase) {
            case 0: g += speed; if (g >= 255) { g = 255; phase = 1; } break; // R->Y
            case 1: r -= speed; if (r <= 0)   { r = 0;   phase = 2; } break; // Y->G
            case 2: b += speed; if (b >= 255) { b = 255; phase = 3; } break; // G->C
            case 3: g -= speed; if (g <= 0)   { g = 0;   phase = 4; } break; // C->B
            case 4: r += speed; if (r >= 255) { r = 255; phase = 5; } break; // B->M
            case 5: b -= speed; if (b <= 0)   { b = 0;   phase = 0; } break; // M->R
        }

        // printing the art by going through each line
        for (int i = 0; i < 4; i++) {
            printf("\033[%d;%dH\033[38;2;%d;%d;%dm%s\033[0m", // I never saw this many specifiers in one line before oh god
                        noct.y + i, noct.x, r, g, b, noct.art[i]); // prints rgb version
        }

        fflush(stdout); // Ensure the output is printed immediately
        usleep(100000); // Sleep for a short time to control the update rate (e.g., 100ms)
        /* printf("\e[1;1H\e[2J");  Clear the screen for the next frame (move cursor to top-left and clear the screen [Optional]).*/
    }

    return 0;
}
