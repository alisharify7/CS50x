#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string answer = get_string("whats your name? ");
    printf("hello ,%s\n", answer);

}