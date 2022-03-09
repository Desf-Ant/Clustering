#include "notes.h"

Notes::Notes()
{
    this->allNotes = new std::vector < Note >();
}


void Notes::addNote(Note n) {
    this->allNotes->push_back(n);
}

Note Notes::getNoteAt(int index) const {
    if (index <= 0 || index >= (int)this->allNotes->size() )
        return Note();
    return this->allNotes->at(index);
}

void Notes::affiche() const {
    for (int i=0; i<(int)this->allNotes->size(); i++) {
        std::cout << "index " << i << " | ";
        this->allNotes->at(i).affiche();
    }
}
