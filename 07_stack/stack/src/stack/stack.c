#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct stack *stack_alloc(const size_t size, const size_t item_size) {
    struct stack *new_stack;

    if (size == 0 || item_size == 0) {
        return NULL;
    }

    new_stack = malloc(sizeof(*new_stack));
    if (!new_stack) {
        return NULL;
    }

    if (!stack_init(new_stack, size, item_size)) {
        free(new_stack);
        return NULL;
    }

    return new_stack;
}

int stack_init(struct stack *s, const size_t size, const size_t item_size) {
    if (!s || size == 0 || item_size == 0) {
        return 0;
    }

    s->size = size;
    s->item_size = item_size;
    s->sp = 0;

    s->items = malloc(size * item_size);
    if (!s->items) {
        return 0;
    }

    return 1;
}

void stack_deinit(struct stack *s) {
    if (!s) {
        return;
    }

    /* Uvolníme dynamicky alokovanou paměť, kterou instance struktury drží. */
    if (s->items) {
        free(s->items);
        s->items = NULL;
    }

    /* Případně po sobě můžeme uklidit ještě pečlivěji. */
    s->sp = 0;
    s->size = 0;
    s->item_size = 0;
    s->items = NULL;
}

void stack_dealloc(struct stack **s) {
    if (!s || !*s) {
        return;
    }

    /* Pro uvolnění vnitřních členů struktury máme připravenou funkci. */
    stack_deinit(*s);

    /* Nakonec uvolníme samotnou dynamicky alokovanou instanci struktury `stack`. */
    free(*s);
    *s = NULL;
}

int stack_push(struct stack *s, const void *item) {
    /* size_t i; */

    if (!s || !item || s->sp >= s->size) {
        return 0;
    }

    /* Doporučený způsob kopírování. */
    memcpy((char *)s->items + s->sp * s->item_size, item, s->item_size);

    s->sp++;

    /* Nebo můžu kopírovat pomocí for cyklu, ale je to pomalé. */
    /*
    for (i = 0; i < s->item_size; i++) {
        *((char *)s->items + s->sp * s->item_size + i) = *((char *)item + i);
        ((char *)s->items)[s->sp * s->item_size + i] = ((char *)item)[i];
        (s->sp * s->item_size + i)[(char *)s->items] = i[(char *)item]; (:brutalvomitingface:)
    }
    */

   return 1;
}

int stack_pop(struct stack *s, void *item) {
    if (!s) {
        return 0;
    }

    /* Pokud byl zadán platný ukazatel `item`, zkopírujeme prvek z vrcholu zásobníku. */
    if (item && !stack_head(s, item)) {
        return 0;
    }

    s->sp--;
    return 1;
}

int stack_head(const struct stack *s, void *item) {
    if (stack_item_count(s) == 0 || !item) {
        return 0;
    }

    /* Doporučený způsob kopírování paměti. */
    memcpy(item, (char *)s->items + (s->sp - 1) * s->item_size, s->item_size);

    /* Opět je samozřejmě možné kopírovat for cyklem, ale je to pomalé. */
    return 1;
}

size_t stack_item_count(const struct stack *s) {
    if (!s) {
        return 0;
    }

    return s->sp;
}
