#include "widget.h"
#include "ui_widget.h"

#define CIRCLE_RADIUS 50

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene( 0, 0, 800, 600, this);
    ui->graphicsView->setScene(m_scene);
    m_scene->addRect(m_scene->sceneRect());
    Ball *ball = new Ball( 0, 0);
    m_scene->addItem( ball);
}

Widget::~Widget()
{
    delete ui;
}

Ball::Ball(double x, double y) : QGraphicsEllipseItem(0)
{
//    QColor color = QColor(rand()%255, rand()%255, rand()%255);
//    setBrush(color);
    setRect(0, 0, CIRCLE_RADIUS, CIRCLE_RADIUS);
    setPos( x, y);
}
