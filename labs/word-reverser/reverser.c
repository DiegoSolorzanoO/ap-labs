// Diego Solorzano Ortiz A01422048

#include <stdio.h>
#include <stdlib.h>

void reverse(int lenght, int arr[]) {

    int i, tmp;

    for (i = 0;  i < lenght/2; i++) {
        tmp = arr[i];
        arr[i] = arr[lenght - i - 1];
        arr[lenght - i - 1] = tmp;
    }
    for (size_t k = 0; k < lenght; k++) {
        printf("%c",arr[k]);
    }
    printf(" ");
    
}


int main(){
    int *arr, c;
    int size = 2;
    int i = 0;

    arr = (int*) malloc(size * sizeof(int));
    
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            reverse(i,arr);
            i = 0;
            printf("\n");
        } else {
            if (i == size) {
                arr = realloc(arr,size*2*sizeof(int));
                size = size*2;
            }
            if (c == ' ') {
                reverse(i,arr);
                i = 0;
            } else {
                arr[i] = c;
                i = i + 1;
            }
        }
    }
  
    free(arr);

    return 0;
}
