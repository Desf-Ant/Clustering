#include "matrice.h"

float EPSILON = 0.00001f;

// Constructeur
Matrice::Matrice ( unsigned int size )
{
    this->nb_lignes = size;
    this->nb_colonnes = size;
    this->lesCoeffs = std::vector<double>();
    for ( unsigned int i = 0 ; i < size*size ; i++ )
    {
        this->lesCoeffs.push_back( 0.0 );
    }

    this->eigen_analysis_effectuee = false;
    this->lesValeursPropres = std::vector<double>();
    this->lesVecteursPropres = std::vector< Vecteur >();
}

Matrice::Matrice( unsigned int L, unsigned int C )
{
    this->nb_lignes = L;
    this->nb_colonnes = C;
    this->lesCoeffs = std::vector<double>();
    for ( unsigned int i = 0 ; i < L*C; i++ )
    {
        this->lesCoeffs.push_back( 0.0 );
    }

    this->eigen_analysis_effectuee = false;
    this->lesValeursPropres = std::vector<double>();
    this->lesVecteursPropres = std::vector< Vecteur >();
}

Matrice::Matrice ( const Matrice& M )
{
    this->nb_lignes = M.getNbLignes();
    this->nb_colonnes = M.getNbColonnes();
    this->lesCoeffs = std::vector<double>();
    for ( unsigned int i = 0 ; i < this->nb_lignes ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->nb_colonnes; j++ )
        {
            this->lesCoeffs.push_back( M.getCoeff(i, j) );
        }
    }

    this->eigen_analysis_effectuee = false;
    this->lesValeursPropres = std::vector<double>();
    this->lesVecteursPropres = std::vector< Vecteur >();
}

Matrice::Matrice ( const Vecteur& diagonale )
{
    this->nb_lignes = diagonale.getTaille();
    this->nb_colonnes = diagonale.getTaille();
    this->lesCoeffs = std::vector<double>();
    for ( unsigned int i = 0 ; i < this->nb_lignes ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->nb_colonnes; j++ )
        {
            if ( i == j )   this->lesCoeffs.push_back( diagonale.getCoeff(i) );
            else            this->lesCoeffs.push_back( 0.0 );
        }
    }

    this->eigen_analysis_effectuee = false;
    this->lesValeursPropres = std::vector<double>();
    this->lesVecteursPropres = std::vector< Vecteur >();
}

Matrice::~Matrice()
{
    // Rien
}

Matrice Matrice::identite ( unsigned int size )
{
    Matrice id = Matrice ( size );
    for ( unsigned int i = 0 ; i < size; i++ )
    {
        id.setCoeff( i, i, 1.0 );
    }
    return id;
}

