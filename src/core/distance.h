#ifndef DISTANCE_H
#define DISTANCE_H

#include "sommet.h"
#include "note.h"

#include <limits>
#include "math.h"

typedef enum { MANHATTAN, EUCLIDIENNE, CHEBYSHEV, COSINUS } type_dist;

class Distance
{
    private :
        type_dist type;

    public :
        const static double INFINIE;
        const static double EPSILON;

    public:
        Distance();
        Distance( type_dist t );
        double calcul ( const Sommet& A, const Sommet& B ) const;
        double calculNote ( const Note& A, const Note& B) const;

    private :
        double calculManhattan   ( const Sommet& A, const Sommet& B ) const;
        double calculEuclidienne ( const Sommet& A, const Sommet& B ) const;
        double calculChebyshev   ( const Sommet& A, const Sommet& B ) const;
        double calculCosinus     ( const Sommet& A, const Sommet& B ) const;

        double calculManhattanNote   ( const Note& A, const Note& B ) const;
        double calculEuclidienneNote ( const Note& A, const Note& B ) const;
        double calculChebyshevNote   ( const Note& A, const Note& B ) const;
};

#endif // DISTANCE_H
