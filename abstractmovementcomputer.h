#ifndef ABSTRACTMOVEMENTCOMPUTER_H
#define ABSTRACTMOVEMENTCOMPUTER_H

#include <ItemList.h>

enum StateOfMovement
{
    inProcess,
    paused,
    stopped
};

enum BorderFlag
{
    withBorder,           // учитывать столкновения с границей
    withoutBorder         // не учитывать столкновения с границей

};

enum TypeOfInteraction
{
    withoutInteraction,
    elastic
};

class AbstractMovementComputer
{
public:
    virtual void setField( double width, double height) = 0;
    virtual void getField(double *width, double *height) = 0;
    virtual void setItemsList( ItemList *itemList) = 0;

    /// \brief start movement calculating
    virtual int start() = 0;
    virtual int pause() = 0;
    virtual int stop() = 0;
    virtual StateOfMovement getState() = 0;

    virtual void setBorderFlag( BorderFlag flag) = 0;
    virtual BorderFlag getBorderFlag() = 0;

    virtual void setTypeOfInteraction( TypeOfInteraction type) = 0;
    virtual TypeOfInteraction getInteractionType() = 0;

    virtual void setObjectsMass( double mass) = 0;
    virtual double getObjectsMass() = 0;


};

#endif // ABSTRACTMOVEMENTCOMPUTER_H
