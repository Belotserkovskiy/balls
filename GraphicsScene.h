#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include <ItemList.h>
#include <Ball.h>

class GraphicsScene :  public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene( QObject *parent = 0);
    GraphicsScene( double x, double y, double width, double height, QObject *parent = 0);

    void mousePressEvent( QGraphicsSceneMouseEvent *event);

signals:
    void addElement( double, double);

};

#endif // GRAPHICSSCENE_H
