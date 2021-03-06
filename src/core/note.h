#ifndef NOTE_H
#define NOTE_H

#include <vector>
#include <iostream>

class Note
{
private :
    std::vector<double> dimensions;
    int classe;
public:
    Note();
    Note(std::vector <double> dimensions);
    int getClasse ( void ) const;
    int getSizeDimension ( void ) const;
    double getCoeffAt (int index) const;

    void setClasse ( int n );
    void ajoute ( const Note& autre );
    void affiche ( void ) const;

    void removeCoeff ( int n );

    void setTranslation ( Note n );

    static Note random(int n);
};

#endif // NOTE_H
