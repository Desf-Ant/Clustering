#ifndef SOMMET_H
#define SOMMET_H

#include <random>
#include <math.h>

class Sommet
{
    private :
        int x;
        int y;
        int z;
        int classe;

    public:
        Sommet ();
        Sommet ( int x, int y , int z );
        int getX ( void ) const;
        int getY ( void ) const;
        int getZ ( void ) const;
        int getClasse ( void ) const;

        void setClasse ( int n );
        void setTranslation ( int tx, int ty, int tz );
        void setScale ( double sx, double sy, double sz );
        void setRotation ( double theta );
        void ajoute ( const Sommet& autre );

        static Sommet random2D();
        static Sommet random3D();
};



#endif // SOMMET_H
