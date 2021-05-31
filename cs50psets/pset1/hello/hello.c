#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /* prompts the user for their name */
    string name = get_string("What is your name: ");
    
    /* prints a greeting with the retrieved name */
    printf("hello, %s\n", name);
}