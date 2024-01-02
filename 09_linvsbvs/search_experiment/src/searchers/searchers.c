#include "searchers.h"

/**
 * Klíč k úspěchu!
 *
 * ! `struct commodity comms[]` == `struct commodity *comms`
 * ! `comm_id_array_type id` == `char ids[MAX_ID_LENGTH]`
 * ! `comm_id_array_type ids[]` == `char(*ids)[MAX_ID_LENGTH]`
 * ! `comm_id_array_type ids[]` == `char(ids[])[MAX_ID_LENGTH]`
 */

/**
 * Funkce ke studiu:
 *
 * `qsort`      https://en.cppreference.com/w/c/algorithm/qsort
 * `bsearch`    https://en.cppreference.com/w/c/algorithm/bsearch
 * `strcmp`     https://en.cppreference.com/w/c/string/byte/strcmp
 */

/** INFO: pro rychlejší debugging snižte hodnotu TEST_RUNS v souboru `config.h`. */


int linear_search(const struct commodity comms[], const size_t comms_count,
                    const comm_id_array_type ids[], const size_t ids_count, int quantities[]) {
    size_t i, j;
    int found;

    if (!comms || comms_count == 0 || !ids || ids_count == 0 || !quantities) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < ids_count; ++i) {
        found = 0;

        for (j = 0; j < comms_count; ++j) {
            if (strcmp(ids[i], comms[j].id) == 0) {
                quantities[i] = comms[j].quantity;
                found = 1;
                break;
            }
        }

        if (!found) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/* Správná implementace funkce. V C++ nám toto "usnadní" lambda výrazy (closures). */
static int _comm_compare(const void *a, const void *b) {
    return strcmp(((const struct commodity *)a)->id, ((const struct commodity *)b)->id);
}

/**
 * \brief Verze od studentů, která bude (možná překvapivě) také fungovat. Stejně jako v předchozí implementaci ukazatele
 *        `a` i `b` ukazují na instance struktury `commodity` v operační paměti. Dokud je tedy identifikátor komodity prvním
 *        členem struktury, tak zde použitá funkce `strcmp` bude ve výsledku skutečně porovnávat identifikátory, které jsou
 *        ukončeny ukončovací nulou. Pokud ale po 20 letech přijde jiný programátor, který změní pořadí členů struktury
 *        `commodity`, tak tato implementace (v úplně jiném zdrojovém kódu, který má na starosti jiný programátor) přestane
 *        fungovat. No prostě hnus...
 * \param a První komodita.
 * \param b Druhá komodita.
 * \return int -1 pokud `a` je v pořadí před `b`, 0 pokud `a` je stejné jako `b`, 1 pokud `a` je v pořadí za `b`.
 */
/*
int _comm_compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}
*/

/**
 * \brief Podívejte se na použití funkce `bsearch` v tomto zdrojovém souboru.
 * \param a Klíč.
 * \param b Komodita.
 * \return int -1 pokud `a` je v pořadí před `b`, 0 pokud `a` je stejné jako `b`, 1 pokud `a` je v pořadí za `b`.
 */
static int _ids_compare(const void *a, const void *b) {
    return strcmp(*(comm_id_array_type *)a, ((const struct commodity *)b)->id);
}

int binary_search(const struct commodity comms[], const size_t comms_count,
                    const comm_id_array_type ids[], const size_t ids_count, int quantities[]) {
    struct commodity *comms_copy, *found;
    size_t i;

    if (!comms || comms_count == 0 || !ids || ids_count == 0 || !quantities) {
        return EXIT_FAILURE;
    }

    comms_copy = malloc(sizeof(*comms_copy) * comms_count);
    if (!comms_copy) {
        return EXIT_FAILURE;
    }

    /* Pole comms je konstantní, takže je třeba jej zkopírovat. */
    memcpy(comms_copy, comms, sizeof(*comms_copy) * comms_count);

    /**
     * Někteří studenti volali funkci `qsort` s argumentem `__compar = (int (*)(const void *, const void *))strcmp`. Což je
     * šílený hnus, který ovšem naneštěstí bude fungovat. A to ze stejného důvodu jako v případě implementace funkce _comm_compare
     * výše.
     */
    qsort(comms_copy, comms_count, sizeof(*comms_copy), _comm_compare);

    for (i = 0; i < ids_count; ++i) {
        found = bsearch(&ids[i], comms_copy, comms_count, sizeof(*comms_copy), _ids_compare);
        if (!found) {
            free(comms_copy);
            return EXIT_FAILURE;
        }

        quantities[i] = found->quantity;
    }

    free(comms_copy);
    return EXIT_SUCCESS;
}
