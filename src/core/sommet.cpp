#include "sommet.h"

Sommet::Sommet ( )
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->classe = -1;
}

Sommet::Sommet ( int x, int y, int z )
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->classe = -1;
}

int Sommet::getX ( void ) const
{
    return this->x;
}

int Sommet::getY ( void ) const
{
    return this->y;
}

int Sommet::getZ ( void ) const
{
    return this->z;
}

int Sommet::getClasse ( void ) const
{
    return this->classe;
}

void Sommet::setClasse ( int n )
{
    this->classe = n;
}

void Sommet::setTranslation ( int tx, int ty, int tz )
{
    this->x += tx;
    this->y += ty;
    this->z += tz;
}

void Sommet::setScale ( double sx, double sy, double sz )
{
    this->x *= sx;
    this->y *= sy;
    this->z *= sz;
}

void Sommet::setRotation ( double theta )
{
    double oldX = this->x;
    double oldY = this->y;
    this->x = x*cos(theta) - y*sin(theta);
    this->y = oldX*sin(theta) + oldY*cos(theta);
}

void Sommet::ajoute ( const Sommet& autre )
{
    this->x += autre.getX();
    this->y += autre.getY();
    this->z += autre.getZ();
}

Sommet Sommet::random2D ( void )
{
    return Sommet(arc4random() % 495 + 5,arc4random() % 495 + 5,0);
}

Sommet Sommet::random3D ( void )
{
    return Sommet(arc4random() % 495 + 5,arc4random() % 495 + 5,arc4random() % 100 - 50);
}
