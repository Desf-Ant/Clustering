#include "hierarchical.h"

Hierarchical::Hierarchical ( Donnees* d, unsigned int n, type_dist t )
{
    // Bonne visualisation avec une generation de 100
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes_objectif = n;
    this->nb_classes_depart = this->lesDonnees->size();
    this->nb_classes_courantes = this->lesDonnees->size();
    this->type_distance = t;
    this->centroids = std::vector<Sommet>();
    this->classeA = 0;
    this->classeB = 1;
}

void Hierarchical::execute() {
    this->donnees->getGraines()->clear();
    this->initialise();
    while (this->nb_classes_courantes>this->nb_classes_objectif) {
        this->calculeClasseAFusionner();
        this->fusionne();
        this->calculeCentroid(classeA);
        this->appliqueClasses();
    }

    int cl = 0;

    for (int i=0; i<(int)this->nb_sommets_par_classes.size();i++) {
        if (this->nb_sommets_par_classes.at(i) > 0) {
            this->centroids.at(i).setClasse(cl);
            std::cout << this->centroids.at(i).getX() << " " << this->centroids.at(i).getY() << " " << this->centroids.at(i).getZ() << std::endl;
            this->donnees->getGraines()->push_back(this->centroids.at(i));
            for (int j=0; j<(int)this->liste_sommets_par_classe.at(i).size();j++) {
                this->liste_sommets_par_classe.at(i).at(j)->setClasse(cl);
            }
            cl++;
        }
    }
}

void Hierarchical::initialise ( void )
{
    this->centroids.clear();
    for (int i=0;i<(int)this->lesDonnees->size();i++) {
        this->lesDonnees->at(i).setClasse(i);
        this->nb_sommets_par_classes.push_back(1);
        std::vector<Sommet*> vec;
        vec.push_back(&(this->lesDonnees->at(i)));
        this->liste_sommets_par_classe.push_back(vec);
        this->centroids.push_back(Sommet(this->lesDonnees->at(i)));
    }
}

void Hierarchical::calculeClasseAFusionner ( void )
{
    double inertie = 9999999;
    Distance dist = Distance(this->type_distance);
    for (int i=0; i<(int)this->liste_sommets_par_classe.size()-1;i++){
        if (this->nb_sommets_par_classes.at(i) > 0) {
            for (int j=i+1; j<(int)this->liste_sommets_par_classe.size();j++) {
                if (this->nb_sommets_par_classes.at(j) > 0) {
                    int n1 = nb_sommets_par_classes.at(i);
                    int n2 = nb_sommets_par_classes.at(j);
                    double calcule = (n1*n2*dist.calcul(this->centroids.at(i),this->centroids.at(j)))/(n1+n2);
                    if (calcule<inertie) {
                        inertie = calcule;
                        this->classeA = i;
                        this->classeB = j;
                    }
                }
            }
        }
    }
}

void Hierarchical::fusionne ( void )
{
    for (int i=0; i<(int)this->liste_sommets_par_classe.at(classeB).size(); i++) {
        this->liste_sommets_par_classe.at(classeA).push_back(liste_sommets_par_classe.at(classeB).at(i));
    }
    this->liste_sommets_par_classe.at(classeB).clear();
    this->nb_sommets_par_classes.at(classeA) += this->nb_sommets_par_classes.at(classeB);
    this->nb_sommets_par_classes.at(classeB) = 0;
    this->nb_classes_courantes -= 1;
}

void Hierarchical::calculeCentroid ( unsigned int n ) {
    Sommet centro = Sommet(0,0,0);
    for (int i=0; i<(int)this->liste_sommets_par_classe.at(n).size();i++){
        centro.ajoute(*(this->liste_sommets_par_classe.at(n).at(i)));
    }
    centro = Sommet(centro.getX()/this->nb_sommets_par_classes.at(n),centro.getY()/this->nb_sommets_par_classes.at(n),centro.getZ()/this->nb_sommets_par_classes.at(n));
    this->centroids.at(n) = centro;
}

void Hierarchical::appliqueClasses ( void )
{
    for (int i=0; i<(int)this->liste_sommets_par_classe.size(); i++) {
        for (int j=0; j<(int)this->liste_sommets_par_classe.at(i).size();j++){
            this->liste_sommets_par_classe.at(i).at(j)->setClasse(i);
        }
    }
}
