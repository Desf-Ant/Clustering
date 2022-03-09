#ifndef KMEDIANNOTES_H
#define KMEDIANNOTES_H

#include "../core/distance.h"
#include "../core/notes.h"
#include "../core/note.h"

class KmedianNotes
{
    private :
        Notes* donnees;
        std::vector<Note>* lesDonnees;
        unsigned int nb_classes;
        Distance distance;

        std::vector<Note> graines;
        std::vector < std::vector< std::vector < int > > > listesCoords;
        std::vector<int> nb_sommets_par_classe;

    public:
        KmedianNotes ( Notes* d, unsigned int n, type_dist t );
        void execute ( void );

    private :
        void initialise ( void );
        void attribueClasse ( void );
        bool calculNouvelleGraines ( void );
};

#endif // KMEDIANNOTES_H
