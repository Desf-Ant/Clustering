#include "scene.h"

QBrush Scene::lesBrosses[8] =
{
    QBrush ( Qt::white ),
    QBrush ( Qt::red ),
    QBrush ( Qt::green ),
    QBrush ( Qt::blue ),
    QBrush ( Qt::magenta ),
    QBrush ( Qt::yellow ),
    QBrush ( Qt::cyan ),
    QBrush ( Qt::black )
};

QPen Scene::contour = QPen (Qt::black);

Scene::Scene ( Donnees* d )
{
    this->donnees = d;
    this->scene = new QGraphicsScene();
    this->setScene( this->scene );
    this->scene->addRect( 0, 0, 500, 500 );
    this->update();
}

void Scene::recharge ( void )
{
    this->scene->clear();
    this->scene->addRect( 0, 0, 500, 500 );

    std::vector<Sommet>* lesSommets = this->donnees->getDonnees();
    for (std::vector<Sommet>::iterator it = lesSommets->begin() ; it != lesSommets->end() ; it++)
    {
        double rayon = 5 + (*it).getZ()/10;
        this->scene->addEllipse( (*it).getX()-rayon, 500-(*it).getY()-rayon, rayon*2, rayon*2, Scene::contour, Scene::lesBrosses[(*it).getClasse()+1]);
    }

    std::vector<Sommet>* lesGraines = this->donnees->getGraines();
    for (std::vector<Sommet>::iterator it = lesGraines->begin() ; it != lesGraines->end() ; it++)
    {
        double rayon = 5 + (*it).getZ()/10;
        this->scene->addRect( (*it).getX()-rayon, 500-(*it).getY()-rayon, rayon*2, rayon*2, Scene::contour, Scene::lesBrosses[(*it).getClasse()+1]);
    }
}
