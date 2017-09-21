#ifndef BALL_H
#define BALL_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>

#include <abstractitem.h>
#include <ItemList.h>

//#define CIRCLE_RADIUS 25

class Ball : public QObject, public QGraphicsEllipseItem, public AbstractItem
{
    Q_OBJECT

    itemId m_id;
    double m_radius = 25;
    double m_velocityX = 0, m_velocityY = 0;
    double m_currX, m_currY;
    Coordinates m_startedMouseMovePosition;
    bool m_lock = false;
    ItemList *m_parentList = nullptr;

public slots:
    void update();

public:
    Ball(double x, double y, itemId id);
    void setParentList( ItemList *ballsList);
    itemId getId() override;
    void setSize( double width, double height);
    void setRadius( double radius);
    Coordinates getCoordinates() override;
    double getX() override;
    double getY() override;
    double getWidth();
    double getHeight();
    bool checkTouch( double X, double Y) override;

    double getVelocityX() override;
    double getVelocityY() override;
    void setVelocityX( double velocityX) override;
    void setVelocityY( double velocityY) override;

    int setCoordinates( double X, double Y) override;
    int moveBy( double deltaX, double deltaY) override;

    int lock();
    void unlock();
    int isLocked();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // BALL_H
