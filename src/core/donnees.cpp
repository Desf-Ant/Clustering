#include "donnees.h"

Donnees::Donnees()
{
    this->lesDonnees = new std::vector<Sommet>();
    this->lesGraines = new std::vector<Sommet>();
    this->deuxD = true;
    this->nb_donnees = 1;
    this->type = EUCLIDIENNE;
}

Donnees::~Donnees()
{
    delete[] this->lesDonnees;
}

std::vector<Sommet>* Donnees::getDonnees ( void ) const
{
    return this->lesDonnees;
}

std::vector<Sommet>* Donnees::getGraines() const {
    return this->lesGraines;
}

void Donnees::setNbDonnees ( unsigned int n )
{
    this->nb_donnees = n;
}

void Donnees::setDimension ( bool dD )
{
    this->deuxD = dD;
}

void Donnees::setTypeDistance ( type_dist t )
{
    this->type = t;
}

void Donnees::genere_random( void )
{
    for (int i = 0; i<(int)this->nb_donnees;i++) {
        this->lesDonnees->push_back(this->genereSommet());
    }
}

void Donnees::genere_eparpilles( void )
{
    Distance d = Distance(this->type);
    std::vector<Sommet> ephemere = std::vector<Sommet>();
    std::vector<double> ephemereLong = std::vector<double>();
    for (int i = 0; i<(int)this->nb_donnees;i++) {
        ephemere.clear();
        ephemereLong.clear();
        for (int j = 0; j<15;j++) {
            std::vector<double> l = std::vector<double>();
            ephemere.push_back(Sommet::random2D());
            for (int k=0; k<(int)this->lesDonnees->size(); k++) {
                l.push_back(d.calcul(this->lesDonnees->at(k), ephemere.at(j)));
            }
            std::vector<double>::iterator result = std::min_element(std::begin(l), std::end(l));
            ephemereLong.push_back(std::distance(std::begin(l), result));
        }
        std::vector<double>::iterator result = std::max_element(std::begin(ephemereLong), std::end(ephemereLong));
        double index = std::distance(std::begin(ephemereLong), result);
        this->lesDonnees->push_back(ephemere.at(index));
    }
}

void Donnees::genere_carre( void )
{
    int xRect = arc4random () %490 + 5;
    int yRect = arc4random () %490 + 5;
    int widht = arc4random () %100 + 50;
    double angle = arc4random() % 360 + 0;
    while ( xRect+widht > 490 || yRect+widht > 490)
        widht = arc4random () %490 + 5;

    for (int i = 0; i<(int)this->nb_donnees; i++) {
        Sommet s;
        Sommet s2;
        do {
            s = this->genereSommet();
            s2 = Sommet(s);
            s2.setTranslation(-(xRect+widht/2), -(yRect+widht/2),0);
            s2.setRotation(-angle);
        } while (s2.getX()<-widht/2 || s2.getX()> widht/2 || s2.getY() < -widht/2 || s2.getY() > widht/2 || s2.getZ() < -widht/2 || s2.getZ() > widht/2);

        this->lesDonnees->push_back(s);
    }
}

void Donnees::genere_rectangle( void )
{
    int xRect = arc4random () %490 + 5;
    int yRect = arc4random () %490 + 5;
    int zRect = arc4random() %100 - 50;
    int widht = arc4random () %100 + 50;
    int height = arc4random() % 100 + 50;
    int deep = arc4random() % 75;
    double angle = arc4random() % 360 + 0;
    while ( xRect+widht > 490 )
        widht = arc4random () %490 + 5;
    while ( yRect+height > 490 )
        height = arc4random() % 490 + 5;
    while ( zRect+deep > 50 )
        deep = arc4random() % 75;

    for (int i = 0; i<(int)this->nb_donnees; i++) {
        Sommet s;
        Sommet s2;
        do {
            s = this->genereSommet();
            s2 = Sommet(s);
            s2.setTranslation(-(xRect+widht/2), -(yRect+height/2),-(zRect+deep/2));
            s2.setRotation(-angle);
        } while (s2.getX()<-widht/2 || s2.getX()> widht/2 || s2.getY() < -height/2 || s2.getY() > height/2 || s2.getZ() < -deep/2 || s2.getZ() > deep/2 );

        this->lesDonnees->push_back(s);
    }
}

void Donnees::genere_disque (void )
{
    int xRect = arc4random () %495 + 5;
    int yRect = arc4random () %495 + 5;
    int radius = arc4random () % 250 + 5;
    Sommet centre = Sommet(xRect,yRect,0);
    Distance d = Distance(this->type);

    for (int i = 0; i<(int)this->nb_donnees; i++) {
        Sommet s = this->genereSommet();
        Sommet s2 = Sommet(s);
        while (d.calcul(s2, centre) > radius) {
            s = this->genereSommet();
            s2 = Sommet(s);
        }
        this->lesDonnees->push_back(s);
    }
}

void Donnees::genere_ellipse ( void )
{
    int xRect = arc4random () %495 + 5;
    int yRect = arc4random() %495 + 5;
    int h = arc4random () % 250 + 5;
    int k = arc4random () %250 + 5;
    double angle = arc4random() % 360;

    while (xRect + h/2 > 495)
        h = arc4random () % 250 + 5;
    while (yRect + k/2 > 495)
        k = arc4random () % 250 + 5;

    for (int i = 0; i<(int)this->nb_donnees; i++) {
        Sommet s;
        Sommet s2;
        do {
            s = this->genereSommet();
            s2 = Sommet(s);
            s2.setTranslation(-(xRect+h/2), -(yRect+k/2),0);
            s2.setRotation(-angle);
        } while ((std::pow(s2.getX(),2))/std::pow(h,2)+(std::pow(s2.getY(),2))/std::pow(k,2)> 1);
        this->lesDonnees->push_back(s);
    }
}


Sommet Donnees::genereSommet() {
    if (deuxD)
        return Sommet::random2D();
    else
        return Sommet::random3D();
}
