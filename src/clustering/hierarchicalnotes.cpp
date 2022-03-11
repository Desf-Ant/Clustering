#include "hierarchicalnotes.h"

HierarchicalNotes::HierarchicalNotes ( Notes* d, unsigned int n, type_dist t )
{
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes_objectif = n;
    this->nb_classes_depart = this->lesDonnees->size();
    this->nb_classes_courantes = this->lesDonnees->size();
    this->type_distance = t;
    this->centroids = std::vector<Note>();
    this->classeA = 0;
    this->classeB = 1;
}

void HierarchicalNotes::execute() {
//    this->donnees->getGraines()->clear();
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
//            this->donnees->getGraines()->push_back(this->centroids.at(i));
            for (int j=0; j<(int)this->liste_sommets_par_classe.at(i).size();j++) {
                this->liste_sommets_par_classe.at(i).at(j)->setClasse(cl);
            }
            cl++;
        }
    }
}

void HierarchicalNotes::initialise ( void )
{
    this->centroids.clear();
    for (int i=0;i<(int)this->lesDonnees->size();i++) {
        this->lesDonnees->at(i).setClasse(i);
        this->nb_sommets_par_classes.push_back(1);
        std::vector<Note*> vec;
        vec.push_back(&(this->lesDonnees->at(i)));
        this->liste_sommets_par_classe.push_back(vec);
        this->centroids.push_back(Note(this->lesDonnees->at(i)));
    }
}

void HierarchicalNotes::calculeClasseAFusionner ( void )
{
    double inertie = 9999999;
    Distance dist = Distance(this->type_distance);
    for (int i=0; i<(int)this->liste_sommets_par_classe.size()-1;i++){
        if (this->nb_sommets_par_classes.at(i) > 0) {
            for (int j=i+1; j<(int)this->liste_sommets_par_classe.size();j++) {
                if (this->nb_sommets_par_classes.at(j) > 0) {
                    int n1 = nb_sommets_par_classes.at(i);
                    int n2 = nb_sommets_par_classes.at(j);
                    double calcule = (n1*n2*dist.calculNote(this->centroids.at(i),this->centroids.at(j)))/(n1+n2);
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

void HierarchicalNotes::fusionne ( void )
{
    for (int i=0; i<(int)this->liste_sommets_par_classe.at(classeB).size(); i++) {
        this->liste_sommets_par_classe.at(classeA).push_back(liste_sommets_par_classe.at(classeB).at(i));
    }
    this->liste_sommets_par_classe.at(classeB).clear();
    this->nb_sommets_par_classes.at(classeA) += this->nb_sommets_par_classes.at(classeB);
    this->nb_sommets_par_classes.at(classeB) = 0;
    this->nb_classes_courantes -= 1;
}

void HierarchicalNotes::calculeCentroid ( unsigned int n ) {
    std::vector<double> zeros = std::vector<double>();
    for (int i=0; i<this->lesDonnees->at(0).getSizeDimension();i++)
        zeros.push_back(0);
    Note centro = Note(zeros);
    for (int i=0; i<(int)this->liste_sommets_par_classe.at(n).size();i++){
        centro.ajoute(*(this->liste_sommets_par_classe.at(n).at(i)));
    }
    std::vector < double > coords = std::vector < double > ();
    for (int i=0; i<this->lesDonnees->at(0).getSizeDimension(); i++)
        coords.push_back(centro.getCoeffAt(i)/this->nb_sommets_par_classes.at(n));
    centro = Note(coords);
    this->centroids.at(n) = centro;
}

void HierarchicalNotes::appliqueClasses ( void )
{
    for (int i=0; i<(int)this->liste_sommets_par_classe.size(); i++) {
        for (int j=0; j<(int)this->liste_sommets_par_classe.at(i).size();j++){
            this->liste_sommets_par_classe.at(i).at(j)->setClasse(i);
        }
    }
}

