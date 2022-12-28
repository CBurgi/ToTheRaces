#include "FileEditor.h"

//number of horses + 1
#define H_NUM 5
#define H1_CHANCE 65
#define H2_CHANCE 80
#define H3_CHANCE 95

void makeHorses(horse horses[H_NUM]);
char nameHorse(horse horses[H_NUM], int currentH);
void printHorses(horse horses[H_NUM]);

void makeHorses(horse horses[H_NUM]){
    horses[0].amountBet = 0;
    horses[0].distance = 0;
    horses[0].name = '0';
    horses[0].winChance = 0;
    srand ( time(NULL) );

    //using a for loop here didnt work for some reason
    horses[1].amountBet = 0;
    horses[2].amountBet = 0;
    horses[3].amountBet = 0;
    horses[4].amountBet = 0;

    horses[1].distance = 0;
    horses[2].distance = 0;
    horses[3].distance = 0;
    horses[4].distance = 0;

    horses[1].name = nameHorse(horses, 1);
    horses[2].name = nameHorse(horses, 2);
    horses[3].name = nameHorse(horses, 3);
    horses[4].name = nameHorse(horses, 4);

    horses[1].winChance = (rand() % (H1_CHANCE - 1 + 1)) + 1;
    horses[2].winChance = (rand() % (H2_CHANCE - H1_CHANCE + 1)) + H1_CHANCE;
    horses[3].winChance = (rand() % (H1_CHANCE - H2_CHANCE + 1)) + H2_CHANCE;
    horses[4].winChance = 100;
}

//generates an engish capital letter that has not been used and assignes it to the current horse
char nameHorse(horse horses[H_NUM], int currentH) {
    char tempName = (rand() % (90 - 65 + 1)) + 65;
    for(int j = 0; j<currentH; j++){
        if(tempName == horses[j].name) tempName = nameHorse(horses, currentH);
    }

    return tempName;
}

//prints each horse and its percent chance of winning
void printHorses(horse horses[H_NUM]){
    for(int i = 0; i<H_NUM; i++){
        printf("%c: %i\n", horses[i].name, horses[i].winChance/* - horses[i-1].winChance*/);
    }
}