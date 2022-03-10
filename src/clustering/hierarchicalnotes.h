#ifndef HIERARCHICALNOTES_H
#define HIERARCHICALNOTES_H

#include "../core/distance.h"
#include "../core/note.h"
#include "../core/notes.h"

class HierarchicalNotes
{
private :
    Notes* donnees;
    std::vector<Note>* lesDonnees;
    unsigned int nb_classes_objectif;
    unsigned int nb_classes_courantes;
    unsigned int nb_classes_depart;
    type_dist type_distance;

    std::vector < Note > centroids;
    std::vector < unsigned int > nb_sommets_par_classes;
    std::vector < std::vector<Note*> > liste_sommets_par_classe;

    unsigned int classeA;
    unsigned int classeB;

public:
    HierarchicalNotes ( Notes* d, unsigned int n, type_dist t );
    void execute ( void );

private :
    void initialise ( void );
    void calculeClasseAFusionner ( void );
    void fusionne ( void );
    void calculeCentroid ( unsigned int n );
    void appliqueClasses ( void );
};

#endif // HIERARCHICALNOTES_H
