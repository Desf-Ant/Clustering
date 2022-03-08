#ifndef HIERARCHICAL_H
#define HIERARCHICAL_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/donnees.h"

class Hierarchical
{
    private :
        Donnees* donnees;
        std::vector<Sommet>* lesDonnees;
        unsigned int nb_classes_objectif;
        unsigned int nb_classes_courantes;
        unsigned int nb_classes_depart;
        type_dist type_distance;

        std::vector < Sommet > centroids;
        std::vector < unsigned int > nb_sommets_par_classes;
        std::vector < std::vector<Sommet*> > liste_sommets_par_classe;

        unsigned int classeA;
        unsigned int classeB;

    public:
        Hierarchical ( Donnees* d, unsigned int n, type_dist t );
        void execute ( void );

    private :
        void initialise ( void );
        void calculeClasseAFusionner ( void );
        void fusionne ( void );
        void calculeCentroid ( unsigned int n );
        void appliqueClasses ( void );
};

#endif // KMEANS_H
