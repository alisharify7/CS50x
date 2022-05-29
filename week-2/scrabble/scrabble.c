#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


    // created by : alisharify
    //Do not copy code 


// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else
    {
        printf("Tie!\n");
        return 0;
    }

}

int compute_score(string word)
{
    int sum = 0;

    // TODO: Compute and return score for string
    // Iterate over all Word String
    for(int i = 0,len = strlen(word); i < len; i++)
    {   
        char temp = word[i];
        // check if temp is alphabetic  or Not
        if (isalpha(temp))
        {   
            // Convert temp to uppercase
            temp = toupper(temp);
            
            // find location of temp is points array
            int loc = 'A' - temp;
            
            // add points [loc] element to sum variable
            sum += POINTS[loc];
        }
    }
    // Return sum of word 
    return sum;
}


// another way  to Solve this Problem

//#include <ctype.h>
//#include <cs50.h>
//#include <stdio.h>
//#include <string.h>

    
// Points assigned to each letter of the alphabet
// int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
// char letter[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// int compute_score(string word);

// int main(void)
// {
//    // Get input words from both players
//    string word1 = get_string("Player 1: ");
//    string word2 = get_string("Player 2: ");

    // Score both words
//    int score1 = compute_score(word1);
//    int score2 = compute_score(word2);

    // TODO: Print the winner
//    if (score1 > score2)
//    {
//        printf("Player 1 Wins!\n");
//    }
//    else if (score1 < score2)
//    {
//        printf("Player 2 Wins!\n");
//    }
//    else
//    {
//        printf("Tie!\n");
//    }
//}

//int compute_score(string word)
//{
    // TODO: Compute and return score for string
//    int sum = 0;
//    int lenght = strlen(word);

    //with this for loop calculating 
    //points of word
//    for (int i = 0 ; i < lenght; i++)
//    {
//        for (int s = 0 ; s < 26; s++)
//        {
//            if (letter[s] == toupper(word[i]))
//            {
//                sum += POINTS[s];
//            }
//        }
//    }
//    return sum;
//}
