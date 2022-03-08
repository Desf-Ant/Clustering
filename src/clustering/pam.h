#ifndef PAM_H
#define PAM_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/donnees.h"
#include <vector>

class PAM
{
    private :
        std::vector<Sommet>* lesDonnees;
        Donnees* donnees;
        unsigned int nb_classes;
        Distance distance;

        std::vector<unsigned int> centroids;
        std::vector<double> sommes_distances;

    public :
        PAM ( Donnees* d, unsigned int n, type_dist t );
        void execute ( void );

    private :
        void initialise ( void );
        double attribueClasse ( unsigned int max_classes );
        bool selectionneMeilleurRemplacant ( unsigned int a_remplacer );
};

#endif // PAM_H
