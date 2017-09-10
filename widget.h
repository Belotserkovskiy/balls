#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <abstractitemlist.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsScene *m_scene;
};

class Ball : public QGraphicsEllipseItem/*, public AbstractItem*/
{
public:
    Ball(double x, double y);

};
#endif // WIDGET_H
