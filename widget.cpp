#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment( Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scene = new GraphicsScene( 0, 0, ui->graphicsView->width(), ui->graphicsView->height(), this);
    ui->graphicsView->setScene(m_scene);

    timer = new QTimer;
    timer->start(5);
    connect( timer, SIGNAL(timeout()), this, SLOT(adjustSize()));

    m_computer = new MovementComputer;
    m_computer->setField( ui->graphicsView->width(), ui->graphicsView->height());
    m_ballsList = new ItemList;

    connect(m_scene, SIGNAL(addElement(double,double)), this, SLOT( addItem(double,double)));
    ui->notInteractiveBallsRadioButton->setAutoExclusive(false);
    ui->interactiveBallsRadioButton->setAutoExclusive(false);
    ui->notInteractiveBallsRadioButton->setChecked( true);
    ui->interactiveBorderRadioButton->setChecked(true);
    on_interactiveBorderRadioButton_clicked();
    on_notInteractiveBallsRadioButton_clicked();

    ui->massBallSlider->setMaximum(1);
    ui->massBallSlider->setMaximum(10);
    connect(ui->massBallSlider, SIGNAL(valueChanged(int)), this, SLOT(setBallsMass(int)));

    ui->sizeBallSlider->setMinimum(25);
    ui->sizeBallSlider->setMaximum(70);
    connect(ui->sizeBallSlider, SIGNAL(valueChanged(int)), this, SLOT(setBallsSize(int)));

    addItem( ui->sizeBallSlider->value(), ui->graphicsView->height()/2);
    addItem( ui->graphicsView->width() - ui->sizeBallSlider->value(), ui->graphicsView->height()/2);
}

Widget::~Widget()
{
    m_computer->stop();
    delete m_computer;
    delete m_ballsList;
    delete ui;
}

void Widget::on_start_Button_clicked()
{
    if( m_computer->getState() == StateOfMovement::stopped)
        m_computer->setItemsList( m_ballsList);
    m_computer->start();
}

void Widget::on_pause_Button_clicked()
{
    m_computer->pause();
}

void Widget::on_stop_Button_clicked()
{
    m_computer->stop();
}

void Widget::on_cancel_Button_clicked()
{
    this->close();
}

void Widget::addItem(double x, double y)
{
    StateOfMovement initialState = m_computer->getState();
    if( initialState == StateOfMovement::inProcess)
        m_computer->pause();

    Ball* ball = getBall( x, y);
    m_scene->addItem( ball);
    connect( timer, SIGNAL(timeout()), ball, SLOT(update()));
    m_ballsList->addItem( ball);
    if(( m_computer->getState() == StateOfMovement::paused) && ( initialState == StateOfMovement::inProcess))
        m_computer->start();
}

Ball *Widget::getBall(double x, double y)
{
    auto count = m_ballsList->count();
    Ball* ball = new Ball( x - ui->sizeBallSlider->value(), y - ui->sizeBallSlider->value(), ++count);
    ball->setRadius( ui->sizeBallSlider->value());

    if( ui->notInteractiveBallsRadioButton->isChecked()){
        QPen pen(Qt::darkRed);
        pen.setWidth(2);
        ball->setPen( pen);
    }else
    {
        QPen pen(Qt::darkRed);

        double ballsRadius = ui->sizeBallSlider->value();
        QRadialGradient color(ballsRadius, ballsRadius, ballsRadius);
        color.setColorAt(1, Qt::darkRed);
        color.setColorAt(0, Qt::lightGray);

        ball->setPen( pen);
        ball->setBrush(color);
    }
    return ball;
}

void Widget::adjustSize()
{
    m_scene->setSceneRect( 0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    m_computer->setField( ui->graphicsView->width(), ui->graphicsView->height());
}

void Widget::setBallsMass(int mass)
{
    m_computer->setObjectsMass( mass);
}

void Widget::setBallsSize(int size)
{
    StateOfMovement initialState = m_computer->getState();
    if( initialState == StateOfMovement::inProcess)
        m_computer->pause();
    for( auto& ball : *m_ballsList)
        ball->setSize( size*2, size*2);
    if(( m_computer->getState() == StateOfMovement::paused) && ( initialState == StateOfMovement::inProcess))
        m_computer->start();
}

void Widget::on_notInteractiveBallsRadioButton_clicked()
{

    ui->interactiveBallsRadioButton->setChecked(false);
    ui->notInteractiveBallsRadioButton->setChecked(true);

    QPen pen(Qt::darkRed);
    pen.setWidth(2);

    StateOfMovement initialState = m_computer->getState();
    if( initialState == StateOfMovement::inProcess)
        m_computer->pause();
    m_computer->setTypeOfInteraction( TypeOfInteraction::withoutInteraction);  // change type of interaction
    for ( auto &ball : *m_ballsList){                              // change color
        dynamic_cast<Ball*>(ball)->setBrush( QBrush());
        dynamic_cast<Ball*>(ball)->setPen( pen);
    }
    if(( m_computer->getState() == StateOfMovement::paused) && ( initialState == StateOfMovement::inProcess))
        m_computer->start();
}

void Widget::on_interactiveBallsRadioButton_clicked()
{
    ui->notInteractiveBallsRadioButton->setChecked(false);
    ui->interactiveBallsRadioButton->setChecked(true);

    double ballsRadius = ui->sizeBallSlider->value();
    QRadialGradient color(ballsRadius, ballsRadius, ballsRadius);
    color.setColorAt(1, Qt::darkRed);
    color.setColorAt(0, Qt::lightGray);

    QPen pen(Qt::darkRed);
    pen.setWidth(0);

    StateOfMovement initialState = m_computer->getState();
    if( initialState == StateOfMovement::inProcess)
        m_computer->pause();
    m_computer->setTypeOfInteraction( TypeOfInteraction::elastic);  // change type of interaction
    for ( auto &ball : *m_ballsList){                              // change color
        dynamic_cast<Ball*>(ball)->setBrush( color);
        dynamic_cast<Ball*>(ball)->setPen( pen);
    }
    if(( m_computer->getState() == StateOfMovement::paused) && ( initialState == StateOfMovement::inProcess))
        m_computer->start();
}

void Widget::on_notInteractiveBorderRadioButton_clicked()
{
    ui->interactiveBorderRadioButton->setChecked(false);
    ui->notInteractiveBorderRadioButton->setChecked(true);
    m_computer->setBorderFlag( BorderFlag::withoutBorder);
}

void Widget::on_interactiveBorderRadioButton_clicked()
{
    ui->notInteractiveBorderRadioButton->setChecked(false);
    ui->interactiveBorderRadioButton->setChecked(true);
    m_computer->setBorderFlag( BorderFlag::withBorder);
}

void Widget::on_clearButton_clicked()
{
    m_computer->stop();
    m_ballsList->clear();
}
