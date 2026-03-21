/* rushed code with few comments finished by Copilot AI and searches */
/* oh my god why did i think i had a backup code to keep up my github streak */
#include <stdio.h>
#include <stdlib.h> // for rand() and srand()
#include <time.h> // for time() to seed the random number generator
#include <unistd.h> // for usleep() to create a delay between color changes

int main() {
    srand(time(NULL)); // Randomizer

    while(1) { // wont stop playing until the user interrupts it (e.g., Ctrl+C)
        // generate random RGB values between 0 and 255 for each color component
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;

        // combining RGB values into a single hex value
        unsigned int hex = (r << 16) | (g << 8) | b;

        //\x1b[48;2;R;G;Bm sets the background color using RGB values, and \x1b[0m resets the formatting
        // this is confusing but i think i get it
        printf("\r\033[48;2;%d;%d;%dm  \033[0m  HEX: #%06X  ", r, g, b, hex);
        printf("\r\033[48;2;%d;%d;%dm  \033[0m \033[38;2;%d;%d;%dm HEX: #%06X \033[0m", r, g, b, r, g, b, hex); // sets the text color to the same as the background color for a cool effect
        
        fflush(stdout); // prints the output immediately without waiting for a newline
        usleep(1000000); // Wait 1000ms before generating a new color (1 second)
    }
    return 0;
}
