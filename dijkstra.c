#include "dijkstra.h"
#include "animation.h"
#include <stdlib.h>
#include <math.h>

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float cout(grille_t grille, coord_t courant, coord_t suivant) {
    float base = distance_euclidienne(courant, suivant);
    float denivele = get_hauteur(grille, suivant) - get_hauteur(grille, courant);
    if (denivele > 0.0f) {
        base += denivele;
    }
    return base;
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
static void construire_chemin_vers(
        liste_noeud_t* chemin,
        const liste_noeud_t* visites,
        coord_t source,
        coord_t noeud
    ) {
    if (!memes_coord(noeud, source)) {
        coord_t precedent = precedent_noeud_liste(visites, noeud);
        construire_chemin_vers(chemin, visites, source, precedent);
    }
    inserer_noeud_liste(
            chemin,
            noeud,
            precedent_noeud_liste(visites, noeud),
            cout_noeud_liste(visites, noeud)
    );
}

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {
    liste_noeud_t* a_traiter = creer_liste();
    liste_noeud_t* visites = creer_liste();
    coord_t no_prec = creer_coord(-1, -1);

    inserer_noeud_liste(a_traiter, source, no_prec, 0.0f);

    animate_source(source);
    animate_destination(destination);

    while (!est_vide_liste(a_traiter)) {
        coord_t courant = min_noeud_liste(a_traiter);
        float cout_courant = cout_noeud_liste(a_traiter, courant);
        coord_t prec_courant = precedent_noeud_liste(a_traiter, courant);

        supprimer_noeud_liste(a_traiter, courant);
        inserer_noeud_liste(visites, courant, prec_courant, cout_courant);

        animate_visiting(courant);

        if (memes_coord(courant, destination)) {
            break;
        }

        coord_t* voisins = NULL;
        size_t n_voisins = get_voisins(grille, courant, seuil, &voisins);
        for (size_t i = 0; i < n_voisins; i++) {
            coord_t voisin = voisins[i];
            animate_neighbor(voisin);

            if (contient_noeud_liste(visites, voisin)) {
                continue;
            }

            float alt = cout_courant + cout(grille, courant, voisin);
            if (alt < cout_noeud_liste(a_traiter, voisin)) {
                inserer_noeud_liste(a_traiter, voisin, courant, alt);
            }
        }
        free(voisins);
        animate_visited(visites);
    }

    float resultat = cout_noeud_liste(visites, destination);

    if (chemin != NULL) {
        *chemin = creer_liste();
        if (contient_noeud_liste(visites, destination)) {
            construire_chemin_vers(*chemin, visites, source, destination);
        }
        animate_path(*chemin);
    }

    detruire_liste(&a_traiter);
    detruire_liste(&visites);

    return resultat;
}

