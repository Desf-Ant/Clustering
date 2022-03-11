#ifndef DBSCANNOTE_H
#define DBSCANNOTE_H

#include "../core/distance.h"
#include "../core/note.h"
#include "../core/notes.h"
#include <vector>
#include <iterator>

class DbscanNote
{
private :
    Notes* donnees;
    std::vector <Note>* lesDonnees;
    type_dist type_distance;
    Distance distance;
    unsigned int nb_points_minimum;
    double distance_maximum;

    unsigned int classe_courante;
    std::vector<bool> deja_visites;
    std::vector<unsigned int> voisinage_courant;
    std::vector<unsigned int> a_ajouter_au_cluster;

public:
    DbscanNote ( Notes* d, type_dist t );
    void execute ( void );
    void calculVoisinage ( unsigned int indice );
    void etendCluster ( unsigned int indice );
};
#endif // DBSCANNOTE_H
