#ifndef ANALYSECLEANDATA_H
#define ANALYSECLEANDATA_H

#include "../core/notes.h"
#include "../core/note.h"
#include <math.h>

class AnalyseCleanData
{
private :
    Notes* donnees;
    std::vector < Note >* lesDonnees;
public:
    AnalyseCleanData(Notes* data);
    std::vector < Note >* execute ( void );
    void cleanData( void );
    void removeLine ( int n );
    void removeColonne ( int n );
    void ligneVariance ( void );
    void colonneVariance ( void );
};

#endif // ANALYSECLEANDATA_H
