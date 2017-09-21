#ifndef MOVEMENTCOMPUTER_H
#define MOVEMENTCOMPUTER_H

#include <abstractmovementcomputer.h>

#include <map>
#include <thread>
#include <chrono>
#include <cmath>

#define SPEED_KOEF 1

class MovementComputer : public AbstractMovementComputer
{
    struct AdditionalInformationForComputing
    {
        double fieldWidth = 0, fieldHeight = 0;
        double objectsMass = 1; // mass of moving objects
        StateOfMovement state = StateOfMovement::stopped;
        BorderFlag borderFlag = BorderFlag::withoutBorder;
        TypeOfInteraction typeOfInteraction = TypeOfInteraction::withoutInteraction;
    } m_informationForComputing;

    ItemList *m_itemList = nullptr;

public:
    MovementComputer();
    void setField(double width, double height) override;
    void getField(double *width, double *height) override;
    void setItemsList( ItemList *itemList) override;

    /// \brief start movement calculating
    int start() override;
    int pause() override;
    int stop() override;
    StateOfMovement getState();

    void setBorderFlag( BorderFlag flag);
    BorderFlag getBorderFlag();

    void setTypeOfInteraction( TypeOfInteraction type);
    TypeOfInteraction getInteractionType();

    void setObjectsMass( double mass);
    double getObjectsMass() override;

private:
    static void checkTouchOfBorder(AbstractItem *item, double fieldWidth, double fieldHeight);
    static void startInOtherThread(ItemList *itemList, AdditionalInformationForComputing& informationForComputing);

};

#endif // MOVEMENTCOMPUTER_H
