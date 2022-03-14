#ifndef ACP_H
#define ACP_H

#include "../core/note.h"
#include "../core/notes.h"

class ACP
{
    private :
        Notes* lesDonneesOriginales;
        std::vector<Note> lesDonnees;

    public:
        ACP (Notes* data);
        void execute (void);


    private :
        void centreDonnees (void);
        void genere_matrice_covariance (void);
        void extraction_vecteurs_propres (void);
};

#endif // ACP_H
