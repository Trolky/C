#include <stdio.h>
#include <stdlib.h>


int main(){
    int cislo;
    /* rozdíl mezi  const int *pointer_na_cislo;  a int * const pointer_na_cislo;*/
    /* c++ confusing pointer */
    int *pointer_na_cislo;
    int **pointer_na_pointer_na_cislo;
    /* R value literál, něco co není uloženo v paměti, používá se na pravé straně za = */
    cislo = 5;
    pointer_na_cislo = &cislo;
    pointer_na_pointer_na_cislo=&pointer_na_cislo;
    /* zásobník basepointer - 4 */
    /* jak ví že -4 protože bázový typ je int */
    /* %p (void*) */
    printf("%d, %d, %d\n", cislo, *pointer_na_cislo, **pointer_na_pointer_na_cislo);


    return EXIT_SUCCESS;
}