void Matrice::affiche ( void ) const
{
    std::cout << "----------------------------" << std::endl;
    for ( unsigned int i = 0 ; i < this->nb_lignes ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->nb_colonnes ; j++ )
        {
            std::cout << ((int)(100 * this->getCoeff(i, j)))/100.0 << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

// Accesseurs
std::vector<double> Matrice::getCoeffs ( void ) const
{
    return this->lesCoeffs;
}

unsigned int Matrice::getNbLignes ( void ) const
{
    return this->nb_lignes;
}

unsigned int Matrice::getNbColonnes ( void ) const
{
    return this->nb_colonnes;
}

bool Matrice::isSquare( void ) const
{
    return ( this->nb_lignes == this->nb_colonnes );
}

double Matrice::getCoeff ( unsigned int i, unsigned int j ) const
{
    return this->lesCoeffs[i*this->nb_colonnes+j];
}

void Matrice::setCoeff ( unsigned int i, unsigned int j, double val )
{
    this->lesCoeffs[i*this->nb_colonnes+j] = val;
    this->eigen_analysis_effectuee = false;
}

Matrice Matrice::inverse ( void ) const
{
    // Inversion de matrice par la m??thode du pivot de Gauss
    Matrice matrice = Matrice(*this);
    Matrice id = Matrice::identite(this->nb_colonnes);

    // matrice triangle sup??rieur
    for (int i=0; i<(int)matrice.getNbLignes(); i++) {
        double diagM = matrice.getCoeff(i,i);
        for (int j=0; j<(int)matrice.getNbColonnes(); j++) {
            matrice.setCoeff(i,j,matrice.getCoeff(i,j) / diagM);
            id.setCoeff(i,j,id.getCoeff(i,j) / diagM);
        }
        for (int j=i+1; j<(int)matrice.getNbLignes();j++) {
            double coefM = matrice.getCoeff(j,i);
            for (int k=0; k<(int)matrice.getNbColonnes();k++) {
                 matrice.setCoeff(j,k, matrice.getCoeff(j,k)-matrice.getCoeff(i,k)*coefM);
                 id.setCoeff(j,k, id.getCoeff(j,k)-id.getCoeff(i,k)*coefM);
            }
        }
    }
    // matrice triangle inf??rieur
    for (int i=matrice.getNbLignes()-1; i>=0; i--) {
        for (int j=i-1; j>=0;j--) {
            double coefM = matrice.getCoeff(j,i);
            for (int k=matrice.getNbColonnes()-1; k>=0;k--) {
                 matrice.setCoeff(j,k, matrice.getCoeff(j,k)-matrice.getCoeff(i,k)*coefM);
                 id.setCoeff(j,k, id.getCoeff(j,k)-id.getCoeff(i,k)*coefM);
            }
        }
    }
    return id;
}

Vecteur Matrice::powerIteration ( void )
{
    // Power iteration pour le calcul de la plus grande valeur propre
    // M.vect = lambda.vect
    Vecteur v = Vecteur(this->getNbLignes());
    v.setCoeff(0,1);

    Vecteur vold = Vecteur(v);
    for (int i=0; i < 100; i++) {
        v = *this*v;
        v = v.normalise();
        if (v == vold) {
            break;
        }
        vold = Vecteur(v);
    }
    return v;
}

double Matrice::calculValeurPropreAssociee ( Vecteur v )
{
    // Trouve la valeur propre associ??e au vecteur v par division
    Vecteur vect_l = Vecteur(this->getNbLignes());
    double valeur = 0;
    vect_l = (*this)*v;
    for (int i=0; i <(int)v.getTaille(); i++){
//        std::cout<< "calcul : " << vect_l.getCoeff(i)/v.getCoeff(i) << std::endl;
        valeur += vect_l.getCoeff(i)/v.getCoeff(i) ;
        // std::cout << valeur << std::endl;
    }
//    std::cout << "valeur :" << valeur<<std::endl;
//    vect_l.affiche();
//    v.affiche();
//    std::cout << std::endl;
    return valeur/vect_l.getTaille();
}

void Matrice::ordonneValeurPropre ( void )
{
    std::vector<double> valeur_tmp = std::vector<double>();
    for ( unsigned int i = 0 ; i < this->lesValeursPropres.size() ; i++ )
    {
        valeur_tmp.push_back( this->lesValeursPropres.at(i) );
    }
    std::sort ( valeur_tmp.begin(), valeur_tmp.end() );

    std::vector<Vecteur> vecteur_tmp = std::vector<Vecteur>();
    for ( unsigned int i = 0 ; i < valeur_tmp.size() ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->lesValeursPropres.size() ; j++ )
        {
            if ( abs ( valeur_tmp.at(i) - this->lesValeursPropres.at(j) ) < 0.0001 )
            {
                vecteur_tmp.push_back( this->lesVecteursPropres.at(j) );
                break;
            }
        }
    }

    for ( unsigned int i = 0 ; i < vecteur_tmp.size() ; i++ )
    {
        this->lesValeursPropres.at(i) = valeur_tmp.at(i);
        this->lesVecteursPropres.at(i) = vecteur_tmp.at(i);
    }
}

void Matrice::ordonneValeurPropreAbsolue ( void )
{
    std::vector<double> valeur_tmp = std::vector<double>();
    for ( unsigned int i = 0 ; i < this->lesValeursPropres.size() ; i++ )
    {
        valeur_tmp.push_back( this->lesValeursPropres.at(i) );
    }
    std::sort ( valeur_tmp.begin(), valeur_tmp.end(),
        [](double a, double b) {
            return abs(a) > abs(b);
        }
    );

    std::vector<Vecteur> vecteur_tmp = std::vector<Vecteur>();
    for ( unsigned int i = 0 ; i < valeur_tmp.size() ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->lesValeursPropres.size() ; j++ )
        {
            if ( abs ( valeur_tmp.at(i) - this->lesValeursPropres.at(j) ) < 0.0001 )
            {
                vecteur_tmp.push_back( this->lesVecteursPropres.at(j) );
                break;
            }
        }
    }

    for ( unsigned int i = 0 ; i < vecteur_tmp.size() ; i++ )
    {
        this->lesValeursPropres.at(i) = valeur_tmp.at(i);
        this->lesVecteursPropres.at(i) = vecteur_tmp.at(i);
    }
}

