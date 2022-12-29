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
double bet(double balance, horse horses[5]);

int main(){
    double balance;
    char* username = (char*)malloc(MAX);
    user* users = NULL;
    char exit = '0';

    //WHEN PROGRAM IS OPENED
    readFile(&users, "users.crp");
    //readFile(&users, "usersDev.txt");
    system("cls");

    //Creating horses
    horse horses[H_NUM];
    makeHorses(horses);
    //printHorses(horses);

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
                if(scanf(" %c", &exit)){
                    if (exit == 'e') {
                        system("cls");
                        break;
                    }
                }
                printf("Sorry that is not a valid selection, please try again.\n\n");
                while ((getchar()) != '\n');
            }
        }

        // testing for quit before anything else so we can stop right away
        if (selection == 4 || exit == 'e'){
            while(1){
                while ((getchar()) != '\n');
                puts("Are you sure you want to exit? Y/N");
                if(scanf(" %c", &exit)){
                    if (exit == 'e' || exit == 'Y'  || exit == 'y') {
                        system("cls");
                        logout(&users, &username, balance);
                        return 0;
                    }
                    if(exit == 'N' || exit == 'n')break;
                }
                printf("Sorry, that is not a valid response, pleast try again\n");
            }
        }

        //chooses which selection to run. If the input is not a valid selection, default will run and restart the 
        //  selection process
        switch (selection)
        {
        case (1): // Add funds to account
            balance = addFunds(balance);
            break;
        case (2): // Bet on horses
            balance = bet(balance, horses);
            break;
        case (3): // Watch Race
            
            break;
        default:
            printf("Sorry that is not a valid selection, please try again.\n\n");
        }
    }

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
    char exit;
    system("cls");

    printf("Current balance is %.2f\n", oldBalance);
    puts("How much would you like to add?");
    while(1){
        while ((getchar()) != '\n');
        if(scanf(" %lf", &change))break;
        if(scanf(" %c", &exit)){
            if (exit == 'e') {
                system("cls");
                return oldBalance;
            }
        }
        printf("Sorry, that is not a valid amount, pleast try again\n");
    }

    newBalance = oldBalance + change;
    system("cls");
    printf("Your new balance is %.2f", newBalance);

    return newBalance;
}

double bet(double balance, horse horses[5]){
    while(1){
    char bet = '0', exit = '0';
    double amountBet = 0;
    int h = 0;
    system("cls");
    printf("Current balance: $%.2f\n", balance);
    puts("Horses running in the next race:");
    printHorses(horses);
    puts("Which horse would you like to bet on?");
    while(1){
        while ((getchar()) != '\n');
        if(scanf(" %c", &bet)){
            if (bet == 'e') {
                system("cls");
                return balance;
            }
            for(int i=0; i<H_NUM;i++){
                if(bet == horses[i].name){
                    h = i;
                    break;
                }
            }
        }
        if(h != 0)break;
        printf("Sorry, that is not a valid horse, please try again\n");
    }
    puts("How much would you like to bet?");
    while(1){
        while ((getchar()) != '\n');
        if(scanf(" %lf", &amountBet)){
            if(amountBet <=balance){
                balance -= amountBet;
                horses[h].amountBet += amountBet;
                system("cls");
                printf("$%.2f bet on horse %c.", amountBet, bet);
                break;
            }
            puts("Insufficient funds in account, please try again.");
            continue;
        }
        if(scanf(" %c", &exit)){
            if (exit == 'e') {
                system("cls");
                break;
            }
        }
        puts("Sorry, that is not a valid amount, please try again.");
    }
    //(exit) variable is reversed from assumed here because of wording of command.
    while(1){
        puts("Do you want to bet on another horse? Y/N");
        while ((getchar()) != '\n');
        if(scanf(" %c", &exit)){
            if (exit == 'e' || exit == 'N' || exit == 'n') {
                system("cls");
                return balance;
            }
            if(exit == 'Y' || exit == 'y')break;
        }
        printf("Sorry, that is not a valid response, please try again\n");
    }
    }
}