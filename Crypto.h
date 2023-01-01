#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 40
//cryptoMagic is another one of my programs
//https://github.com/CBurgi/cryptoMagic

//encripts a string following cryptoMagic's logic
char* encrypt(char* decrp){
    char *crp = (char*)malloc(strlen(decrp)*2+1);
    
    char temp[3];
    int letter, j=0;

    for(int i=0; i<strlen(decrp); i++){
        if(decrp[i] == '\0')break;
        letter = decrp[i];

        letter -= 16;
        if(letter < 32) letter = (letter - 32) +144;

        sprintf(temp, "%X", letter);
        crp[j] = temp[0];
        crp[j+1] = temp[1];
        j+=2;
    }
    for(j;j<strlen(crp);j++)crp[j] = '\0';

    return crp;
}

//decrypts a string following cryptoMagic's logic
char* decrypt(char* crp){
    char *decrp = (char*)malloc(strlen(crp)/2);
    char temp[3];
    int letter, j=0;

    for(int i=0; i<strlen(crp); i+=2){
        if(crp[i] == '\0')break;

        temp[0] = crp[i];
        temp[1] = crp[i+1];

        sscanf(temp, "%X", &letter);
        
        letter += 16;
        if(letter > 127) letter = (letter - 144) + 32;

        decrp[j] = letter;
        j++;
    }

    for(j;j<strlen(decrp);j++)decrp[j] = '\0';
    return decrp;
}