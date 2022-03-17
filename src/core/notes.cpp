#include "notes.h"

Notes::Notes()
{
    this->allNotes = new std::vector < Note >();
}

Notes::Notes(std::vector <Note>* n) {
    this->allNotes = n;
}


void Notes::addNote(Note n) {
    this->allNotes->push_back(n);
}

std::vector< Note >* Notes::getDonnees () const {
    return this->allNotes;
}

Note Notes::getNoteAt(int index) const {
    if (index < 0 || index >= (int)this->allNotes->size() )
        return Note();
    return this->allNotes->at(index);
}

std::vector<Note>* Notes::getGraines() const {
    return this->graines;
}

void Notes::affiche() const {
    for (int i=0; i<(int)this->allNotes->size(); i++) {
        std::cout << "index " << i << " | ";
        this->allNotes->at(i).affiche();
    }
}
