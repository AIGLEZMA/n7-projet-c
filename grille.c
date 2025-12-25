#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    return (size_t) position.y * (size_t) grille.largeur +
           (size_t) position.x;
}

grille_t creer_grille(int largeur, int profondeur) {
    grille_t grille;

    grille.largeur = largeur;
    grille.profondeur = profondeur;
    
    size_t taille = (size_t) largeur * (size_t) profondeur;

    grille.hauteurs = calloc(taille, sizeof(float));

    return grille;
}

void detruire_grille(grille_t grille) {
    free(grille.hauteurs);
}

bool dans_les_bornes(grille_t grille, coord_t position) {
    return position.x >= 0 && position.y >= 0 &&
           position.x < grille.largeur && position.y < grille.profondeur;
}

int get_largeur(grille_t grille) {
    return grille.largeur;
}

int get_profondeur(grille_t grille) {
    return grille.profondeur;
}

coord_t inferieur_gauche(grille_t grille) {
    return creer_coord(0, 0);
}

coord_t superieur_droit(grille_t grille) {
    return creer_coord(grille.largeur - 1, grille.profondeur - 1);
}

void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    size_t index = coord_lin(grille, position);
    grille.hauteurs[index] = hauteur;
}

float get_hauteur(grille_t grille, coord_t position) {
    size_t index = coord_lin(grille, position);
    return grille.hauteurs[index];
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    *voisins = malloc(4 * sizeof(coord_t));

    const coord_t directions[4] = {
        translation(position, -1, 0),
        translation(position, 1, 0),
        translation(position, 0, -1),
        translation(position, 0, 1)
    };

    float hauteur = get_hauteur(grille, position);
    size_t compteur = 0;
    for (int i = 0; i < 4; i++) {
        coord_t candidat = directions[i];
        if (dans_les_bornes(grille, candidat)) {
            float diff = fabsf(hauteur - get_hauteur(grille, candidat));
            if (diff <= seuil) {
                (*voisins)[compteur++] = candidat;
            }
        }
    }

    return compteur;
}
