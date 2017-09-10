#ifndef ABSTRACTITEMLIST_H
#define ABSTRACTITEMLIST_H

typedef int itemId;

struct Coordinates
{
    double x = 0;
    double y = 0;
};

class AbstractItem
{
    virtual itemId getId() = 0;
    virtual Coordinates getCoordinates() = 0;
    virtual int setCoordinates( Coordinates coordinates) = 0;
    virtual int moveBy( double deltaX, double deltaY) = 0;
};

class AbstractItemList
{
    virtual int addItem( AbstractItem *item) = 0;
    virtual void deleteItem( itemId id) = 0;
};

#endif // ABSTRACTITEMLIST_H
