#ifndef KMEDIANS_H
#define KMEDIANS_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/donnees.h"
#include <algorithm>

class Kmedians
{
    private :
        Donnees* donnees;
        std::vector<Sommet>* lesDonnees;
        unsigned int nb_classes;
        Distance distance;

        std::vector<Sommet> graines;
        std::vector < std::vector<int> > listesX;
        std::vector < std::vector<int> > listesY;
        std::vector < std::vector<int> > listesZ;
        std::vector<int> nb_sommets_par_classe;

    public:
        Kmedians ( Donnees* d, unsigned int n, type_dist t );
        void execute ( void );

    private :
        void initialise ( void );
        void attribueClasse ( void );
        bool calculNouvelleGraines ( void );
};

#endif // KMEANS_H
