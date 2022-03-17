#include "acpNotes.h"

ACPNotes::ACPNotes (Notes* data){
    this->lesDonneesOriginales = data;
    this->lesDonnees = *(data->getDonnees());
}

void ACPNotes::execute (void){
    this->centreDonnees();
    this->genere_matrice_covariance();
    this->extraction_vecteurs_propres();
}

void ACPNotes::centreDonnees (void){
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

void ACPNotes::genere_matrice_covariance (void){
    Matrice* matrice = new Matrice(this->lesDonnees.size(), this->lesDonnees.at(0).getSizeDimension());
    for (int i=0; i<(int)matrice->getNbLignes(); i++)
        for (int j=0; j<(int)matrice->getNbColonnes();j++)
            matrice->setCoeff(i,j,this->lesDonneesOriginales->getNoteAt(i).getCoeffAt(j));

    Matrice* transpose = new Matrice(matrice->getTranspose());
    matrice = new Matrice((*transpose)* (*matrice));
    this->covariance = matrice;
}

void ACPNotes::extraction_vecteurs_propres (void){
    std::cout << "ACP: " << std::endl;
    this->covariance->eigenAnalysis();
    for ( unsigned int i = 0 ; i < covariance->getNbLignes() ; i++ )
    {
        Vecteur produit = covariance->getValeurPropre(i) * covariance->getVecteurPropre(i);
        Vecteur transfo = *covariance * covariance->getVecteurPropre(i);

        std::cout << "(vecteur) " << covariance->getValeurPropre(i) << " -> ";
        covariance->getVecteurPropre(i).affiche();
        std::cout << "(produit) " << covariance->getValeurPropre(i) << " -> ";
        produit.affiche();
        std::cout << "(transfo) " <<  covariance->getValeurPropre(i) << " -> ";
        transfo.affiche();
        std::cout << std::endl;
    }
}


