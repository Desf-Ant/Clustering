#ifndef DBSCAN_H
#define DBSCAN_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/donnees.h"
#include <vector>
#include <iterator>

class DBSCAN
{
    private :
        Donnees* donnees;
        std::vector <Sommet>* lesDonnees;
        type_dist type_distance;
        Distance distance;
        unsigned int nb_points_minimum;
        double distance_maximum;

        unsigned int classe_courante;
        std::vector<bool> deja_visites;
        std::vector<unsigned int> voisinage_courant;
        std::vector<unsigned int> a_ajouter_au_cluster;

    public:
        DBSCAN ( Donnees* d, type_dist t );
        void execute ( void );
        void calculVoisinage ( unsigned int indice );
        void etendCluster ( unsigned int indice );
};

#endif // DBSCAN_H
