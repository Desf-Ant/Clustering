#include "kmeannotes.h"

KmeanNotes::KmeanNotes ( Notes* d, unsigned int n, type_dist t )
{
    assert ( n > 0 );
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes = n;
    this->distance = Distance ( t );

    this->graines = std::vector<Note>();
    this->centroids = std::vector<Note>();
    this->nb_sommets_par_classe = std::vector<int>();
}

void KmeanNotes::execute ( void )
{
    this->lesDonnees = this->donnees->getDonnees();
    this->initialise();

    do {
        this->attribueClasse();
    }while (this->calculNouvelleGraines());

    for (int i = 0; i<(int)this->graines.size(); i++) {
        this->graines.at(i).setClasse(i);
    }
}

void KmeanNotes::initialise ( void )
{
    this->graines.clear();
    this->centroids.clear();
    this->nb_sommets_par_classe.clear();
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->graines.push_back(Note::random(15));
        std::vector<double> zeros = std::vector<double>();
        for (int i=0; i<this->lesDonnees->at(0).getSizeDimension();i++)
            zeros.push_back(0);
        this->centroids.push_back(Note(std::vector<double>(zeros)));
        this->nb_sommets_par_classe.push_back(0);
    }
}

void KmeanNotes::attribueClasse ( void )
{
    for (int i = 0; i< (int)this->nb_classes;i++) {
        std::vector<double> zeros = std::vector<double>();
        for (int i=0; i<this->lesDonnees->at(0).getSizeDimension();i++)
            zeros.push_back(0);
        this->centroids.at(i)=Note(std::vector<double>(zeros));
        this->nb_sommets_par_classe.at(i)=0;
    }
    std::vector<double> d;
    for (int i=0; i<(int)this->lesDonnees->size(); i++) {
        d.clear();
        for (int j = 0; j<(int)this->graines.size(); j++) {
            d.push_back(this->distance.calculNote(this->donnees->getNoteAt(i), this->graines.at(j)));
        }
        std::vector<double>::iterator result = std::min_element(std::begin(d), std::end(d));
        this->lesDonnees->at(i).setClasse(std::distance(std::begin(d), result));
        this->nb_sommets_par_classe.at(std::distance(std::begin(d), result)) += 1;
        this->centroids.at(std::distance(std::begin(d), result)).ajoute(this->lesDonnees->at(i));
    }
}

bool KmeanNotes::calculNouvelleGraines ( void )
{
    bool majs = false;
    for (int i=0; i<(int)this->nb_classes; i++) {
        if (this->nb_sommets_par_classe.at(i) > 0) {
            std::vector < double > listeCoeff = std::vector < double >();
            for (int j=0; j<this->centroids.at(i).getSizeDimension();j++)
                listeCoeff.push_back(this->centroids.at(i).getCoeffAt(j)/this->nb_sommets_par_classe.at(i));
            this->centroids.at(i) = Note(listeCoeff);
            if (this->distance.calculNote(this->graines.at(i), this->centroids.at(i))>Distance::EPSILON) {
                this->graines.at(i) = Note(this->centroids.at(i));
                majs = true;
            }
        }
    }
    return majs;
}