void Matrice::eigenAnalysis ( void )
{
    if ( this->eigen_analysis_effectuee ) return;
    if ( !this->isSquare() )
    {
        std::cout << "Pas d'eigen-analysis sur une matrice non-carr??e !" << std::endl;
        return;
    }

    this->lesVecteursPropres.clear();
    this->lesValeursPropres.clear();

    // Calcul de la paire propre la plus grande
    Matrice copieM = Matrice(*this);

    // Recherche des autres paires
    for (int i=0; i < (int)copieM.getNbLignes(); i++){
        Vecteur vect = copieM.powerIteration();
        this->lesVecteursPropres.push_back(vect);
        double lambda = this->calculValeurPropreAssociee(vect);
        this->lesValeursPropres.push_back(lambda);

        double norme = vect.getNorme();
        copieM = (copieM) - ((lambda / (norme*norme)) * Matrice::tensoriel(vect, vect));
    }

    //std::sort(this->lesValeursPropres.begin(),this->lesValeursPropres.end());

    // It??ration inverse pour la paire propre la plus proche de z??ro

    // V??rification que toutes les paires ont ??t?? trouv??s et sinon valeur propre = 0 et vecteur propre est nul
    if ( this->lesValeursPropres.size() < this->getNbLignes() )
    {
        std::cout << "Toutes les paires propres n'ont pas ete trouvees !" << std::endl;
        while ( this->lesValeursPropres.size() < this->getNbLignes() )
        {
            this->lesValeursPropres.push_back( 0.0 );
            this->lesVecteursPropres.push_back( Vecteur( this->getNbLignes() ) );
        }
    }

    // On range les valeurs/vecteurs propres et on l??ve le drapeau pour ne pas avoir ?? refaire l'analyse
    //this->ordonneValeurPropreAbsolue();
    this->eigen_analysis_effectuee = true;
}

// Accesseurs apr??s analyse
Matrice Matrice::getMatriceValeursPropres ( void )
{
    return Matrice ( this->getVecteurValeursPropres() );
}

Vecteur Matrice::getVecteurValeursPropres ( void )
{
    Vecteur res = Vecteur ( this->nb_lignes );
    for ( unsigned int i = 0 ; i < this->nb_lignes ; i++ )
    {
        res.setCoeff(i, this->lesValeursPropres.at(i) );
    }
    return res;
}

float Matrice::getValeurPropre ( unsigned int n )
{
    if ( n >= this->lesValeursPropres.size() )
    {
        std::cout << "La valeur propre n'existe pas" << std::endl;
        return 0.0;
    }
    return this->lesValeursPropres.at(n);
}

Matrice Matrice::getMatriceVecteursPropres ( void )
{
    Matrice res = Matrice ( this->nb_lignes );
    for ( unsigned int i = 0 ; i < this->nb_lignes ; i++ )
    {
        for ( unsigned int j = 0 ; j < this->nb_colonnes ; j++ )
        {
            res.setCoeff( i, j, this->lesVecteursPropres.at(i).getCoeff(j) );
        }
    }
    return res;
}

Vecteur Matrice::getVecteurPropre ( unsigned int n )
{
    if ( n >= this->lesVecteursPropres.size() )
    {
        std::cout << "Le vecteur propre n'existe pas" << std::endl;
        return Vecteur(0);
    }
    return this->lesVecteursPropres.at(n);
}

Matrice Matrice::getTranspose() {
    Matrice transpose = Matrice (this->getNbColonnes(), this->getNbLignes());
    for (int j=0; j<(int)this->getNbColonnes();j++)
        for (int i=0; i<(int)this->getNbLignes(); i++)
            transpose.setCoeff(j,i,this->getCoeff(i,j));
    return transpose;
}

