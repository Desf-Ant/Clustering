#ifndef ACP_H
#define ACP_H

#include "../core/sommet.h"
#include "../core/donnees.h"

class ACP
{
    private :
        Donnees* lesDonneesOriginales;
        std::vector<Sommet> lesDonnees;

    public:
        ACP (Donnees* data);
        void execute (void);


    private :
        void centreDonnees (void);
        void genere_matrice_covariance (void);
        void extraction_vecteurs_propres (void);
};

#endif // ACP_H
