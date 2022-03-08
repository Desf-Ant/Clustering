#include "pam.h"

PAM::PAM ( Donnees* d, unsigned int n, type_dist t )
{
    this->donnees = d;
    this->nb_classes = n;
    this->distance = Distance(t);
}

void PAM::execute ( void )
{
    this->initialise();
}

void PAM::initialise ( void )
{

}

double PAM::attribueClasse ( unsigned int max_classes )
{
    return 0.0;
}

bool PAM::selectionneMeilleurRemplacant ( unsigned int a_remplacer )
{
    return false;
}


