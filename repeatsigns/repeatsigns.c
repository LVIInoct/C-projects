#include <stdio.h>
#include <ctype.h> // needed for lowercase input
#include <string.h> // import string library for strcmp function
/* also you use & when you need the address of the variable (like when editing it)
like using scanf since it always needs to give the address of the variable a place to be
set in the RAM (otherwise it would be sort of read-only) 

only use & with int, float, char, but NEVER with printf or arrays

It's also good practice to use getchar(); after using scanf for "cleanup"

*/

int main(void){

    while(1){
        // declaring variables
        int a;
        char input[100]; // by the way, the numbers in [ ] are the limits of the string
        char answer[3];
        // input
        printf("Program to repeat input\nInput: ");
        scanf("%99s", &input);
        getchar();
        printf("How many times to repeat it?: ");
        scanf("%2d", &a);
        getchar();
        /* by adding string limits before the variable name in scanf we stop user from typing more than 100 and 3 digits*/

        // output
        printf("This is the output: \n");
        for (int i = 0; i < a; i++) { 
            printf("%s", input); // print the input a number of imes
        }

        // leaving
        printf("\nDo you wish to leave? (Y/n): ");
        scanf("%2s", answer); // take answer
        getchar();
        /* by using answer[0], we check the position and get the first letter.
        then, we change it to lowercase so capitalizations dont matter, and then
        check if it starts with Y (yes) */
        answer[0] = tolower(answer[0]); // conversion
        if (answer[0] == 'y')
            break; // end program
    }
    return 0;
}
