//Horse Betting Simulator
//Cole Burgi - [date]

#include "Crypto.h"
#include "Horses.h"
#include <conio.h>
#include <math.h>

#define MAX 40
#define TRACK_LENGTH 80

double login(user** list, char** user);
int makeUser(user** list, char** user, char* pass);
void logout(user** list, char** username, double balance);
double addFunds(double oldBalance);
double bet(double balance, horse horses[5]);
double watch(horse horses[5]);

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

    int selection = 0;
    while (1)
    {
        printf("Welcome %s! Current balance: %.2f", decrypt(username), balance);

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
                printf("Sorry, that is not a valid response, please try again\n");
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
            balance += watch(horses);
            makeHorses(horses);
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
            system("cls");
        }
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
        printf("Sorry, that is not a valid amount, please try again\n");
    }

    newBalance = oldBalance + change;
    system("cls");
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
            for(int i=1; i<H_NUM;i++){
                if(bet == horses[i].name || bet-48 == i){
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
                printf("$%.2f bet on horse %c.\n", amountBet, bet);
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

double watch(horse horses[5]){
    char winner = '0';
    char exit; 
    int i, j, move = 0;
    double payout = 0.00;

    while(winner == '0'){
        system("cls");
        for (i = 1; i<H_NUM-1;i++) printf("$%.2f on %c(%i%%), ", horses[i].amountBet, horses[i].name, horses[i].winChance - horses[i-1].winChance);
        printf("$%.2f on %c(%i%%)\n", horses[H_NUM-1].amountBet, horses[H_NUM-1].name, horses[H_NUM-1].winChance - horses[H_NUM-2].winChance);

        for(i = 0;i<TRACK_LENGTH+4;i++)printf("=");
        puts("");
        for(i=1;i<H_NUM;i++){
            printf("|");
            if(horses[i].distance < TRACK_LENGTH){
                for(j=0;j<horses[i].distance;j++)printf(" ");
                printf("%c", horses[i].name);
                for(j=0;j<TRACK_LENGTH - horses[i].distance-1;j++)printf(" ");
                printf("| |\n");
            }else {
                for(j=0;j<TRACK_LENGTH;j++)printf(" ");
                printf("|%c|\n", horses[i].name);
                winner = horses[i].name;
            }
        }

        for(i = 0;i<TRACK_LENGTH+4;i++)printf("=");
        puts("");
        for(i=1;i<H_NUM;i++){
            if(winner == horses[i].name){
                printf("Horse %c wins! ", winner);
                if(horses[i].amountBet > 0){
                    payout = round((horses[i].amountBet/(horses[i].winChance-horses[i-1].winChance)) * 10000) / 100;
                    printf("You won $%.2f!\n", payout);
                }else printf("Better luck next time.\n");
                break;
            }
        }

        move = (rand() % (100 - 1 + 1)) + 1;
        for(i=1;i<H_NUM;i++){
            if(move <= horses[i].winChance && move > horses[i-1].winChance)horses[i].distance +=1;
        }
    }

    while ((getchar()) != '\n');
    puts("Type any key to return to menu:");
    scanf("%c", &exit);
    system("cls");
    return payout;
}