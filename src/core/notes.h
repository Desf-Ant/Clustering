#ifndef NOTES_H
#define NOTES_H

#include <iostream>
#include <vector>
#include "../core/note.h"

class Notes
{
private :
    std::vector < Note >* allNotes;
    std::vector < Note >* graines;
public:
    Notes();
    void addNote ( Note n );
    Note getNoteAt( int index ) const;
    std::vector < Note >* getDonnees( void ) const;
    std::vector < Note >* getGraines( void ) const;

    void affiche ( void ) const;
};

#endif // NOTES_H
