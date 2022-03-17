#include "analysecleandata.h"

AnalyseCleanData::AnalyseCleanData(Notes* data)
{
    this->donnees = data;

    Note n = data->getDonnees()->at(0);
    this->lesDonnees = data->getDonnees();
}

std::vector < Note >* AnalyseCleanData::execute () {
    this->cleanData();
    this->ligneVariance();
    this->colonneVariance();
    std::cout << "taille apres clean " << this->lesDonnees->size() << std::endl;
    return this->lesDonnees;
}

void AnalyseCleanData::ligneVariance() {
    std::vector < int > faibleVariance;
    for (int i=0; i<(int)this->lesDonnees->size();i++) {
        double variance = 0;
        double moyenne = 0;

        // calcul de la moyenne
        for (int j=0; j<(int)this->lesDonnees->at(i).getSizeDimension();j++)
            moyenne += this->lesDonnees->at(i).getCoeffAt(j);
        moyenne /= this->lesDonnees->at(i).getSizeDimension();

        // calcul de la variance
        for (int j=0; j<(int)this->lesDonnees->at(i).getSizeDimension();j++) {
            variance += pow(this->lesDonnees->at(i).getCoeffAt(j) - moyenne,2);
        }
        variance /= this->lesDonnees->at(i).getSizeDimension();

        if (variance <= 1.5) {
            faibleVariance.push_back(i);
            std::cout << "l'élève a l'index " << i << " a variance de " << variance << " ce n'est pas suffisant" << std::endl;
        }
    }

    std::sort(faibleVariance.begin(), faibleVariance.end(), std::greater<int>());
    for (int i=0; i<(int)faibleVariance.size(); i++) {
        std::cout << " variance index ligne " << faibleVariance.at(i) << std::endl;
        this->removeLine(faibleVariance.at(i));
    }
}

void AnalyseCleanData::colonneVariance() {
    std::vector < int > faibleVariance;
    for (int j=0; j<(int)this->lesDonnees->at(0).getSizeDimension();j++) {
        double variance = 0;
        double moyenne = 0;

        // calcul de la moyenne
        for (int i=0; i<(int)this->lesDonnees->size();i++)
            moyenne += this->lesDonnees->at(i).getCoeffAt(j);
        moyenne /= this->lesDonnees->size();

        // calcul de la variance
        for (int i=0; i<(int)this->lesDonnees->size();i++) {
            variance += pow(this->lesDonnees->at(i).getCoeffAt(j) - moyenne,2);
        }
        variance /= this->lesDonnees->size();

        if (variance <= 3) {
            faibleVariance.push_back(j);
            std::cout << "la moyenne a l'index " << j << " a variance de " << variance << " ce n'est pas suffisant" << std::endl;
        }
    }

//    std::sort(faibleVariance.begin(), faibleVariance.end(), std::greater<int>());
//    for (int i=0; i<(int)faibleVariance.size(); i++) {
//        std::cout << " variance index colonne " << faibleVariance.at(i) << std::endl;
//        this->removeLine(faibleVariance.at(i));
//    }
}

void AnalyseCleanData::removeLine(int n) {
//    std::vector<Note>::iterator it = this->lesDonnees->begin();
//    std::advance(it, n*sizeof (Note));
//    this->lesDonnees->erase(it);
    this->lesDonnees->erase(std::find(this->lesDonnees->begin(), this->lesDonnees->end(), (Note)this->lesDonnees->at(n)));
}

void AnalyseCleanData::cleanData() {
    std::vector < int > indexSupp ;
    for (int i=0; i<(int)this->lesDonnees->size();i++) {
        for (int j=0;j<(int)this->lesDonnees->at(i).getSizeDimension();j++) {
            if (this->lesDonnees->at(i).getCoeffAt(j) == -2) {
                indexSupp.push_back(i);
                break;
            }
        }
    }

    std::sort(indexSupp.begin(), indexSupp.end(), std::greater<int>());

    for (int i=0; i<(int)indexSupp.size();i++)
       this->removeLine(i);
}
