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