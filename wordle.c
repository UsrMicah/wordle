/*
This program uses the list of common english words from
https://github.com/first20hours/google-10000-english.git
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "words.h"
#define MAXWORDS 1382
int getword(char *s, int max) {
    int i = 0;
    int a = 0;
    char c;
    while((c = getchar()) != '\n') {
        if(i < max) {
            s[i] = c;
            i++;
        }
        a++;
    }
    s[i] = 0;
    return a;
}
int isinword(char c, char *s) {
    for(int i = 0; s[i] != 0; i++) {
        if(s[i] == c)
            return 1;
    }
    return 0;
}
int val() {
    int out = 0;
    int c;
    while((c = getchar()) != '\n' && c != EOF)
        out += c;
    return out;
}
int main() {
    int wp = 0;
    int wc = 0;
    int next = 0;
    int run = 1;
    int turns = 0;
    printf("\033[2J\033[HEnter randomizer seed: ");
    wp = val()%MAXWORDS;
    printf("Your Word has been chosen. Proceed.\n");

    char word[6];
    do {
        while((wc = getword(word,5)) != 5) {
            next+=wc;
            printf("\033[1F");
            for(int i = 0; i < wc; i++)
                printf(" ");
            printf("\n\033[1F");
        }
        next+=wc;
        printf("\033[1F");
        for(int i = 0; i < 5 && word[i] != 0; i++) {
            if(isinword(word[i],words[wp]))
                printf("\033[33m");
            else
                printf("\033[31m");
            if(word[i] == words[wp][i])
                printf("\033[32m");
            printf("%c",word[i]);
        }
        printf("\033[0m\n");
        turns++;

        if(turns == 6 || strcmp(word,words[wp]) == 0) {
            if(strcmp(word,words[wp]) != 0) 
                printf("Your word was %s.\n",words[wp]);
            else
                printf("\033[1;4;33mCongratulations! You got the word on your %d%s try.\033[0m\n",turns, (turns < 4) ? ((turns == 1) ? "st" : ((turns == 2) ? "nd" : "rd")) : "th");
            printf("Would you like to play again? \033[4m(y/n)\033[0m ");
            getword(word,5);
            if(word[0] != 'y') {
                if(word[0] != 'n')
                    printf("I'll take that as a no.\n");
                run = 0;
                printf("Works cited:\nhttps://github.com/first20hours/google-10000-english.git\nhttps://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797\n\n");
            }
            else {
                wp = (wp+next)%MAXWORDS;
                turns = 0;
                printf("\033[2J\033[HYour word has been chosen. Proceed.\n");
            }
        }
    } while(run);

}