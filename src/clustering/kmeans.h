#ifndef KMEANS_H
#define KMEANS_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/donnees.h"

class Kmeans
{
    private :
        Donnees* donnees;
        std::vector<Sommet>* lesDonnees;
        unsigned int nb_classes;
        Distance distance;

        std::vector<Sommet> graines;
        std::vector<Sommet> centroids;
        std::vector<int> nb_sommets_par_classe;

    public:
        Kmeans ( Donnees* d, unsigned int n, type_dist t );
        void execute ( void );

    private :
        void initialise ( void );
        void attribueClasse ( void );
        bool calculNouvelleGraines ( void );
};

#endif // KMEANS_H
