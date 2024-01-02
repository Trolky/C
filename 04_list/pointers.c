/**
 * \file pointers.c
 * \author František Pártl (fpartl\ntis.zcu.cz)
 * \brief První ukázka pořádná ukázka "pointerů".
 * \version 1.0
 * \date 2020-10-15
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Hlavní přístupový bod aplikace.
 * \return int Funkce vrací vždy hodnotu `EXIT_SUCCESS`.
 */
int main() {
    int cislo, *pointer_na_cislo, **pointer_na_pointer_na_cislo;

    /* POZOR NA NÁSLEDUJÍCÍ VARIANTU: `cislo_2` NENÍ UKAZATEL!*/
    int* pointer_na_cislo_2, cislo_2;

    /*
     * `int *pointer`, či `int* pointer`... to je oč tu běží!
     * Na toto téma by se dala vést "svatá válka" -- a taky že se vede: 
     * https://stackoverflow.com/questions/558474/what-makes-more-sense-char-string-or-char-string
     * 
     * HLAVNÍ JE KONZISTENCE VE VAŠICH ZDROJOVÝCH KÓDECH!
    */

    cislo = 5;                                          /* Inicializace staticky alokované proměnné. */
    pointer_na_cislo = &cislo;                          /* Inicializace staticky alokovaného ukazatele. */
    pointer_na_pointer_na_cislo = &pointer_na_cislo;    /* Inicializace staticky alokovaného ukazatele. */

    /* Bude fungovat i tento příkaz? Pozor na rozdíl mezi l-values vs r-values! */
    /* pointer_na_pointer_na_cislo = &(&cislo); */

    /* Pomocí dereferenčního operátoru `*` zjišťujeme hodnotu, jejíž typ a umístění je dán zadaným ukazatelem. */
    /* Pro nikoho by nemělo být překvapením, že výpis bude pro všechny výrazy stejný. */
    printf("%d, %d, %d\n", cislo, *pointer_na_cislo, **pointer_na_pointer_na_cislo);

    /* Víte jaké číslo zde bude vypsáno a proč? */
    printf("%ld\n", sizeof(int *));

    return EXIT_SUCCESS;
}