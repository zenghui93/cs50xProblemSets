#include <stdio.h>
#include <cs50.h>
int main(void)
{
    // It promts the user for their name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}