/**
 * \file bst.c
 * \author František Pártl (fpartl\ntis.zcu.cz)
 * \brief Implementace funkcí pracujících s binárním vyhledávacím stromem.
 * \version 1.0
 * \date 2020-09-07
 */

#include "bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
    Zavazuji se kompilátoru, že hodnotu ukazatele root v této funkce nebudu měnit.
    Ukazatel, na který ukazatel root ukazuje, ale změnit mohu. 
    Stejně tak instanci struktury bst_node, na kterou ukazatel root nepřímo ukazuje, změnit mohu.
*/
int bst_add(struct bst_node ** const root, int key) {
    struct bst_node *new, *it;

    if (!root) {
        return 0;   /* Byl zadán neplatný ukazatel. */
    }

    /* Analogie z Javy: klíčovým slovem "new" alokuji potřebný paměťový prostor na haldě a zavolám konstruktor. */
    new = malloc(sizeof(*new));
    if (!new) {
        return 0;  /* Alokace paměti se nezdařila. */
    }

    new->key = key;                 /* Inicializace nově alokované paměti (volání konstruktoru). */
    new->left = new->right = NULL;

    if (!*root) {                   /* Přidávám prvek do prázdného stromu. */
        *root = new;
        return 1;
    }

    it = *root;                     /* Inicializujeme iterátor, se kterým strom projdeme, abychom prvek zařadili na správné místo. */
    for (;;) {
        if (new->key > it->key) {   /* Pohybujeme se stromem směrem vpravo. */
            if (it->right) {        /* Má aktuální vrchol pravého potomka? */
                it = it->right;
            }
            else {
                it->right = new;
                break;
            }
        }
        else {                      /* Pohybujeme se stromem směrem vlevo. */
            if (it->left) {         /* Má aktuální vrchol levého potomka? */
                it = it->left;
            }
            else {
                it->left = new;
                break;
            }
        }
    }

    /*
        Je tato funkce správně navržena? Samozřejmě není! Je to hnus!
        TODO: Mějte na paměti Single-responsibility principle a zkuste si tuto funkci správně dekomponovat.
    */

    return 1;
}

void bst_print(const struct bst_node *root) {
    if (!root) {
        printf("X");
    }
    else {
        printf("(");
        bst_print(root->left);
        printf(" %d ", root->key);
        bst_print(root->right);
        printf(")");
    }
}

/* Opět předávám **, aby bylo možné ukazatel první úrovně změnit (v naší aplikaci deklarovaný v tree.c:20). */
void bst_free(struct bst_node **root) {
    /* Zde spoléháme na neúplné vyhodnocování podmínek. Pozor tedy na zdánlivě stejnou podmínku !*root || !root. */
    if (!root || !*root) {
        return;
    }

    bst_free(&((*root)->left));
    bst_free(&((*root)->right));

    /* V jaké pořadí se budou vrcholy uvolňovat z paměti? */
    /* printf("\nFreeing node %d.", (*root)->key); */

    free(*root);
    *root = NULL;
}

int bst_size(const struct bst_node *root) {
    int left_count = 0, right_count = 0;    /* Inicializace je zde kritická. Jinak by určení velikosti stromu bylo zcela nedeterministické. */

    if (!root) {
        return 0;
    }

    if (root->right) {
        right_count = bst_size(root->right);
    }
    if (root->left) {
        left_count = bst_size(root->left);
    }

    return right_count + left_count + 1;    /* Musí přičíst ještě sebe. */
}

/* Funkce bst_size jde samozřejmě zapsat vícero způsoby. U poslední verze dejte pozor na zbytečné a drahé funkční volání při neexistujícím potomkovi. */
/*
int bst_size(const struct bst_node *root) {
    int left_count, right_count;

    if (!root) {
        return 0;
    }

    right_count = (root->right) ? bst_size(root->right) : 0;    Ukázka použití ternárního operátoru.
    left_count = (root->left) ? bst_size(root->left) : 0;

    return right_count + left_count + 1;
}

int bst_size(const struct bst_node *root) {
    return (root) ? bst_size(root->right) + bst_size(root->left) + 1 : 0;
}
*/

int bst_dsize(const struct bst_node *root) {
    return (root) ? bst_size(root->right) - bst_size(root->left) : 0;
}
