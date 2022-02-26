#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);


    // created by : alisharify
    //Do not copy code 
    
int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // TODO
    int user = 0;
    do
    {
        user = get_int("Enter input: ");
    }
    while (user < 0);
    return user;
    // this function is Done!
}

int calculate_quarters(int cents)
{
    // TODO
    int sum = 0;
    while (cents >= 25)
    {
        cents -= 25;
        sum++;
    }
    return sum;
    // this is Done too!
}

int calculate_dimes(int cents)
{
    // TODO
    int sum = 0;
    while (cents >= 10)
    {
        cents -= 10;
        sum++;
    }
    return sum;
}

int calculate_nickels(int cents)
{
    // TODO
    int sum = 0;
    while (cents >= 5)
    {
        cents -= 5;
        sum++;
    }
    return sum;
}

int calculate_pennies(int cents)
{
    // TODO
    int sum = 0;
    while (cents >= 1)
    {
        cents -= 1;
        sum++;
    }
    return sum;
}
