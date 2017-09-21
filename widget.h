#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>

#include <abstractitem.h>
#include <GraphicsScene.h>
#include <ItemList.h>
#include <Ball.h>
#include <MovementComputer.h>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_pause_Button_clicked();

    void on_stop_Button_clicked();

    void on_start_Button_clicked();

    void on_cancel_Button_clicked();

    void addItem( double x, double y);

    void adjustSize();

    void setBallsMass(int mass);

    void setBallsSize(int size);

    void on_notInteractiveBallsRadioButton_clicked();

    void on_interactiveBallsRadioButton_clicked();

    void on_notInteractiveBorderRadioButton_clicked();

    void on_interactiveBorderRadioButton_clicked();

    Ball *getBall( double x, double y);

    void on_clearButton_clicked();

private:
    Ui::Widget *ui;

    QTimer *timer;
    GraphicsScene *m_scene;
    ItemList *m_ballsList;
    AbstractMovementComputer *m_computer;

public:
    Ball *m_ball;
};

#endif // WIDGET_H
