#include "acp.h"

ACP::ACP(Donnees* data){
    this->lesDonneesOriginales = data;
    this->lesDonnees = *(data->getDonnees());
}

void ACP::execute (void){
    this->centreDonnees();
    this->genere_matrice_covariance();
}

void ACP::centreDonnees (void){
    // calcul du centroid
    Sommet centroid = Sommet(0,0,0);

    for (int i=0; i<(int)this->lesDonnees.size();i++)
        centroid.ajoute(this->lesDonnees.at(i));
    centroid = Sommet(centroid.getX()/this->lesDonnees.size(), centroid.getY()/this->lesDonnees.size(), centroid.getZ()/this->lesDonnees.size());

    //translation de toutes les données par l'opposé du centroid
    Sommet invertCentroid = Sommet(centroid);
    invertCentroid.setScale(-1,-1,-1);

    for (int i=0; i<(int)this->lesDonnees.size();i++)
        this->lesDonnees.at(i).setTranslation(invertCentroid.getX(), invertCentroid.getY(), invertCentroid.getZ());
}

void ACP::genere_matrice_covariance (void){
    Matrice matrice = Matrice(this->lesDonnees.size(), 3);
    for (int i=0; i<(int)matrice.getNbLignes(); i++) {
        matrice.setCoeff(i,0,this->lesDonneesOriginales->getDonnees()->at(i).getX());
        matrice.setCoeff(i,1,this->lesDonneesOriginales->getDonnees()->at(i).getY());
        matrice.setCoeff(i,2,this->lesDonneesOriginales->getDonnees()->at(i).getZ());
    }

   matrice.affiche();
   Matrice transpose = matrice.getTranspose();
   matrice = matrice * transpose;
}

void ACP::extraction_vecteurs_propres (void){

}
