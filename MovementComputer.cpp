#include "MovementComputer.h"

MovementComputer::MovementComputer()
{

}

void MovementComputer::setField(double width, double height)
{
    m_informationForComputing.fieldWidth = width;
    m_informationForComputing.fieldHeight = height;
}

void MovementComputer::getField(double *width, double *height)
{
    *width = m_informationForComputing.fieldWidth;
    *height = m_informationForComputing.fieldHeight;
}

void MovementComputer::setItemsList(ItemList *itemList)
{
    m_itemList = itemList;
}

int MovementComputer::start()
{
    if( m_informationForComputing.state == StateOfMovement::stopped)
    {
        if( m_itemList != nullptr)
        {
            m_informationForComputing.state = StateOfMovement::inProcess;
            std::thread workThread(&MovementComputer::startInOtherThread, std::ref(m_itemList), std::ref(m_informationForComputing));
            workThread.detach();
        }
    }else
        m_informationForComputing.state = StateOfMovement::inProcess;

    return 0;
}

int MovementComputer::pause()
{
    m_informationForComputing.state = StateOfMovement::paused;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return 0;
}

int MovementComputer::stop()
{
    m_informationForComputing.state = StateOfMovement::stopped;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if( m_itemList != nullptr)
        for( auto &iter : *m_itemList){
            iter->setVelocityX(0);
            iter->setVelocityY(0);
        }
    return 0;
}

StateOfMovement MovementComputer::getState()
{
    return m_informationForComputing.state;
}

void MovementComputer::setBorderFlag(BorderFlag flag)
{
    m_informationForComputing.borderFlag = flag;
}

BorderFlag MovementComputer::getBorderFlag()
{
    return m_informationForComputing.borderFlag;
}

void MovementComputer::setTypeOfInteraction(TypeOfInteraction type)
{
    m_informationForComputing.typeOfInteraction = type;
}

TypeOfInteraction MovementComputer::getInteractionType()
{
    return m_informationForComputing.typeOfInteraction;
}

void MovementComputer::setObjectsMass(double mass)
{
    if( mass < 1)
        mass = 1;
    m_informationForComputing.objectsMass = mass;
}

double MovementComputer::getObjectsMass()
{
    return m_informationForComputing.objectsMass;
}


void MovementComputer::checkTouchOfBorder(AbstractItem *item, double fieldWidth, double fieldHeight)
{
    double width = item->getWidth();
    double height = item->getHeight();
    double xPos = item->getX();
    double yPos = item->getY();
    if( item->checkTouch( 0, yPos + height/2)) // left border
           item->setVelocityX( (-1)*(item->getVelocityX()));
    if( item->checkTouch( xPos + width/2, fieldHeight)) // down border
           item->setVelocityY( (-1)*(item->getVelocityY()));
    if( item->checkTouch( fieldWidth, yPos + height/2)) // right border
           item->setVelocityX( (-1)*(item->getVelocityX()));
    if( item->checkTouch( xPos + width/2, 0)) //up border
           item->setVelocityY( (-1)*(item->getVelocityY()));
}

double sign( double number)
{
    return (number > 0) ? 1 : -1;
}

double distance( AbstractItem *item1, AbstractItem *item2)
{
    double dx = item1->getX() - item2->getX();
    double dy = item1->getY() - item2->getY();
    return std::sqrt(dx*dx + dy*dy);
}

void turnCoordinate( double X, double Y, double &X1, double &Y1, double alfa)  // alfa in radian
{
    double sinAlfa = sin( alfa);
    double cosAlfa = cos( alfa);
    X1 = X*cosAlfa + Y*sinAlfa;
    Y1 = - X*sinAlfa + Y*cosAlfa;
}

void MovementComputer::startInOtherThread(ItemList *itemList, AdditionalInformationForComputing &informationForComputing)
{
    std::map< itemId, double> itemsForcesX;
    std::map< itemId, double> itemsForcesY;

    double Vxi, Vyi, Vxj, Vyj;  // скорости i-го и j-го шарика
    double Vri, Vui, Vrj, Vuj;  // скорости i-го и j-го шарика в системе координат,
                                // ось x которой направлена по линии, соединяющей центры шариков ( для расчета столкновений шаров)

    while( informationForComputing.state != StateOfMovement::stopped)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        if( informationForComputing.state != StateOfMovement::paused)
        {
            itemList->lock();
            for( auto i = itemList->begin(); i != itemList->end(); ++i)
            {
                if( (*i)->isLocked())
                    continue;
                auto j = i;
                for( ++j; j != itemList->end(); ++j)
                {
                    if( (*j)->isLocked())
                        continue;
                    double dx = (*i)->getX() - (*j)->getX();
                    double dy = (*i)->getY() - (*j)->getY();

                    double r = distance( (*i), (*j));

                    double F = (r - 20)/(r*r);  // force

                    itemsForcesX[ (*i)->getId()] -= F*(dx/r); // F*cos(alfa)
                    itemsForcesY[ (*i)->getId()] -= F*(dy/r); // F*sin(alfa)

                    itemsForcesX[ (*j)->getId()] += F*(dx/r);
                    itemsForcesY[ (*j)->getId()] += F*(dy/r);

                    if( ( r <= (*i)->getWidth()) && // условие столкновения шариков (предполагается, что шарики одинакового размера)
                            (informationForComputing.typeOfInteraction == TypeOfInteraction::elastic))
                    {
                        turnCoordinate( (*i)->getVelocityX(), (*i)->getVelocityY(), Vri, Vui, acos(dx/r)*sign( dy));   // поворот системы координат
                        turnCoordinate( (*j)->getVelocityX(), (*j)->getVelocityY(), Vrj, Vuj, acos(dx/r)*sign( dy));

                        double temp = Vri; Vri = Vrj; Vrj = temp;  // шарики одинаковые, поэтому просто меняем скорости, направленные по линии соединяющей центры шаров

                        turnCoordinate( Vri, Vui, Vxi, Vyi, -acos(dx/r)*sign( dy));  // обратный поворот
                        turnCoordinate( Vrj, Vuj, Vxj, Vyj, -acos(dx/r)*sign( dy));

                        (*i)->setVelocityX( Vxi);
                        (*i)->setVelocityY( Vyi);

                        (*j)->setVelocityX( Vxj);
                        (*j)->setVelocityY( Vyj);

                        while( distance( (*i), (*j)) <= (*i)->getWidth())
                        {
                            double koef = (*i)->getWidth();
                            (*i)->moveBy( dx/koef, dy/koef);
                            (*j)->moveBy( -dx/koef, -dy/koef);
                        }
                    }
                }
                if( informationForComputing.borderFlag == BorderFlag::withBorder) // взаимодействие с границей поля
                    checkTouchOfBorder( (*i), informationForComputing.fieldWidth, informationForComputing.fieldHeight);

                (*i)->setVelocityX( (*i)->getVelocityX() + itemsForcesX[ (*i)->getId()]/informationForComputing.objectsMass);
                (*i)->setVelocityY( (*i)->getVelocityY() + itemsForcesY[ (*i)->getId()]/informationForComputing.objectsMass);
                (*i)->moveBy( (*i)->getVelocityX()*SPEED_KOEF, (*i)->getVelocityY()*SPEED_KOEF);
            }
            itemList->unlock();
            itemsForcesX.clear();
            itemsForcesY.clear();
        }
    }
}
