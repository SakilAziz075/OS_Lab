#include <stdio.h>

int main(int argc, char *argv[]) {
    // Print the program name and its arguments
    printf("Program Name: %s\n", argv[0]);

    printf("Arguments passed to the child process:\n");
    for (int i = 1; i < argc; i++) 
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0; // Exit status 0
}
