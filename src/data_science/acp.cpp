#include "acp.h"

ACP::ACP (Notes* data){
    this->lesDonneesOriginales = data;
    this->lesDonnees = *(data->getDonnees());
}

void ACP::execute (void){
    this->centreDonnees();
}

void ACP::centreDonnees (void){
    // calcul du centroid
    std::vector<double> zeros = std::vector<double>();
    for (int i=0; i<(int)this->lesDonnees.at(0).getSizeDimension();i++)
        zeros.push_back(0);
    Note centroid = Note (zeros);

    for (int i=0; i<(int)this->lesDonnees.size();i++)
        centroid.ajoute(this->lesDonnees.at(i));

    for (int i=0; i<(int)this->lesDonnees.at(0).getSizeDimension();i++)
        zeros.at(i) = centroid.getCoeffAt(i) / this->lesDonnees.size() ;

    centroid = Note(zeros);
    std::cout << "centroids" <<std::endl;
    centroid.affiche();

    //translation de toutes les données par l'opposé du centroid
    std::vector<double> invertCoords = std::vector<double>();
    for (int i=0; i<(int)centroid.getSizeDimension();i++)
        invertCoords.push_back(-centroid.getCoeffAt(i));
    Note invertCentroid = Note (invertCoords);
    for (int i=0; i<(int)this->lesDonnees.size();i++)
        this->lesDonnees.at(i).setTranslation(invertCentroid);


    std::vector<double> zeross = std::vector<double>();
    for (int i=0; i<(int)this->lesDonnees.at(0).getSizeDimension();i++)
        zeross.push_back(0);
    Note centroidd = Note (zeross);

    for (int i=0; i<(int)this->lesDonnees.size();i++)
        centroidd.ajoute(this->lesDonnees.at(i));

    for (int i=0; i<(int)this->lesDonnees.at(0).getSizeDimension();i++)
        zeross.at(i) = centroidd.getCoeffAt(i) / this->lesDonnees.size() ;

    centroidd = Note(zeross);
    std::cout << "centroids" <<std::endl;
    centroidd.affiche();

}

void ACP::genere_matrice_covariance (void){

}

void ACP::extraction_vecteurs_propres (void){

}


