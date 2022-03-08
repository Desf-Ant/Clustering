#include "dbscan.h"

DBSCAN::DBSCAN ( Donnees* d, type_dist t )
{
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->type_distance = t;
    this->distance = Distance(this->type_distance);
    this->nb_points_minimum = this->lesDonnees->size()/15;
    this->distance_maximum = 50;
    this->classe_courante = 0;

    for (int i=0;i<(int)this->lesDonnees->size();i++)
        deja_visites.push_back(false);

}

void DBSCAN::execute ( void )
{
    for (int i=0; i<(int)this->deja_visites.size();i++){
        if (!this->deja_visites.at(i)){
            this->calculVoisinage(i);
            if (this->voisinage_courant.size() >= this->nb_points_minimum ) {
                this->a_ajouter_au_cluster.push_back(i);
                for (int j=0; j<(int)this->voisinage_courant.size(); j++) {
                    this->a_ajouter_au_cluster.push_back(this->voisinage_courant.at(j));
                }
                this->voisinage_courant.clear();
                this->etendCluster(i);
                this->classe_courante++;
            } else {
                this->lesDonnees->at(i).setClasse(-1);
            }
        }
    }
//    for (int i=0; i<(int)this->deja_visites.size();i++)
//        std::cout << this->lesDonnees->at(i).getClasse() << " ";
//    std::cout << std::endl;
}

void DBSCAN::calculVoisinage ( unsigned int indice )
{
    this->voisinage_courant.clear();
    for (int i=0; i<(int)this->deja_visites.size();i++) {
        if (i == (int)indice)
            continue;
        if (this->distance.calcul(this->lesDonnees->at(indice), this->lesDonnees->at(i)) < this->distance_maximum)
            this->voisinage_courant.push_back(i);
    }
}

void DBSCAN::etendCluster ( unsigned int indice )
{
    this->lesDonnees->at(indice).setClasse(this->classe_courante);
    for (int i=0;i<(int)this->a_ajouter_au_cluster.size(); i++) {
        if (!this->deja_visites.at(this->a_ajouter_au_cluster.at(i))) {
            this->deja_visites.at(this->a_ajouter_au_cluster.at(i)) = true;
            this->calculVoisinage(this->a_ajouter_au_cluster.at(i));
            this->lesDonnees->at(this->a_ajouter_au_cluster.at(i)).setClasse(this->classe_courante);
            if (this->voisinage_courant.size() >= this->nb_points_minimum) {
                for (int j=0;j<(int)this->voisinage_courant.size();j++) {
                    this->a_ajouter_au_cluster.push_back(this->voisinage_courant.at(j));
                }
            }
            this->voisinage_courant.clear();
        }
    }
}
