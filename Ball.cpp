#include "Ball.h"

Ball::Ball(double x, double y, itemId id) : QGraphicsEllipseItem(0)
{

    m_id = id;
    setRect(0, 0, m_radius*2, m_radius*2);
    m_currX = x;
    m_currY = y;
    setPos( x , y );

    QPen redPen( Qt::darkRed);
    redPen.setWidth(2);
    setPen( redPen);

}

void Ball::update()
{
    QGraphicsEllipseItem::setPos( m_currX, m_currY);
}

void Ball::setParentList(ItemList *ballsList)
{
    m_parentList = ballsList;
}

int Ball::setCoordinates(double X, double Y)
{
    m_currX = X;
    m_currY = Y;
    return 0;
}

int Ball::moveBy(double deltaX, double deltaY)
{
    m_currX += deltaX;
    m_currY += deltaY;
    return 0;
}

int Ball::lock()
{
    if( m_lock)
        return 1;
    else{
        m_lock = true;
        return 0;
    }
}

void Ball::unlock()
{
    m_lock = false;
}

int Ball::isLocked()
{
    return m_lock;
}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        lock();
        m_startedMouseMovePosition.x = event->pos().x();
        m_startedMouseMovePosition.y = event->pos().y();
        m_velocityX = 0;
        m_velocityY = 0;
        return;
    }
    if(event->button() == Qt::RightButton)
    {
        m_parentList->deleteItem(this);
        delete this;
        return;
    }
    return;
}

void Ball::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setCoordinates( event->scenePos().x() - m_startedMouseMovePosition.x, event->scenePos().y() - m_startedMouseMovePosition.y);
}

void Ball::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCoordinates( event->scenePos().x() - m_startedMouseMovePosition.x, event->scenePos().y() - m_startedMouseMovePosition.y);
    unlock();
}

double Ball::getY()
{
    return m_currY;
}

double Ball::getWidth()
{
    return 2*m_radius;
}

double Ball::getHeight()
{
    return 2*m_radius;
}

bool Ball::checkTouch(double X, double Y)
{
    return (((X - (m_currX + m_radius))*(X - (m_currX + m_radius)) +
             (Y - (m_currY + m_radius))*(Y -(m_currY + m_radius))) <= m_radius*m_radius) ? 1 : 0;
}

double Ball::getVelocityX()
{
    return m_velocityX;
}

double Ball::getVelocityY()
{
    return m_velocityY;
}

void Ball::setVelocityX( double velocityX)
{
    m_velocityX = velocityX;
}

void Ball::setVelocityY(double velocityY)
{
    m_velocityY = velocityY;
}

double Ball::getX()
{
    return m_currX;
}

Coordinates Ball::getCoordinates()
{
    return Coordinates( x(), y());
}

itemId Ball::getId()
{
    return m_id;
}

void Ball::setSize(double width, double height)
{
    double minimumSize = width < height ? width : height;
    m_radius = minimumSize/2;
    setRect( 0, 0, m_radius*2, m_radius*2);
}

void Ball::setRadius(double radius)
{
    m_radius = radius;
    setRect( 0, 0, m_radius*2, m_radius*2);
}
