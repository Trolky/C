/**
 * \file bst.h
 * \author František Pártl (fpartl\ntis.zcu.cz)
 * \brief Hlavičkový soubor obsahující deklarace funkcí pracujících se strukturou bvs s celočíselnou hodnotou.
 * \version 1.0 
 * \date 2020-09-04
 */

#ifndef BST_H
#define BST_H

/**
 * \brief Struktura představuje jeden uzel v binárním vyhledávacím stromu.
 */
struct bst_node {  
    int key;                    /** Klíč uzlu. */
    struct bst_node *left;      /** Ukazatel na levého potomka. */
    struct bst_node *right;     /** Ukazatel na pravého potomka. */    
};

/**
 * \brief Funkce přidá klíč key do binárního vyhledávacího stromu `root`.
 * \param root Ukazatel na ukazatel na vrchol stromu.
 * \param key Přidávaný klíč.
 * \return int 1, pokud vše dopadlo dobře, jinak 0.
 */
int bst_add(struct bst_node ** const root, int key);

/**
 * \brief Funkce provede výpis binárního vyhledávacího stromu, který je dán ukazatelem na svůj kořen.
 * \param root Ukazatel na kořen binárního vyhledávacího stromu, který má být vytištěn.
 */
void bst_print(const struct bst_node *root);

/**
 * \brief Funkce pro uvolnění binárního vyhledávacího stromu z paměti. 
 * \param root Ukazatel na ukazatel na vrchol stromu, který bude uvolněn z paměti.
 */
void bst_free(struct bst_node **root);

/**
 * \brief Funkce vrací počet uzlů binárního vyhledávacího stromu.
 * \param root Ukazatel na vrchol stromu, jehož počet bude zjišťován.
 * \return Počet uzlů stromu s kořenem root.
 */
int bst_size(const struct bst_node *root);

/**
 * \brief Funkce vrací vyváženost stromu, tj. rozdíl mezi počtem uzlů pravého a levého podstromu.
 * \param root Ukazatel na vrchol stromu, jehož počet bude zjišťován.
 * \return int Vyváženost stromu s kořenem root.
 */
int bst_dsize(const struct bst_node *root);

#endif