#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"

#define MAX 40
FILE *file;
int testnum = 1;

void readFile(user **readList, char filename[]);
user* newUser(char* name, char* pass, double balance);
void addUser(user **userList, user *temp);
void writeFile(user **writeList, char filename[]);

//reads through a file and makes a list based on its contents
void readFile(user **readList, char filename[])
{
    char tempName[MAX];
    char tempPass[MAX];
    char tempBalance[MAX];
    char blank[10];

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Can't open file");
        exit(1);
    }

    //runs for each 'node' (4 lines) in the file
    while (!feof(file))
    {
        printf("Reading user %i...\n", testnum);

        //assigns contents of first line temp user's Name
        fgets(tempName, MAX, file);
        tempName[strlen(tempName) - 1] = '\0';

        //assigns contents of second line temp user's Pass
        fgets(tempPass, MAX, file);
        tempPass[strlen(tempPass) - 1] = '\0';

        //assigns contents of third line temp user's return date
        fgets(tempBalance, MAX, file);
        tempBalance[strlen(tempBalance) - 1] = '\0';

        //for the blank lines separating each node
        fgets(blank, 5, file);

        //now that we have all the info we can make a new user and add it to the end of the designated list
        addUser(readList, newUser(tempName, tempPass, atof(tempBalance)));
        testnum++;
    }
    printf("All users read from %s\n\n", filename);
    fclose(file);
}

//makes a user node from a username, password, and balance
user* newUser(char* name, char* pass, double balance){
    user* temp = (user *)malloc(sizeof(user));
    temp->username = (char*)malloc(MAX);
    temp->password = (char*)malloc(MAX);
    temp->next = NULL;

    strcpy(temp->username, name);
    strcpy(temp->password, pass);
    temp->balance = balance;

    return temp;
}

//adds a user passed from readFile to the end of a list
void addUser(user **userList, user *temp)
{
    user *ptr = NULL;

    //special case for if list is empty
    if (*userList == NULL)
    {
        *userList = temp;
    }
    //case for if list is not empty
    else
    {
        ptr = *userList;
        //runs until end of list
        while (ptr != NULL)
        {
            if (ptr->next == NULL)
            {
                ptr->next = temp;
                break;
            }
            else
                ptr = ptr->next;
        }
    }
}

//writes all the nodes of a list to a file
void writeFile(user **writeList, char filename[])
{
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Can't open file");
        exit(1);
    }

    user *ptr = NULL;
    ptr = *writeList;
    //runs through all the nodes in the list and prints its contents to the file
    while (ptr != NULL)
    {
        fprintf(file, "%s\n%s\n%.2f", ptr->username, ptr->password, ptr->balance);
        (ptr->next != NULL) ? fprintf(file, "\n\n") : fprintf(file, "\n");
        ptr = ptr->next;
    }

    fclose(file);
}

