#include <stdio.h>
#include <stdlib.h>
 
int compare(const void *a, const void *b) {
   return ( *(int*)a - *(int*)b );
}

int countDistinctElements(int *array, int size){
    int i;
    qsort(array, size, sizeof(int), compare);
    int result = 0;
    for (int i = 0; i < size; i++) { 
        while (i < size - 1 && array[i] == array[i + 1]) 
            i++; 
        result++; 
    } 
    return result;
}
 
int main(){
    int array[6] = {2, 1, 1, 2, 3, 1}; 
    int x = countDistinctElements(array, 5);
    printf("%d",x);
    return 0;
}