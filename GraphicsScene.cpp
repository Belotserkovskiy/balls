#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene( parent){}

GraphicsScene::GraphicsScene(double x, double y, double width, double height, QObject *parent) : QGraphicsScene( x, y, width, height, parent){}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if( itemAt(event->scenePos().x(), event->scenePos().y(), QTransform()) == nullptr){
            emit addElement( event->scenePos().x(), event->scenePos().y());
            return;
        }
    }
    QGraphicsScene::mousePressEvent( event);
    return;
}
