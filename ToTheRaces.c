//Horse Betting Simulator
//Cole Burgi - [date]

#include "Crypto.h"
#include "Horses.h"
#include <conio.h>

#define MAX 40

double login(user** list, char** user);
int makeUser(user** list, char** user, char* pass);
void logout(user** list, char** username, double balance);
double addFunds(double oldBalance);

int main(){
    double balance;
    char* username = (char*)malloc(MAX);
    user* users = NULL;

    //WHEN PROGRAM IS OPENED
    readFile(&users, "users.crp");
    //readFile(&users, "usersDev.txt");
    system("cls");

    //Creating horses
    horse horses[H_NUM];
    makeHorses(horses);
    printHorses(horses);

    //printed for user
    puts(" ~*~*~*~*~*~*~ Welcome to the races! ~*~*~*~*~*~*~ ");
    puts("Press 'e' at any time to return to a previous menu.");
    balance = login(&users, &username);
    system("cls");
    printf("Welcome %s! Current balance: %.2f", decrypt(username), balance);

    int selection = 0;
    while (1)
    {

        //will run again if the input is not a valid int
        while (1)
        {
        printf("\n");
        printf("Please enter the number of the command you would like to run.\n");
        printf("1: Add funds to account\n");
        printf("2: Bet on horses.\n");
        printf("3: Watch race.\n");
        printf("4: Log out.\n");

            if (scanf(" %i", &selection))
            {
                break;
            }
            else
            {
                printf("Sorry that is not a valid selection, please try again.\n\n");
                while ((getchar()) != '\n');
            }
        }

        // testing for quit before anything else so we can stop right away
        if (selection == 4)
            break;

        //chooses which selection to run. If the input is not a valid selection, default will run and restart the 
        //  selection process
        switch (selection)
        {
        case (1): // Add funds to account
            balance = addFunds(balance);
            break;
        case (2): // Bet on horses
            
            break;
        case (3): // Watch Race
            
            break;
        default:
            printf("Sorry that is not a valid selection, please try again.\n\n");
        }
    }

    //WHEN PROGRAM IS CLOSED
    logout(&users, &username, balance);
    return 0;
}

double login(user** list, char** username){
    char* password = (char*)malloc(MAX);
    user* ptr = *list;

    while(1){
        puts("Enter username (or type new to make a new account)");
        scanf("%s", *username);
        if(!strcmp("new", *username)){
            if(!makeUser(list, username, password))continue;
            return 0.00;
        }else if(!strcmp("e", *username))exit (1);

        puts("Enter password");
        scanf("%s", password);

        *username = encrypt(*username);
        password = encrypt(password);

        int uFound = 0;
        while(ptr != NULL){
            if(!strcmp(*username, ptr->username)){
                uFound = 1;
                if(!strcmp(password, ptr->password)){
                    return ptr->balance;
                }
                puts("Incorrect password");
                break;
            }

            ptr = ptr->next;
        }
        system("cls");
        if(!uFound)puts("Sorry, username could not be found");
    }

    return 0;
}

int makeUser(user** list, char** username, char* pass){
    system("cls");
    user* ptr = *list;
    char* pass2 = (char*)malloc(MAX);

    while(1){
        puts("Enter new username");
        scanf("%s", *username);
        if(!strcmp("e", *username)){
            system("cls");
            return 0;
        }
        int uNique = 1;
        while(ptr != NULL){
            if(!strcmp(encrypt(*username), ptr->username)){
                system("cls");
                puts("Sorry, that username is taken");
                uNique = 0;
                break;
            }
            ptr = ptr->next;
        }
        if(uNique)break;
    }

    while(1){
        puts("Enter new password");
        scanf("%s", pass);
        if(!strcmp("e", pass)){
            system("cls");
            return 0;
        }
        puts("Re-enter new password");
        scanf("%s", pass2);
        if(!strcmp("e", pass2)){
            system("cls");
            return 0;
        }
        if(!strcmp(pass, pass2))break;
        system("cls");
        puts("Passwords do not match!");
    }

    addUser(list, newUser(encrypt(*username), encrypt(pass), 0.00));
    return 1;
}

void logout(user** list, char** username, double balance){
    user* ptr = *list;
    while(ptr != NULL){
            if(!strcmp(*username, ptr->username)){
                ptr->balance = balance;
                break;
            }

            ptr = ptr->next;
        }

    writeFile(list, "users.crp");
    //writeFile(users, "usersDev.txt");
    system("cls");
}

double addFunds(double oldBalance){
    double change, newBalance;

    puts("How much would you like to add?");
    while(1){
        if(scanf(" %lf", &change))break;
        printf("Sorry, that is not a valid amount, pleast try again\n");
        while ((getchar()) != '\n');
    }

    newBalance = oldBalance + change;
    printf("Your new balance is %.2f", newBalance);

    return newBalance;
}