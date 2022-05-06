#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // created by : alisharify
    //Do not copy code 
    
    // for get input from user
    int user = 0;
    do
    {
        user = get_int("enter height:");
    }
    while (user > 8 || user < 1);
    //printf("user is ---> %i\n", user);



    for (int i = 1 ; i <= user ; i++)
    {

        // for print each space
        for (int j = user; j > i ; j--)
        {
            printf(" ");
        }
        // for print each #
        for (int k = 0; k < i ; k++)
        {
            printf("#");
        }
        //for print space between #
        printf("  ");
        for (int s= 0 ; s < i ; s++)
        {
            printf("#");
        }
        // for new line
        printf("\n");
    }
}