#ifndef ABSTRACTITEMLIST_H
#define ABSTRACTITEMLIST_H

class ItemList;

typedef int itemId;

struct Coordinates
{
    Coordinates(){}
    Coordinates( double X, double Y) : x(X), y(Y){}
    double x = 0;
    double y = 0;
};

class AbstractItem
{
public:
    virtual ~AbstractItem(){}
    virtual void setParentList( ItemList *ballsList) = 0;
    virtual itemId getId() = 0;
    virtual void setSize( double width, double height) = 0;
    virtual Coordinates getCoordinates() = 0;
    virtual double getX() = 0;
    virtual double getY() = 0;
    virtual double getWidth() = 0;
    virtual double getHeight() = 0;
    virtual bool checkTouch( double X, double Y) = 0;

    virtual double getVelocityX() = 0;
    virtual double getVelocityY() = 0;
    virtual void setVelocityX( double velocityX) = 0;
    virtual void setVelocityY( double velocityY) = 0;

    virtual int setCoordinates( double X, double Y) = 0;
    virtual int moveBy( double deltaX, double deltaY) = 0;

    virtual int lock() = 0;
    virtual int isLocked() = 0;
};

#endif // ABSTRACTITEMLIST_H
