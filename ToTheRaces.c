//Horse Betting Simulator
//Cole Burgi - [date]

#include "FileEditor.h"
#include "Crypto.h"
#include <conio.h>

#define MAX 40

double login(user* list, char* user);
int makeUser(user** list, char* user, char* pass);

int main(){
    double balance;
    char* username = (char*)malloc(MAX);
    user* users = NULL;
    readFile(&users, "users.crp");
    //readFile(&users, "usersDev.txt");
    system("cls");

    puts(" ~*~*~*~*~*~*~ Welcome to the races! ~*~*~*~*~*~*~ ");
    puts("Press 'e' at any time to return to a previous menu.");
    balance = login(users, username);
    printf("%.2f", balance);

    writeFile(&users, "users.crp");
    //writeFile(users, "usersDev.txt");
    system("cls");
    return 0;
}

double login(user* list, char* username){
    char* password = (char*)malloc(MAX);
    user* ptr = list;

    while(1){
        puts("Enter username (or type new to make a new account)");
        scanf("%s", username);
        if(!strcmp("new", username)){
            if(!makeUser(&list, username, password))continue;
            return 0.00;
        }else if(!strcmp("e", username))exit (1);

        puts("Enter password");
        scanf("%s", password);

        username = encrypt(username);
        password = encrypt(password);

        int uFound = 0;
        while(ptr != NULL){
            if(!strcmp(username, ptr->username)){
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

int makeUser(user** list, char* username, char* pass){
    system("cls");
    user* ptr = *list;
    char* pass2 = (char*)malloc(MAX);

    while(1){
        puts("Enter new username");
        scanf("%s", username);
        if(!strcmp("e", username)){
            system("cls");
            return 0;
        }
        int uNique = 1;
        while(ptr != NULL){
            if(!strcmp(encrypt(username), ptr->username)){
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

    addUser(list, newUser(encrypt(username), encrypt(pass), 0.00));
    return 1;
}