Matrice operator* ( const Matrice& A, const Matrice& B )
{
    if ( A.getNbColonnes() != B.getNbLignes() )
    {
        std::cout << "Les matrices ne sont pas compatibles par produit" << std::endl;
        return Matrice(0);
    }

    Matrice res = Matrice ( A.getNbLignes(), B.getNbColonnes() );
    for ( unsigned int i = 0 ; i < res.getNbLignes() ; i++ )
    {
        for ( unsigned int j = 0 ; j < res.getNbColonnes() ; j++ )
        {
            double somme = 0.0;
            for ( unsigned int k = 0 ; k < A.getNbColonnes() ; k++ )
            {
                somme += A.getCoeff(i,k) * B.getCoeff(k,j);
            }
            res.setCoeff( i, j, somme );
        }
    }

    return res;
}

Matrice operator* ( const double lambda, const Matrice& M )
{
    Matrice res = Matrice ( M.getNbLignes(), M.getNbColonnes() );
    for ( unsigned int i = 0 ; i < res.getNbLignes() ; i++ )
    {
        for ( unsigned int j = 0 ; j < res.getNbColonnes() ; j++ )
        {
            res.setCoeff( i, j, lambda*M.getCoeff(i,j) );
        }
    }
    return res;
}

Vecteur operator* ( const Matrice& M, const Vecteur& V )
{
    if ( M.getNbColonnes() != V.getTaille() )
    {
        std::cout << "La matrice et le vecteur ne sont pas compatibles par produit" << std::endl;
        return Vecteur(0);
    }

    Vecteur res = Vecteur ( M.getNbLignes() );
    for ( unsigned int i = 0 ; i < res.getTaille() ; i++ )
    {
        double somme = 0.0;
        for ( unsigned int k = 0 ; k < M.getNbColonnes() ; k++ )
        {
            somme += M.getCoeff( i, k ) * V.getCoeff(k);
        }
        res.setCoeff ( i, somme );
    }
    return res;

}

Vecteur operator* ( const Vecteur& V, const Matrice& M )
{
    if ( M.getNbLignes() != V.getTaille() )
    {
        std::cout << "Le vecteur et la matrice ne sont pas compatibles par produit" << std::endl;
        return Vecteur(0);
    }

    Vecteur res = Vecteur ( M.getNbColonnes() );
    for ( unsigned int j = 0 ; j < res.getTaille() ; j++ )
    {
        double somme = 0.0;
        for ( unsigned int k = 0 ; k < M.getNbLignes() ; k++ )
        {
            somme += M.getCoeff( k, j ) * V.getCoeff(k);
        }
        res.setCoeff ( j, somme );
    }
    return res;
}

Matrice operator+ ( const Matrice& A, const Matrice& B )
{
    if ( A.getNbLignes() != B.getNbLignes() || A.getNbColonnes() != B.getNbColonnes() )
    {
        std::cout << "Les deux matrices ne sont pas compatibles par somme" << std::endl;
        return Vecteur(0);
    }

    Matrice res = Matrice ( A.getNbLignes(), A.getNbColonnes() );
    for ( unsigned int i = 0 ; i < res.getNbLignes() ; i++ )
    {
        for ( unsigned int j = 0 ; j < res.getNbColonnes() ; j++ )
        {
            res.setCoeff( i, j, A.getCoeff(i,j) + B.getCoeff(i,j) );
        }
    }
    return res;
}

Matrice operator- ( const Matrice& A, const Matrice& B )
{
    if ( A.getNbLignes() != B.getNbLignes() || A.getNbColonnes() != B.getNbColonnes() )
    {
        std::cout << "Les deux matrices ne sont pas compatibles par diff??rence" << std::endl;
        return Vecteur(0);
    }

    Matrice res = Matrice ( A.getNbLignes(), A.getNbColonnes() );
    for ( unsigned int i = 0 ; i < res.getNbLignes() ; i++ )
    {
        for ( unsigned int j = 0 ; j < res.getNbColonnes() ; j++ )
        {
            res.setCoeff( i, j, A.getCoeff(i,j) - B.getCoeff(i,j) );
        }
    }
    return res;
}

Matrice Matrice::tensoriel(const Vecteur& A, const Vecteur& B){
    Matrice tensor = Matrice(A.getTaille());
    for (int i=0; i < A.getTaille() ; i++){
        for (int j=0; j < A.getTaille() ; j++){
            double vall = A.getCoeff(i)*B.getCoeff(j);
            tensor.setCoeff(i, j, vall);
        }
    }
    return tensor;
}
