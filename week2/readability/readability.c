#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


    // created by : alisharify
    //Do not copy code 
    
int main(void)
{
    // Get input From User
    int letter = 0;
    // CALCULATING " " to get number of the word
    int word = 1;
    // calculating "! ? ." to get number of the sentences
    int sentences = 0;

    // GET input from user
    string in_user = get_string("Text: ");
    int n = strlen(in_user);

    int counter = 0;
    while (counter < n)
    {
        //check is alohabet or NOT!
        if (isalpha(in_user[counter]))
        {
            letter++;
        }
        //CHECK FOR sentences
        else if (in_user[counter] == '.' || in_user[counter] == '!' || in_user[counter] == '?')
        {
            sentences++;
        }
        //check for word
        else if (in_user[counter] == ' ')
        {
            word++;
        }
        counter++;
    }

    //calculating with coleman liau formola
    float L = (letter / (float) word) * 100;
    float S = ((float)sentences / word) * 100;
    
    //index finaly grade
    int index = round(0.0588 * L - 0.296 * S - 15.8);


    //print winner 
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
