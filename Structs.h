#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct user
{
    char* username;
    char* password;
    double balance;

    struct user *next;
} user;

typedef struct horse
{
    char name;
    int winChance;
    double amountBet;
    int distance;
} horse;