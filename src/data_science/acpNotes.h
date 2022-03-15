#ifndef ACPNOTES_H
#define ACPNOTES_H

#include "../core/note.h"
#include "../core/notes.h"
#include "../matrice/matrice.h"
#include "../matrice/vecteur.h"

class ACPNotes
{
    private :
        Notes* lesDonneesOriginales;
        std::vector<Note> lesDonnees;

    public:
        ACPNotes (Notes* data);
        void execute (void);


    private :
        void centreDonnees (void);
        void genere_matrice_covariance (void);
        void extraction_vecteurs_propres (void);
};

#endif // ACPNOTES_H
