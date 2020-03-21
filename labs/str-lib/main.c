#include <stdio.h>
#include "strlib.h"

int main(int argc, char **argv) {
    if (argc<4 || argc>4) {
        printf("Correct usage: ./main string string_to_add substring_to_search\n");
        return 0;
    }
    char* origin = argv[1];
    char* addition = argv[2];
    char* sub = argv[3];
    char* subFound;
    printf("Initial Lenght      : %d\n", mystrlen(origin));
    char* newOrigin = mystradd(origin,addition);
    printf("New String          : %s\n", newOrigin);
    if (mystrfind(newOrigin,sub)) {
        subFound = "yes";
    } else {
        subFound = "no";
    }
    printf("SubString was found : %s\n", subFound);
    return 0;
}
