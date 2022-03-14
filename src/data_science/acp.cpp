#include "acp.h"

ACP::ACP (Notes* data){
    this->lesDonneesOriginales = data;
    this->lesDonnees = *(data->getDonnees());
}

void ACP::execute (void){
    this->centreDonnees();
    this->genere_matrice_covariance();
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
}

void ACP::genere_matrice_covariance (void){
    Matrice matrice = Matrice(this->lesDonnees.size(), this->lesDonnees.at(0).getSizeDimension());
    for (int i=0; i<(int)matrice.getNbLignes(); i++)
        for (int j=0; j<(int)matrice.getNbColonnes();j++)
            matrice.setCoeff(i,j,this->lesDonneesOriginales->getNoteAt(i).getCoeffAt(j));

   matrice.affiche();
   Matrice transpose = matrice.getTranspose();
   matrice = matrice * transpose;
}

void ACP::extraction_vecteurs_propres (void){

}


