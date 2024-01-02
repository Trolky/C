/**
 * \file bubble_sort.c
 * \author František Pártl (fpartl@ntis.zcu.cz)
 * \brief Implementace algoritmu bublinkového řazení.
 * \version 1.0
 * \date 2020-09-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* Potřebujeme něco čím budemem inicializovat generátor pseudonáhodných čísel. */

/**
 * \brief Počet prvků pole, které bude generováno a následně řazeno bublinkovým řazením. Pozor! Pole je alokováno na zásobníku,
 *        takže to s jeho velikostí příliš nepřehánějte.
 */
#define ARR_LEN 5

/**
 * \brief Použití enumerického typu se zde může zdát jako overkill, ale zpřehledňuje kód.
 */
enum sort_order {
    ASCENDING = 0,      /** Vzestupné pořadí. */
    DESCENDING = 1      /** Sestupné pořadí. */
};

/**
 * \brief Funkce provede výpis zadaného pole s daným popiskem.
 *        V prototypu si všimněte použití specifikátoru `const`. Programátor se jím krásně chrání proti nedbalé
 *        úpravě vypisovaného pole, navíc dáváme kompilátoru další šance k optimalizaci.
 * \param array Ukazatel na prvky pole.
 * \param array_size Počet prvků pole.
 * \param label Popisek pole.
 */
void print_array(const int array[] /* stejné jako `const int *array` */, const size_t array_size, const char *array_label) {
    size_t i;

    /* Tisk popisku (pokud byl zadán). */
    if (array_label) {
        printf("%s:\n", array_label);
    }

    /*
     * Ošetření situace, kdy je předané pole prázdné.
     * `int array[]` je v očích kompilátoru obyčejný ukazatel na první prvek pole (v tomto případě integer)
     * Nemělo by Vás tedy překvapit, když někdo funkci `main` deklaruje s argumentem `char **argv` a ne s `char *argv[]`.
     * V následující podmínce tedy testujeme, zda je "ukazatel" `array` nenulový.
     */
    if (!array || array_size == 0) { 
        printf("<empty-array>\n");
        return;
    }

    for (i = 0; i < array_size; ++i) {
        printf("[%02lu] %12d\n", i + 1, array[i]);
    }
}

/**
 * \brief Funkce naplní zadané pole array_size náhodnými čísly z intervalu <0, RAND_MAX>.
 * \param array Pole, která bude plněno náhodnými hodnotami.
 * \param array_size Počet generovaných náhodných čísel.
 */
void random_fill_array(int array[] /* stejné jako `const int *array` */, const size_t array_size) {
    size_t i;

    /* Kontrola vstupních argumentů! Pokud tato podmínka platí, tak by další exekuce funkce byla nebezpečná! */
    if (!array || array_size == 0) {
        return;
    }

    /* Zadám generátoru seed pro generování. Co by se stalo, kdybych tento krok neudělal nebo snad dával vždy stejný seed? */
    srand(time(NULL));

    /* Naplním pole náhodnými hodnotami. */
    for (i = 0; i < array_size; ++i) {
        array[i] = rand();
    }
}

/**
 * \brief Funkce seřadí zadané pole pomocí algoritmu bublinkového řazení.
 * \param array Pole čísel, které bude řazeno.
 * \param array_size Počet prvků pole.
 */
void bubble_sort(int array[] /* stejné jako `const int *array` */, const size_t array_size, const enum sort_order order) {
    size_t i, end;
    unsigned char swapped;  /* Příznak `swapped` říká, zda došlo k prohození nějakých hodnot. */
    int temp;               /* Dočasná proměnná pro instalaci  */

    if (!array || array_size == 0) {
        return;
    }

    end = 0;
    do {
        swapped = 0;    /* S tímto přístupem a zadaným již seřazeným polem se výpočet po jednom průchodu polem ukončí.*/

        for (i = 0; i < array_size - end - 1; ++i) {
            if ((order == DESCENDING && array[i] < array[i + 1]) || (order == ASCENDING && array[i] > array[i + 1])) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                swapped = 1;
            }
        }

        ++end;
    } while (swapped);
}

/**
 * \brief Hlavní přístupový bod aplikace, který vygeneruje `ARR_LEN` celých čísel. Tato čísla budou následně seřazena algoritmem
 *        bublinkového řazení.
 * \return int Funkce vždy vrací hodnotu `EXIT_SUCCESS`.
 */
int main() {
    /* Pole čísel. POZOR! S konstantou `ARR_LEN` to nepřehánějte, zásobník má omezenou velikost (viz další cvičení). */
    int array[ARR_LEN];

    /* Vygeneruje pole náhodných prvků. */
    random_fill_array(array, ARR_LEN);
    print_array(array, ARR_LEN, "Generated items (unordered)");

    /* Pole seřadím pomocí algoritmu bubble sort sestupně. */
    bubble_sort(array, ARR_LEN, DESCENDING);
    print_array(array, ARR_LEN, "Generated items ordered in descending order");

    /* Pole seřadím pomocí algoritmu bubble sort vzestupně. */
    bubble_sort(array, ARR_LEN, ASCENDING);
    print_array(array, ARR_LEN, "Generated items ordered in ascending order");

    return EXIT_SUCCESS;
}
