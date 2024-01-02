/**
 * \file float2bin.c
 * \author František Pártl (fpartl@ntis.zcu.cz)
 * \version 1.0
 * \date 2020-09-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * \brief Konstrukce `union` nám umožňuje sjednotit množinu pohledů na konkrétní úsek paměti. Při vytvoření instance
 *        `float_int` se tedy v paměti alokují 4 B paměti, na kterou lze nahlížet jako na float nebo na int.
 */
union float_int {
    float f;
    unsigned int i;
};

/* ! Small String Optimization jako ukázka praktického použití konstrukce union. */
/* ! V tomto zdrojovém kódu se struktura `String` nevyužívá. */
struct string { 
    union {
        char static_buffer[16];
        char *dynamic_buffer;
    } data;

    size_t allocated;
    size_t length;
};
/* ! Konec ukázky SSO. */

/**
 * \brief Hlavní přístupový bod aplikace, která zadané desetinné číslo převádí do hexadecimální a binární soustavy.
 * \param argc Počet argumentů aplikace.
 * \param argv Argumenty aplikace.
 * \return int Funkce vrací `EXIT_SUCCESS` při úspěchu, jinak `EXIT_FAILURE`.
 */
int main(int argc, char *argv[]) {
    int i;
    union float_int x;

    /* Zkontrolujeme, že uživatel zadal požadovaný argument. */
    if (argc < 2) {
        printf("usage: float2bin <float-number>\n");
        return EXIT_FAILURE;
    }

    /* Pokud tento předpoklad neplatí, tak tato implementace bohužel nemůže fungovat... */
    assert(sizeof(x.f) == sizeof(x.i));

    x.f = atof(argv[1]);
    printf("%f(d) = %X(h) = ", x.f, x.i);

    for (i = sizeof(x.i) * 8 - 1; i >= 0; i--) {
        /* Operace binárního posunu nedává u datového typu float smysl. Díky konstrukci `union` ale máme řešení! */
        printf("%c", ((x.i >> i) & 1) + '0');

        /**
         * Když se nad úlohou dlouze zamyslíte, tak dojdete k následujícímu: bitový posun má de facto význam násobení resp. 
         * dělení dvojkou (0100(b) = 4(d) -> 0010(b) = 2(d) -> 1000(b) = 8(d)) a výsledek operace AND (`&`) bude nenulový,
         * právě když bude výsledek lichý. Vytvořili jsme tedy úplně stejný program jako v případě zdrojového souboru
         * `dec2bin.c`! Akorát trochu kamuflovaně. :-)
         *
         * Na doma:
         * (i)  Zkuste program `dec2bin.c` přepsat v tomto duchu.
         * (ii) Zkuste program `dec2bin.c` přeložit se zapnutými optimalizacemi (`-O`) a prozkoumejte výsledek kompilace (`-S`).
         */
    }

    printf("(b)\n");
    return EXIT_SUCCESS;
}
