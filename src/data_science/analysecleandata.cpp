#include "analysecleandata.h"

AnalyseCleanData::AnalyseCleanData(Notes* data)
{
    this->donnees = data;

    Note n = data->getDonnees()->at(0);
    this->lesDonnees = data->getDonnees();
}

std::vector < Note >* AnalyseCleanData::execute () {
    std::cout << "taille de la base de données avant le nettoyage (" << this->lesDonnees->size() << " x " << this->lesDonnees->at(0).getSizeDimension() << ")" << std::endl << std::endl;
    this->cleanData();
    this->ligneVariance();
    this->colonneVariance();
    std::cout << "taille de la base de données apres le nettoyage (" << this->lesDonnees->size() << " x " << this->lesDonnees->at(0).getSizeDimension() << ")" << std::endl << std::endl;
    return this->lesDonnees;
}

void AnalyseCleanData::ligneVariance() {
    std::vector < int > indexFaibleVariance;
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
            indexFaibleVariance.push_back(i);
            std::cout << "l'élève a l'index " << i << " a variance de " << variance << " ce n'est pas suffisant" << std::endl;
        }
    }

    std::sort(indexFaibleVariance.begin(), indexFaibleVariance.end(), std::greater<int>());
    for (int i=0; i<(int)indexFaibleVariance.size(); i++) {
        this->removeLine(indexFaibleVariance.at(i));
    }
}

void AnalyseCleanData::colonneVariance() {
    std::vector < int > indexFaibleVariance;
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

        if (variance <= 2.5) {
            indexFaibleVariance.push_back(j);
            std::cout << "la matière a l'index " << j << " a variance de " << variance << " ce n'est pas suffisant" << std::endl;
        }
    }

    std::sort(indexFaibleVariance.begin(), indexFaibleVariance.end(), std::greater<int>());
    for (int i=0; i<(int)indexFaibleVariance.size(); i++) {
        this->removeColonne(indexFaibleVariance.at(i));
    }
}

void AnalyseCleanData::removeLine(int n) {
    std::vector < Note >* newLesDonnees = new std::vector < Note >;
    for (int i=0; i<(int)this->lesDonnees->size(); i++)
        if (i != n)
            newLesDonnees->push_back(this->lesDonnees->at(i));
    this->lesDonnees = newLesDonnees;
}

void AnalyseCleanData::removeColonne(int n) {
    for (int i=0; i<(int)this->lesDonnees->size(); i++)
        this->lesDonnees->at(i).removeCoeff(n);
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
       this->removeLine(indexSupp.at(i));
}
