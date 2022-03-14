#ifndef DONNEES_H
#define DONNEES_H

#include "sommet.h"
#include "distance.h"

#include <vector>
#include <assert.h>
#include <iostream>
#include <algorithm>

class Donnees
{
    private :
        std::vector<Sommet>* lesDonnees;
        unsigned int nb_donnees;
        bool deuxD;
        type_dist type;
        std::vector <Sommet>* lesGraines;
    public :
        Donnees();
        ~Donnees();
        std::vector<Sommet>* getGraines ( void ) const;
        std::vector<Sommet>* getDonnees ( void ) const;
        void setNbDonnees ( unsigned int n );
        void setDimension ( bool dD );
        void setTypeDistance ( type_dist t );
        void setGraines (std::vector<Sommet>* graines) ;

        void genere_random     ( void );
        void genere_eparpilles ( void );
        void genere_carre      ( void );
        void genere_rectangle  ( void );
        void genere_disque     ( void );
        void genere_ellipse    ( void );

    private :
        Sommet genereSommet ( void );
};

#endif // DONNEES_H
