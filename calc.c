/**
 * @file calc.c 
 * @author František Pártl (fpartl@ntis.zcu.cz)
 * @brief Zdrojový kód primitivní kalkulačky, která se zcela spoléhá na bezchybnost uživatele.
 * @version 1.0
 * @date 2020-09-02
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Maximální délka vstupu od uživatele. */
#define MAX_INPUT_LENGTH 64

/**
 * @brief Funkce vrátí součet zadaných parametrů.
 * @param a Sčítanec.
 * @param b Sčítanec.
 * @return float Součet.
 */
float sum(float a, float b) {
    return a + b;
}

/**
 * @brief Funkce vrátí rozdíl zadaných parametrů.
 * @param a Menšenec.
 * @param b Menšitel.
 * @return float Rozdíl.
 */
float sub(float a, float b) {
    return a - b;
}

/**
 * @brief Funkce vrátí součin zadaných parametrů. 
 * @param a Činitel.
 * @param b Činitel.
 * @return float Součin.
 */
float mul(float a, float b) {
    return a * b;
}

/**
 * @brief Funkce vrátí podíl zadaných parametrů.
 * @param a Dělenec.
 * @param b Dělitel.
 * @return float Podíl.
 */
float divide(float a , float b) {
    return a / b;
}

/**
 * @brief Přístupový bod aplikace. Rozhraním aplikace je primitivní konzolové rozhraní, které očekává 
 *        aritmetické výrazy v infixové formě bez mezer.
 * @return int Funkce vrací vždy `EXIT_SUCCESS`.
 */
int main() {
    /* TODO: handler ?! */
    float (*handler) (float, float);
    char op, input[MAX_INPUT_LENGTH];
    float a, b;

    printf("Enter \"quit\" to exit this amazing calculator.\n");
    while (1) { /* vtípek: #define forever while(1), MISRA compliant verze for(;;). */
        printf("> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);      /* Musím sice udat proud, ale je možné kontrolovat délku vstupního řetězce! Vidíte zde praktičnost této funkce? */

        /* Možná trochu neintuitivní porovnávání. Zkontrolujte dokumentaci. */
        /*if (input == "quit\n") porovnává adresy, přetížený operátor, dostal dvě adresy */
        if (strncmp(input, "quit\n", MAX_INPUT_LENGTH) == 0) {
            break;
        }

        /* Bez předání ukazatele to prostně nemůže jít, protože C předává parametry hodnotou. */
        sscanf(input, "%f%c%f", &a, &op, &b);   /* Zde neošetřujeme vstupy! Zkontrolujte dokumentaci funkce sscanf a opravte program! */

        /* Při použití ukazatelů na funkce je od switche jenom malý krůček k poli struktur (operátor, handler) a for cyklu v nové funkci `calc_func_type get_operator_handler(char op);`. */
        /* Opakující kód tím pádem úplně zmizí a možné operátory (a jejich obslužné funkce) můžeme přidávat a odebírat jednoduchou úpravou statického pole (konfiguračního souboru). */
        /* Zkuste si tento program v tomto duchu upravit. Funkce `main` pak bude dělat jenom jednu věc (Single Responsibility Principle)! */
        switch (op) {
            case '+' : handler = sum;     break;        /* Zde být & nemusí, protože bez () se nejedná o volání funkce, což kompilátor ví. */
            case '-' : handler = sub;     break;
            case '*' : handler = mul;     break;
            case '/' : handler = divide;  break;
            /* segmentace, stránkování, memory management */
            /* když se pokusím dereferencovat null pointer memory management mi rozbije hubu */
            default  : handler = NULL;    break;
        }

        if (handler) {
            printf("%f %c %f = %f\n", a, op, b, handler(a, b));
        }
        else printf("Unsupported operator %c!\n", op);
    }

    printf("You are leaving an awesome calculator. Be back soon!\n");
    return EXIT_SUCCESS;
}
