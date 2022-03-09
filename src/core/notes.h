#ifndef NOTES_H
#define NOTES_H

#include <iostream>
#include <vector>
#include "../core/note.h"

class Notes
{
private :
    std::vector < Note >* allNotes;
public:
    Notes();
    void addNote ( Note n );
    Note getNoteAt( int index ) const;
    std::vector < Note >* getDonnees( void ) const;

    void affiche ( void ) const;
};

#endif // NOTES_H
