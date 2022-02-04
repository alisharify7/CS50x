#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,string argv[])
{
    // For get 2 argument from User one For Run program and one for key
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // with for loop goo to each element of argv and see is alpha or number
    int len_argc = strlen(argv[1]);
    {
        for (int i = 0 ; i < len_argc ; i++)
        {
              char tmp = argv[1][i];
              if(isalpha(tmp))
              {
                 printf("Usage: ./caesar key\n");
                 return 1;
              }
        }
    }
    // convert char to int
    int key = atoi(argv[1]);

    if (key == 0)
    {
        printf("Usage: ./caesar key\n");
        return 2;
    }

    // get input from user for ciphering
    string plain_text = get_string("Plain text: ");

    //Final print
    printf("ciphertext: ");
    for (int i = 0,len = strlen(plain_text); i < len; i++)
    {
        char tmp = plain_text[i];
        if (isalpha(tmp))
        {
            // check for alphabet
            if(isupper(tmp))
            {
                printf("%c", (((tmp - 65) + key) % 26 )+ 65);
            }
            // if is not upper definitely it's lower
            else
            {
                printf("%c", (((tmp - 97) + key) % 26 )+ 97);
            }
        }
        else
        {
            printf("%c",tmp);
        }

    }
    printf("\n");


}