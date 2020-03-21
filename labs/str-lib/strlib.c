#include <stdlib.h>
#include "strlib.h"

int mystrlen(char *str){
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        counter++;
    }
    return counter;
}

char* mystradd(char* origin, char* addition){
    int origin_length = mystrlen(origin);
    int addition_length = mystrlen(addition);
    int new_length = origin_length+addition_length;
    char* new_str = (char*)malloc(sizeof(char)*new_length);
    int i = 0;
    int j = 0;
    int k = 0;
    while (j<origin_length) {
        new_str[i] = origin[j];
        i++;
        j++;
    }
    while (k<addition_length) {
        new_str[i] = addition[k];
        i++;
        k++;
    }
    return new_str;
}

int mystrfind(char *origin, char *substr){
    int origin_length = mystrlen(origin);
    int substr_length = mystrlen(substr);
    int pointer = 0;
    int searchPoint = 0;
    while (pointer<origin_length) {
        if (searchPoint==substr_length) {
            return 1;
        } else if (origin[pointer+searchPoint]==substr[searchPoint]) {
            searchPoint++;
        } else {
            pointer++;
            searchPoint = 0;
        }
    }
    return 0;
}
