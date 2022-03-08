#include "kmedians.h"

Kmedians::Kmedians ( Donnees* d, unsigned int n, type_dist t )
{
    assert ( nb_classes > 0 );
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes = n;
    this->distance = Distance ( t );

    this->graines = std::vector<Sommet>();
    this->nb_sommets_par_classe = std::vector<int>();
}

void Kmedians::execute ( void )
{
    this->lesDonnees = this->donnees->getDonnees();
    this->donnees->getGraines()->clear();
    this->initialise();

    do {
        this->attribueClasse();
    }while (this->calculNouvelleGraines());

    for (int i = 0; i<(int)this->graines.size(); i++) {
        this->graines.at(i).setClasse(i);
        this->donnees->getGraines()->push_back(this->graines.at(i));
    }
}

void Kmedians::initialise ( void )
{
    this->graines.clear();
    this->nb_sommets_par_classe.clear();
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->graines.push_back(Sommet::random3D());
        this->nb_sommets_par_classe.push_back(0);
        this->listesX.push_back(std::vector<int>());
        this->listesY.push_back(std::vector<int>());
        this->listesZ.push_back(std::vector<int>());
    }
}

void Kmedians::attribueClasse ( void )
{
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->nb_sommets_par_classe.at(i)=0;
        this->listesX.at(i).clear();
        this->listesY.at(i).clear();
        this->listesZ.at(i).clear();
    }
    std::vector<double> d;
    for (int i=0; i<(int)this->lesDonnees->size(); i++) {
        d.clear();
        for (int j = 0; j<(int)this->graines.size(); j++) {
            d.push_back(this->distance.calcul(this->lesDonnees->at(i), this->graines.at(j)));
        }
        std::vector<double>::iterator result = std::min_element(std::begin(d), std::end(d));
        int clas = std::distance(std::begin(d), result);
        this->nb_sommets_par_classe.at(clas) += 1;
        this->lesDonnees->at(i).setClasse(clas);
        this->listesX.at(clas).push_back(this->lesDonnees->at(i).getX());
        this->listesY.at(clas).push_back(this->lesDonnees->at(i).getY());
        this->listesZ.at(clas).push_back(this->lesDonnees->at(i).getZ());
    }
}

bool Kmedians::calculNouvelleGraines ( void )
{
    bool majs = false;
    for (int i=0; i<(int)this->nb_classes; i++) {
        if (this->nb_sommets_par_classe.at(i) > 0) {
            Sommet oldSeed = Sommet(this->graines.at(i));
            std::sort(this->listesX.at(i).begin(), this->listesX.at(i).end());
            std::sort(this->listesY.at(i).begin(), this->listesY.at(i).end());
            std::sort(this->listesZ.at(i).begin(), this->listesZ.at(i).end());
            int center = this->listesX.at(i).size() / 2;

            this->graines.at(i) = Sommet(this->listesX.at(i).at(center), this->listesY.at(i).at(center), this->listesZ.at(i).at(center));

            if (this->distance.calcul(this->graines.at(i), oldSeed)>Distance::EPSILON) {
                majs = true;
            }
        }
    }
    return majs;
}
