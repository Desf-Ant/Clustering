#include "kmeans.h"

Kmeans::Kmeans ( Donnees* d, unsigned int n, type_dist t )
{
    assert ( nb_classes > 0 );
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes = n;
    this->distance = Distance ( t );

    this->graines = std::vector<Sommet>();
    this->centroids = std::vector<Sommet>();
    this->nb_sommets_par_classe = std::vector<int>();
}

void Kmeans::execute ( void )
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

void Kmeans::initialise ( void )
{
    this->graines.clear();
    this->centroids.clear();
    this->nb_sommets_par_classe.clear();
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->graines.push_back(Sommet::random3D());
        this->centroids.push_back(Sommet(0,0,0));
        this->nb_sommets_par_classe.push_back(0);
    }
}

void Kmeans::attribueClasse ( void )
{
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->centroids.at(i)=Sommet(0,0,0);
        this->nb_sommets_par_classe.at(i)=0;
    }
    std::vector<double> d;
    for (int i=0; i<(int)this->lesDonnees->size(); i++) {
        d.clear();
        for (int j = 0; j<(int)this->graines.size(); j++) {
            d.push_back(this->distance.calcul(this->lesDonnees->at(i), this->graines.at(j)));
        }
        std::vector<double>::iterator result = std::min_element(std::begin(d), std::end(d));
        this->lesDonnees->at(i).setClasse(std::distance(std::begin(d), result));
        this->nb_sommets_par_classe.at(std::distance(std::begin(d), result)) += 1;
        this->centroids.at(std::distance(std::begin(d), result)).ajoute(this->lesDonnees->at(i));
    }
}

bool Kmeans::calculNouvelleGraines ( void )
{
    bool majs = false;
    for (int i=0; i<(int)this->nb_classes; i++) {
        if (this->nb_sommets_par_classe.at(i) > 0) {
            this->centroids.at(i) = Sommet(this->centroids.at(i).getX()/this->nb_sommets_par_classe.at(i),this->centroids.at(i).getY()/this->nb_sommets_par_classe.at(i),this->centroids.at(i).getZ()/this->nb_sommets_par_classe.at(i));
            if (this->distance.calcul(this->graines.at(i), this->centroids.at(i))>Distance::EPSILON) {
                this->graines.at(i) = Sommet(this->centroids.at(i));
                majs = true;
            }
        }
    }
    return majs;

}
