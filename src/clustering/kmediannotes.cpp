#include "kmediannotes.h"

KmedianNotes::KmedianNotes( Notes* d, unsigned int n, type_dist t )
{
    assert ( nb_classes > 0 );
    this->donnees = d;
    this->lesDonnees = d->getDonnees();
    this->nb_classes = n;
    this->distance = Distance ( t );

    this->graines = std::vector<Note>();
    this->nb_sommets_par_classe = std::vector<int>();
}

void KmedianNotes::initialise ( void )
{
    this->graines.clear();
    this->nb_sommets_par_classe.clear();

    for (int i=0; i<this->lesDonnees->at(0).getSizeDimension();i++)
        this->listesCoords.push_back(std::vector<std::vector<int>>());

    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->graines.push_back(Note::random(this->donnees->getDonnees()->at(0).getSizeDimension()));
        this->nb_sommets_par_classe.push_back(0);
        for (int j=0;j<this->lesDonnees->at(0).getSizeDimension();j++)
            this->listesCoords.at(j).push_back(std::vector<int>());
    }
}

void KmedianNotes::execute ( void )
{
    this->lesDonnees = this->donnees->getDonnees();
//    this->donnees->getGraines()->clear();
    this->initialise();

    do {
        this->attribueClasse();
    }while (this->calculNouvelleGraines());

    for (int i = 0; i<(int)this->graines.size(); i++) {
        this->graines.at(i).setClasse(i);
//        this->donnees->getGraines()->push_back(this->graines.at(i));
    }
}

void KmedianNotes::attribueClasse ( void )
{
    for (int i = 0; i< (int)this->nb_classes;i++) {
        this->nb_sommets_par_classe.at(i)=0;

    for (int i=0; i<this->lesDonnees->at(0).getSizeDimension();i++)
        for (int j=0; j< (int)this->nb_classes;j++)
            this->listesCoords.at(i).at(j).clear();
    }
    std::vector<double> d;
    for (int i=0; i<(int)this->lesDonnees->size(); i++) {
        d.clear();
        for (int j = 0; j<(int)this->graines.size(); j++) {
            d.push_back(this->distance.calculNote(this->lesDonnees->at(i), this->graines.at(j)));
        }
        std::vector<double>::iterator result = std::min_element(std::begin(d), std::end(d));
        int clas = std::distance(std::begin(d), result);
        this->nb_sommets_par_classe.at(clas) += 1;
        this->lesDonnees->at(i).setClasse(clas);
        for (int j=0; j<this->lesDonnees->at(0).getSizeDimension();j++)
            this->listesCoords.at(j).at(clas).push_back(this->lesDonnees->at(i).getCoeffAt(j));
    }
}

bool KmedianNotes::calculNouvelleGraines ( void )
{
    bool majs = false;
    for (int i=0; i<(int)this->nb_classes; i++) {
        if (this->nb_sommets_par_classe.at(i) > 0) {
            Note oldSeed = Note(this->graines.at(i));
            for (int j=0; j<this->lesDonnees->at(0).getSizeDimension();j++)
                std::sort(this->listesCoords.at(j).at(i).begin(), this->listesCoords.at(j).at(i).end());

            int indexCentre = this->listesCoords.at(0).at(i).size() / 2;
            std::vector< double > centerCoords = std::vector < double > ();
            for (int j=0; j<this->lesDonnees->at(0).getSizeDimension();j++)
                centerCoords.push_back(this->listesCoords.at(j).at(i).at(indexCentre));

            this->graines.at(i) = Note(centerCoords);

            if (this->distance.calculNote(this->graines.at(i), oldSeed)>Distance::EPSILON) {
                majs = true;
            }
        }
    }
    return majs;
}
