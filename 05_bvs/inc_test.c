/**
 * \file test.c
 * \author František Pártl (fpartl\ntis.zcu.cz)
 * \brief Ukázka nebezpečnosti velice nevhodného použití některých operátorů.
 * \version 1.0
 * \date 2020-09-04
 */

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Hlavní přístupový bod aplikace. Obsahuje ukázku nebezpečnosti při velice nevhodném použití
 *        některých operátorů.
 * \return int Funkce vždy vrací hodnotu `EXIT_SUCCESS`.
 */
int main() {
    int i = 5, j = 5;   /* Dvě proměnné na pokusy. */

    printf("i = %d, j = %d\n\n", i, j);     /* Na začátku si jenom vypíšeme původní hodnoty. */

    /*
     * Přeložte si zdrojový kód s přepínačem `-S` a podívejte se, jaký rozdíl dělá kompilátor mezi
     * mezi operátorem prefixové a postfixové inkrementace.
     */

    /* warning: operation on ‘i’ may be undefined [-Wsequence-point] */ 
    /* vyjde i = 5 */
    /*
        i = i++;
        printf("i = i++; => i = %d\n", i); 
    */

    /* warning: operation on ‘i’ may be undefined [-Wsequence-point] */
    /* vyjde i = 6 */
    /*
        i = ++i;
        printf("i = i++; => i = %d\n", i);
    */

    /* warning: operation on ‘i’ may be undefined [-Wsequence-point] */
    /* podmínka nebude splněna */
    /*
        if (i++ == ++i) {
            printf("i++ == ++i\n");
            printf("i = %d, j = %d\n", i, j);
        }
    */

    /* bohužel bez warningů (nikde tam není operátor přiřazení). */
    /* Podmínka bude splněna pokud i != 0 || -2. */
    /*
        if (i++ && ++i) {
            printf("i++ && ++i\n");
            printf("i = %d, j = %d\n", i, j);
        }
    */

    /* warning: operation on ‘j’ may be undefined [-Wsequence-point] */
    /* Při i = 5 a j = 5 vyjde 27. */
    /*
        j = (j++ * --i) + ++j;
        printf("i = %d, j = %d\n", i, j);
    */

    return EXIT_SUCCESS;
}