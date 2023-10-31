#include <stdio.h>
#include <stdlib.h>
 void swap_int(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
 }


int main(){
    int a = 5, b = 10;
    printf("a = %d, b = %d\n", a, b);

    swap_int(&a, &b);

    printf("a = %d, b = %d\n", a, b);
    
    return EXIT_SUCCESS;
}