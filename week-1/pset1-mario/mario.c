#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // created by : alisharify
    //Do not copy code 
    
    //with do while loop get input from user 
    // user most between 1 to 8
    int user = 0;
    do
    {
        user = get_int("enter height:");
    }
    while (user > 8 || user < 1);
    //printf("user is ---> %i\n", user);


    for (int i = 1 ; i <= user ; i++)
    {

        // for print space
        for (int j = user; j > i ; j--)
        {
            printf(" ");
        }
        // for print #
        for (int k = 0; k < i ; k++)
        {
            printf("#");
        }
        //for print new line
        printf("\n");
    }
}