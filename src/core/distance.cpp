#include "distance.h"

const double Distance::INFINIE = std::numeric_limits<double>::max();
const double Distance::EPSILON = 0.00001;

Distance::Distance ()
{
    this->type = EUCLIDIENNE;
}

Distance::Distance ( type_dist t )
{
    this->type = t;
}

double Distance::calcul ( const Sommet& A, const Sommet& B ) const
{
    switch ( this->type )
    {
        case MANHATTAN   : return this->calculManhattan( A, B ); break;
        case EUCLIDIENNE : return this->calculEuclidienne( A, B ); break;
        case CHEBYSHEV   : return this->calculChebyshev( A, B ); break;
        case COSINUS     : return this->calculCosinus( A, B ); break;
        default          : return Distance::INFINIE;
    }
}

double Distance::calculNote(const Note &A, const Note &B) const {
    switch (this->type) {
    case MANHATTAN   : return this->calculManhattanNote( A, B ) ; break;
    case EUCLIDIENNE : return this->calculEuclidienneNote( A, B ); break;
    case CHEBYSHEV   : return this->calculChebyshevNote( A, B ); break;
    default          : return Distance::INFINIE;
    }
}

double Distance::calculManhattan ( const Sommet& A, const Sommet& B ) const
{
    return std::abs(B.getX() - A.getX())+std::abs(B.getY()-A.getY())+std::abs(B.getZ()-A.getZ());
}

double Distance::calculEuclidienne ( const Sommet& A, const Sommet& B ) const
{
    return std::sqrt(std::pow(B.getX() - A.getX(),2)+std::pow(B.getY() - A.getY(),2)+std::pow(B.getZ() - A.getZ(),2));
}

double Distance::calculChebyshev ( const Sommet& A, const Sommet& B ) const
{
    double maxDist = 0;
    maxDist = std::fmax(std::abs(B.getX()-A.getX()), std::abs(B.getY()-A.getY()));
    return std::fmax(maxDist, std::abs(B.getZ()-A.getZ()));
}

double Distance::calculCosinus ( const Sommet& A, const Sommet& B ) const
{
    return 1 - (A.getX()*B.getX()+A.getY()*B.getY()+A.getZ()*B.getZ())/(std::sqrt(std::pow(A.getX(),2)+std::pow(A.getY(),2)+std::pow(A.getZ(),2))*std::sqrt(std::pow(B.getX(),2)+std::pow(B.getY(),2)+std::pow(B.getZ(),2)));
}

double Distance::calculEuclidienneNote(const Note &A, const Note &B) const {
    double distance = 0;
    for (int i=0; i<A.getSizeDimension();i++)
        distance += std::pow(A.getCoeffAt(i)-B.getCoeffAt(i),2);
    return std::sqrt(distance);
}

double Distance::calculManhattanNote (const Note &A, const Note &B) const
{
    double distance = 0;
    for (int i=0; i<A.getSizeDimension();i++) {
        distance += std::abs(B.getCoeffAt(i) - A.getCoeffAt(i) );
    }
    return distance;
}

double Distance::calculChebyshevNote (const Note &A, const Note &B) const
{
    double maxDist = 0;
    for (int i=0; i<A.getSizeDimension(); i++) {
        if (maxDist < B.getCoeffAt(i) - A.getCoeffAt(i)) {
            maxDist = B.getCoeffAt(i) - A.getCoeffAt(i);
        }
    }
    return maxDist;
}
