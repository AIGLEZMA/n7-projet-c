#include "dijkstra.h"
#include "animation.h"

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
// TODO: construire_chemin_vers

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {
    // TODO
}


