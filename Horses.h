#include "FileEditor.h"

//number of horses + 1
#define H_NUM 5
#define H1_CHANCE 50
#define H2_CHANCE 70
#define H3_CHANCE 85

void makeHorses(horse horses[H_NUM]);
char nameHorse(horse horses[H_NUM], int currentH);
void printHorses(horse horses[H_NUM]);

//Makes the 4 horses that will be used for the race
//and one extra horse at the beginning of the array
//for calculation purposes
void makeHorses(horse horses[H_NUM]){
    horses[0].amountBet = 0;
    horses[0].distance = 0;
    horses[0].name = '0';
    horses[0].winChance = 0;
    srand ( time(NULL) );

    for(int i=0;i<H_NUM; i++){
        horses[i].amountBet = 0;
        horses[i].distance = 0;
        horses[i].name = nameHorse(horses, i);
    }

    horses[1].winChance = (rand() % (H1_CHANCE - 1 + 1)) + 1;
    horses[2].winChance = (rand() % (H2_CHANCE - H1_CHANCE + 1)) + H1_CHANCE;
    horses[3].winChance = (rand() % (H1_CHANCE - H2_CHANCE + 1)) + H2_CHANCE;
    horses[4].winChance = 100;
}

//generates an english capital letter that has not been used and assigns it to the current horse
char nameHorse(horse horses[H_NUM], int currentH) {
    char tempName = (rand() % (90 - 65 + 1)) + 65;
    for(int j = 0; j<currentH; j++){
        if(tempName == horses[j].name) tempName = nameHorse(horses, currentH);
    }

    return tempName;
}

//prints each horse and its percent chance of winning
void printHorses(horse horses[H_NUM]){
    for(int i = 1; i<H_NUM; i++){
        printf("Horse %c [Odds: %i%%, Currently $%.2f bet]\n", horses[i].name, horses[i].winChance - horses[i-1].winChance, horses[i].amountBet);
    }
}