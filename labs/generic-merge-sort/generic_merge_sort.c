#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int arr[],int left,int middle,int right) {
    int i=0;
    int j=0;
    int k=left;
    int leftArraySize = middle-left+1;
    int rightArraySize = right-middle;

    int tempLeftArray[leftArraySize];
    int tempRightArray[rightArraySize];

    for (int h = 0; h < leftArraySize; h++) {
        tempLeftArray[h] = arr[left+h];
    }
    for (int p = 0; p < rightArraySize; p++) {
        tempRightArray[p] = arr[middle+1+p];
    }

    while (i<leftArraySize && j<rightArraySize) {
        if (tempLeftArray[i]>tempRightArray[j]) {
            arr[k] = tempRightArray[j];
            j++;
        } else {
            arr[k] = tempLeftArray[i];
            i++;
        }
        k++;
    }
    
    while (i<leftArraySize) {
        arr[k] = tempLeftArray[i];
        i++;
        k++;
    }

    while (j<rightArraySize) {
        arr[k] = tempRightArray[j];
        j++;
        k++;
    }
}

void mergesort(int arr[], int left, int right) {
    if (left < right) {
        int middle = ( left + right ) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle+1, right);
        merge(arr, left, middle, right);
    }
}

int main(int argc, char *argv[]) {
    int size = argc-1;
    if (size==0) {
        printf("Add list of numbers when running\n");
        return 0;
    }
    
    int arr[size];

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i+1]);
    }
    
    mergesort(arr,0,size-1);

    printf("Output: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    
    return 0;
}
