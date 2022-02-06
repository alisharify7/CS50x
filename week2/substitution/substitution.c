#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

    // created by : alisharify
    //Do not copy code 
    
int main(int argc, string argv[])
{
    // this is for check location of user input
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    // this array for get and added user key input to this array
    char key[26];

    // check argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int counter = 0;
    int len_key = strlen(argv[1]);

    // check length of key equal to 26
    if (len_key != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check all of 26 char is alphabet and not dublicate
    else if (len_key == 26)
    {
        // tmpp char is for check one step by one step key and looking for duplicate
        char tmpp = 'a';
        // for check each house of key and see if not alphabet or it has
        for (int i = 0 ; i < len_key; i++)
        {
            if (tmpp == argv[1][i])
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            if (isalpha(argv[1][i]))
            {
                counter++;
                key[i] = argv[1][i];
                tmpp = argv[1][i];
            }
            else
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }
    
    // get input from user
    string user = get_string("PlainText: ");
    printf("ciphertext: ");

    // Got to Each of char of user string
    for (int i = 0, n = strlen(user); i < n; i++)
    {
        char tmp = user[i];
        if (isupper(tmp))
        {
            for (int a = 0 ; a < 26 ; a++)
            {
                if (tmp == alphabet[a])
                {
                    printf("%c", toupper(key[a]));
                }
            }
        }
        // in here check for lowercase
        else if (islower(tmp))
        {
            for (int s = 0 ; s < 26 ; s++)
            {
                if (toupper(tmp) == alphabet[s])
                {
                    printf("%c", tolower(key[s]));
                }
            }
        }
        // if user[i] is not alphabet so we just print it
        else
        {
            printf("%c", user[i]);
        }
    }
    //print for newline
    printf("\n");
}