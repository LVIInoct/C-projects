// Casual switch implementation (rushed)
#include <stdio.h>

int main() {
    // declaring variables
    float celsius, fahrenheit;
    int choice;

    // menu
    printf("Temperature converter\nchoose a temperature unit to convert from:\n1) Celsius\n2) Fahrenheit\n> ");
    scanf("%d", &choice);

    // switch statement to determine which conversion to perform
    switch (choice)
    {
    case 1:
        printf("Enter temperature in celsius: ");
        scanf("%f", &celsius);
        fahrenheit = (celsius * 9 / 5) + 32;
        printf("result: %.2f\n", fahrenheit);
        break;
    case 2:
        printf("Enter temperature in fahrenheit: ");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - 32) * 5 / 9;
        printf("result: %.2f\n", celsius);
        break;
    
    default:
        printf("Invalid choice.\n");
        return 1;
    }
    return 0;
}
