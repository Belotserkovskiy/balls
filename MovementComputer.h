#ifndef MOVEMENTCOMPUTER_H
#define MOVEMENTCOMPUTER_H

#include <abstractmovementcomputer.h>
#include <thread>

class MovementComputer : public AbstractMovementComputer
{
    double m_fieldWidth, m_fieldHeight;
    AbstractItemList *m_itemList;
    enum StateOfMovement
    {
        inProcess,
        paused,
        stopped
    } m_state;

public:
    MovementComputer();
    void setField(double width, double height) override;
    void setItemsList( AbstractItemList *itemList) override;

    /// \brief start movement calculating
    int start() override;
    int pause() override;
    int stop() override;

private:
    static void startInOtherThread(AbstractItemList *itemList, StateOfMovement& state);

};

#endif // MOVEMENTCOMPUTER_H
