#ifndef SCENE_H
#define SCENE_H

#include "../core/donnees.h"

#include <QGraphicsView>
#include <QGraphicsScene>

class Scene : public QGraphicsView
{
    private :
        Donnees* donnees;
        QGraphicsScene* scene;

    public :
        Scene ( Donnees* d );
        void recharge ( void );

    private :
        static QBrush lesBrosses[8];
        static QPen contour;
};

#endif // SCENE_H
