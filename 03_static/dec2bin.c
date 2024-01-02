/**
 * \file dec2bin.c
 * \author František Pártl (fpartl@ntis.zcu.cz)
 * \version 1.0
 * \date 2020-09-25
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Hlavní přístupový bod aplikace. Jako první parametr aplikace očekává kladné nenulové číslo,
 *        které převede do jeho binární podoby v přímém kódu).
 * \param argc Počet argumentů aplikace.
 * \param argv Argumenty aplikace.
 * \return int Funkce vrací hodnotu EXIT_SUCCESS při úspěchu, jinak vrací EXIT_FAILURE.
 */
int main(int argc, char *argv[]) {
    unsigned int dec;                                   /* Vstup aplikace. */
    char inverted_out[sizeof(dec) * 8 + 1] = { 0 };     /* Paměťový prostor pro výsledek převodu. */
    int i;                                              /* Iterační proměnná. */

    /* První parametr je vždy název spustitelného souboru. */
    if (argc < 2) {
        printf("usage: dec2bin <positive-number>\n");
        return EXIT_FAILURE;
    }

    /* Řetězec znaků z parametru převedu na číslo. */
    dec = abs(atoi(argv[1]));

    /**
     * ! Vidíme, že funkce main dělá více věcí, což je dle Single-responsibility principu nepřijatelné a funkci je tedy nutné
     * ! "rozbít" na menší celky. Doporučuji si to v rámci domácího tréninku zkusit. Napovídá tomu i nesourodost lokálních
     * ! proměnných (převod a výpis by měl být implementován v dedikovaných funkcích).
     */

    /* Vypíšu zadané číslo v dekadické soustavě. */
    printf("%d(d) = ", dec);
    for (i = 0; dec != 0; dec /= 2, ++i) {
        /* Při kompilaci se zjistí hodnota znaku '0'. Podle toho je pak do pole uložena hodnota znaku '0' nebo '1'. */
        inverted_out[i] = dec % 2 + '0';
    }

    for (--i; i >= 0; --i) {                    /* Další pěkné použití for cyklu pro výpis řetězce odzadu. */
        printf("%c", inverted_out[i]);          /* Pomocí %d si zkuste prvky pole pří výpisu interpretovat jako celá čísla. */
    }
    printf ("(b)\n");

    return EXIT_SUCCESS;
}
