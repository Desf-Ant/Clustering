#ifndef ACP_H
#define ACP_H

#include "../core/sommet.h"
#include "../core/donnees.h"
#include "../matrice/matrice.h"
#include "../matrice/vecteur.h"

class ACP
{
    private :
        Donnees* lesDonneesOriginales;
        std::vector<Sommet> lesDonnees;
        Matrice* covariance;

    public:
        ACP (Donnees* data);
        void execute (void);


    private :
        void centreDonnees (void);
        void genere_matrice_covariance (void);
        void extraction_vecteurs_propres (void);
};

#endif // ACP_H
