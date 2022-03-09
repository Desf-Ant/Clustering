#ifndef KMEANNOTES_H
#define KMEANNOTES_H

#include "../core/distance.h"
#include "../core/sommet.h"
#include "../core/notes.h"

class KmeanNotes
{
private :
    Notes* donnees;
    std::vector<Note>* lesDonnees;
    unsigned int nb_classes;
    Distance distance;

    std::vector<Note> graines;
    std::vector<Note> centroids;
    std::vector<int> nb_sommets_par_classe;

public:
    KmeanNotes ( Notes* d, unsigned int n, type_dist t );
    void execute ( void );

private :
    void initialise ( void );
    void attribueClasse ( void );
    bool calculNouvelleGraines ( void );
};

#endif // KMEANNOTES_H
