#ifndef ABSTRACTMOVEMENTCOMPUTER_H
#define ABSTRACTMOVEMENTCOMPUTER_H

#include <abstractitemlist.h>

class AbstractMovementComputer
{
public:
    virtual void setField( double width, double height) = 0;
    virtual void setItemsList( AbstractItemList *itemList) = 0;

    /// \brief start movement calculating
    virtual int start() = 0;
    virtual int pause() = 0;
    virtual int stop() = 0;
};

#endif // ABSTRACTMOVEMENTCOMPUTER_H
