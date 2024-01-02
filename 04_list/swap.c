/**
 * \file swap.c
 * \author František Pártl (fpartl\ntis.zcu.cz)
 * \brief Soubor obsahuje funkci pro prohození hodnot dvou proměnných.
 * \version 1.0
 * \date 2020-09-02
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \brief Funkce provede výměnu hodnot dvou proměnných typu `int`.
 *
 * \param a Ukazatel na proměnnou, která nabude hodnoty proměnné dané ukazatelem `b`.
 * \param b Ukazatel na proměnnou, která nabude hodnoty proměnné dané ukazatelem `a`.
 */
void swap_int(int *a, int *b) {
    int temp;

    /* Vždy když pracuji s pamětí danou ukazatelem, tak musím testovat platnost tohoto ukazatele. */
    if (!a || !b) {
        return;
    }

    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * \brief Funkce provede výměnu hodnot dvou proměnných nedefinovaného typu. Velikost proměnné je dána
 *        parametrem size.
 * 
 * \param a Ukazatel na proměnnou, která nabude hodnoty proměnné dané ukazatelem b.
 * \param b Ukazatel na proměnnou, která nabude hodnoty proměnné dané ukazatelem a.
 * \param size Velikost proměnných, jejichž hodnoty budou prohozeny.
 */
void swap(void *a, void *b, const size_t size) {
    void *temp;

    if (!a || !b || size == 0) {
        return;
    }

    /*
     * Během překladu nevím, jak velké jsou oblasti dané ukazateli `a` a `b`. Za běhu programu tedy
     * v závislosti na argument `size` musím dynamicky alokovat paměť pro pomocnou proměnnou `temp`.
    */
    temp = malloc(size);
    if (!temp) {
        return;
    }

    /* Kopírování paměti pomocí funkce `memcpy`. */
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);

    /* Dynamicky alokovanou oblast musím uvolnit, jinak se dopustím známého "memory leaku"! */
    free(temp);

    /* Jaké jsou nevýhody tohoto řešení? Jak by šel problém řešit jinak? */
}

/**
 * \brief Hlavní přístupový bod aplikace. Pomocí funkce `swap` prohodí hodnoty dvou lokálních proměnných
 *        a provede jejich výpis.
 * \return int Funkce vrací vždy hodnotu `EXIT_SUCCESS`.
 */
int main() {
    int a = 5, b = 10;

    printf("a = %d, b = %d\n", a, b);

    swap_int(&a, &b);
    swap(&a, &b, sizeof(int));  /* Zkuste si i funkci `swap`. */

    printf("a = %d, b = %d\n", a, b);
    return EXIT_SUCCESS;
}
