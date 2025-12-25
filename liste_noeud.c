#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

typedef struct cellule_noeud_t {
    coord_t noeud;
    coord_t precedent;
    float cout;
    struct cellule_noeud_t* suivant;
} cellule_noeud_t;

struct liste_noeud_t {
    cellule_noeud_t* tete;
    int taille;
};

liste_noeud_t* creer_liste(void) {
    liste_noeud_t* liste = malloc(sizeof(*liste));
    if (liste == NULL) {
        return NULL;
    }
    liste->tete = NULL;
    liste->taille = 0;
    return liste;
}

void detruire_liste(liste_noeud_t** liste_ptr) {
    if (liste_ptr == NULL || *liste_ptr == NULL) {
        return;
    }
    cellule_noeud_t* courant = (*liste_ptr)->tete;
    while (courant != NULL) {
        cellule_noeud_t* suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    free(*liste_ptr);
    *liste_ptr = NULL;
}

bool est_vide_liste(const liste_noeud_t* liste) {
    return liste->taille == 0;
}

static cellule_noeud_t* trouver_noeud(const liste_noeud_t* liste, coord_t noeud) {
    for (cellule_noeud_t* cur = liste->tete; cur != NULL; cur = cur->suivant) {
        if (memes_coord(cur->noeud, noeud)) {
            return cur;
        }
    }
    return NULL;
}

bool contient_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    return trouver_noeud(liste, noeud) != NULL;
}

bool contient_arrete_liste(const liste_noeud_t* liste, coord_t source, coord_t destination) {
    cellule_noeud_t* dest = trouver_noeud(liste, destination);
    if (dest == NULL) {
        return false;
    }
    if (!contient_noeud_liste(liste, source)) {
        return false;
    }
    return memes_coord(dest->precedent, source);
}

float cout_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    cellule_noeud_t* cur = trouver_noeud(liste, noeud);
    if (cur == NULL) {
        return INFINITY;
    }
    return cur->cout;
}

coord_t precedent_noeud_liste(const liste_noeud_t* liste, coord_t noeud) {
    cellule_noeud_t* cur = trouver_noeud(liste, noeud);
    if (cur == NULL) {
        return creer_coord(-1, -1);
    }
    return cur->precedent;
}

coord_t min_noeud_liste(const liste_noeud_t* liste) {
    cellule_noeud_t* cur = liste->tete;
    cellule_noeud_t* best = cur;
    for (; cur != NULL; cur = cur->suivant) {
        if (cur->cout < best->cout) {
            best = cur;
        }
    }
    return best->noeud;
}

void inserer_noeud_liste(liste_noeud_t* liste, coord_t noeud, coord_t precedent, float cout) {
    cellule_noeud_t* cur = trouver_noeud(liste, noeud);
    if (cur != NULL) {
        cur->precedent = precedent;
        cur->cout = cout;
        return;
    }
    cellule_noeud_t* nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        return;
    }
    nouveau->noeud = noeud;
    nouveau->precedent = precedent;
    nouveau->cout = cout;
    nouveau->suivant = liste->tete;
    liste->tete = nouveau;
    liste->taille += 1;
}

void supprimer_noeud_liste(liste_noeud_t* liste, coord_t noeud) {
    cellule_noeud_t* cur = liste->tete;
    cellule_noeud_t* prev = NULL;
    while (cur != NULL) {
        if (memes_coord(cur->noeud, noeud)) {
            if (prev == NULL) {
                liste->tete = cur->suivant;
            } else {
                prev->suivant = cur->suivant;
            }
            free(cur);
            liste->taille -= 1;
            return;
        }
        prev = cur;
        cur = cur->suivant;
    }
}

