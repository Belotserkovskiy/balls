#include "MovementComputer.h"

MovementComputer::MovementComputer()
{

}

void MovementComputer::setField(double width, double height)
{
    m_fieldWidth = width;
    m_fieldHeight = height;
}

void MovementComputer::setItemsList(AbstractItemList *itemList)
{
    m_itemList = itemList;
}

int MovementComputer::start()
{
    m_state = inProcess;
    std::thread workThread(&MovementComputer::startInOtherThread, m_itemList, std::ref(m_state));
    workThread.detach();
    return 0;
}

int MovementComputer::pause()
{
    m_state = paused;
    return 0;
}

int MovementComputer::stop()
{
    m_state = stopped;
    return 0;
}

void MovementComputer::startInOtherThread(AbstractItemList *itemList, StateOfMovement &state)
{
    while( state == inProcess)
    {

    }
}

