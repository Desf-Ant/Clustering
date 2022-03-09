#include "Note.h"

Note::Note()
{
    this->dimensions = std::vector < double >() ;
    this->classe = -1;
}

Note::Note(std::vector<double> dimensions) {
    this->dimensions = dimensions;
    this->classe = -1;
}

int Note::getClasse() const {
    return this->classe;
}

int Note::getSizeDimension() const {
    return this->dimensions.size();
}

double Note::getCoeffAt(int index) const {
    if (index < 0 || index >= this->getSizeDimension())
        return -1;
    return this->dimensions.at(index);
}

void Note::setClasse(int n) {
    this->classe = n;
}

void Note::ajoute(const Note &autre) {
    if (this->getSizeDimension() != autre.getSizeDimension())
        return;
    for (int i=0; i<this->getSizeDimension(); i++)
        this->dimensions.at(i) += autre.getCoeffAt(i);
}

void Note::affiche() const {
    for (int i=0; i<this->getSizeDimension(); i++) {
        std::cout << this->getCoeffAt(i) << " | ";
    }
    std::cout << "classe -> " << this->classe << std::endl;
}

Note Note::random(int n) {
    std::vector < double > noteListe = std::vector < double >();
    for (int i=0; i<n; i++) {
        noteListe.push_back(rand()%20);
    }
    return Note(noteListe);
}
