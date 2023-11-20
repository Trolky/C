#include "loader_examples.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "person.h"
#include "vector.h"
#include "config.h"

/* Jen pro ukázku. */
#define TODO(message) \
    printf(__FILE__":%d This has not been implemented yet: "#message"!\n", __LINE__);


void int_loader_example() {
    char line[CHAR_BUFFER_SIZE] = { 0 };
    struct vector *numbers;
    FILE *file;
    int temp;

    file = fopen(INTEGER_FILE, "r");
    if (!file) {
        return;
    }

    numbers = vector_allocate(sizeof(int), NULL);
    if (!numbers) {
        goto clean_and_exit;
    }

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        temp = atoi(line);

        if (!vector_push_back(numbers, &temp)) {

            goto clean_and_exit;
        }
    }

  #ifdef PRINT_VECTORS
    for (size_t i = 0; i < vector_count(numbers); ++i) {
        printf("%d\n", *(int *)vector_at(numbers, i)); /*i prvek ve vektoru numbers */
    }
  #endif

  clean_and_exit:
    vector_deallocate(&numbers);
    fclose(file);
}
static void person_dealloc_wrapper(void *poor) {
    person_deallocate(poor);
}

void dynamic_person_loader_example() {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *name;
    int age, shoe_size;
    FILE *file;
    struct vector *persons;
    struct person *temp_person;

    #define EXIT_IF_NOT(expression)         \
        if (!(expression)) {                \
            vector_deallocate(&persons);    \
            fclose(file);                   \
            return;                         \
        }

    file = fopen(PERSON_FILE, "r");
    if (!file) {
        return;
    }

   
    persons = vector_allocate(sizeof(struct person *), person_dealloc_wrapper);
    EXIT_IF_NOT(persons);

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        if (strlen(line) == 0) {
            continue;
        }

        age = atoi(strtok(line, CSV_DELIMETER));
        shoe_size = atoi(strtok(NULL, CSV_DELIMETER));
        name = strtok(NULL, CSV_DELIMETER);
        name[strcspn(name, "\r\n")] = 0;

        temp_person = person_allocate(name, age, shoe_size);
        EXIT_IF_NOT(temp_person);
        EXIT_IF_NOT(vector_push_back(persons, &temp_person));
    }

    /**
     * Uvědomte si, co přesně je uloženo ve vektoru persons (přesný datový typ).
     * Prvek z vektoru vyberte pomocí funkce vector_at a opět se důkladně zamyslete nad tím, co tato funkce vrací.
     * Instanci struktury struct person je možné vypsat pomocí funkce person_print, která je deklarována v person.h.
     */
  #ifdef PRINT_VECTORS
    for (size_t i = 0; i < vector_count(persons); ++i) {
        struct person *current_person = *(struct person **)vector_at(persons,i); 
        person_print(current_person);
    }
  #endif

    EXIT_IF_NOT(0);
    #undef EXIT_IF_NOT
}

/**
 * \brief Účel této obalové funkce popisuje "slohová práce" výše. Ve zkratce se tímto způsobem zbavujeme standardem
 *        nedefinované konverze ukazatelů funkce a místo toho implicitně převádíme samotné ukazatele, v tomto případě
 *  
 *            `void *` na `struct person *`.
 * 
 *        Využíváním implicitních konverzí dáváme kompilátoru prostor pro kontrolu.
 * 
 * \param poor Ukazatel na deinicilizovanou instanci struktury `person`.
 */
static void person_deinit_wrapper(void *poor) {
    person_deinit(poor);
}

void static_person_loader_example() {
    char line[CHAR_BUFFER_SIZE] = { 0 }, *name;
    int age, shoe_size;
    FILE *file;
    struct vector *persons;
    struct person temp_person;

    #define EXIT_IF_NOT(expression)         \
        if (!(expression)) {                \
            vector_deallocate(&persons);    \
            fclose(file);                   \
            return;                         \
        }

    file = fopen(PERSON_FILE, "r");
    if (!file) {
        return;
    }

    /* Zde není potřeba ošklivé explicitní konverze! Super! */
    persons = vector_allocate(sizeof(temp_person), person_deinit_wrapper);
    EXIT_IF_NOT(persons)

    while (fgets(line, CHAR_BUFFER_SIZE, file)) {
        if (strlen(line) == 0) {
            continue;
        }

        age = atoi(strtok(line, CSV_DELIMETER));
        shoe_size = atoi(strtok(NULL, CSV_DELIMETER));
        name = strtok(NULL, CSV_DELIMETER);
        name[strcspn(name, "\r\n")] = 0;

        /* Inicializuji automaticky alokovanou (na zásobníku této funkce) instanci struktury struct person. */
        EXIT_IF_NOT(person_init(&temp_person, name, age, shoe_size));

        /* A zkopírujeme ji do vektoru persons. */
        EXIT_IF_NOT(vector_push_back(persons, &temp_person));
    }

    /**
     * Uvědomte si, co přesně je uloženo ve vektoru persons (přesný datový typ).
     * Prvek z vektoru vyberte pomocí funkce vector_at a opět se důkladně zamyslete nad tím, co tato funkce vrací.
     * Instanci struktury struct person je možné vypsat pomocí funkce person_print, která je deklarována v person.h.
     */
  #ifdef PRINT_VECTORS
    for (size_t i = 0; i < vector_count(persons); ++i) {
        struct person *current_person = (struct person *)vector_at(persons,i);
        person_print(current_person);
    }
  #endif

    EXIT_IF_NOT(0);
    #undef EXIT_IF_NOT
}
