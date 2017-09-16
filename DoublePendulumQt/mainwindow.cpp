#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <Eigen/Dense>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    QBrush greenBrush(Qt::green);
    QPen blackOutline(Qt::transparent);
    blackOutline.setWidth(0);

    float centerX = scene->width()/2;
    float centerY = scene->height()/2;
    int rectHeight = 10*rectWidth;

    anchor = new QGraphicsEllipseItem(centerX - circleWidth/2, centerY - circleWidth/2, circleWidth, circleWidth);
    anchor->setBrush(greenBrush);
    anchor->setPen(blackOutline);
    anchor->setZValue(20);

    anchoredRect = new QGraphicsRectItem(centerX - rectWidth/2, centerY, rectWidth, rectHeight, anchor);
    anchoredRect->setBrush(greenBrush);
    anchoredRect->setPen(blackOutline);
    anchoredRect->setZValue(0);
    anchoredRect->setTransformOriginPoint(centerX, centerY);

    joint = new QGraphicsEllipseItem(centerX - circleWidth/2, centerY + rectHeight - circleWidth/2, circleWidth, circleWidth, anchoredRect);
    joint->setBrush(QBrush(Qt::black));
    joint->setPen(blackOutline);
    joint->setZValue(20);
    joint->setFlag(QGraphicsItem::ItemStacksBehindParent, true);


    freeRect = new QGraphicsRectItem(centerX - rectWidth/2, centerY + rectHeight, rectWidth, rectHeight, joint);
    freeRect->setBrush(QBrush(Qt::blue));
    freeRect->setPen(blackOutline);
    freeRect->setZValue(0);
    freeRect->setTransformOriginPoint(centerX, centerY + rectHeight);


    scene->addItem(anchor);

    initializeSimulation();
    drawSimulation();

    playing = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSimulation()));
    timer->start(5);
}

void MainWindow::initializeScene() {
    scene->removeItem(anchor);
    delete freeRect;
    delete joint;
    delete anchoredRect;
    delete anchor;

    QBrush greenBrush(Qt::green);
    QPen blackOutline(Qt::transparent);
    blackOutline.setWidth(0);

    float centerX = scene->width()/2;
    float centerY = scene->height()/2;
    int rectHeight = 10*rectWidth;

    anchor = new QGraphicsEllipseItem(centerX - circleWidth/2, centerY - circleWidth/2, circleWidth, circleWidth);
    anchor->setBrush(greenBrush);
    anchor->setPen(blackOutline);
    anchor->setZValue(20);

    float anchoredHeight = rectHeight * anchored.length;
    anchoredRect = new QGraphicsRectItem(centerX - rectWidth/2, centerY, rectWidth, anchoredHeight, anchor);
    anchoredRect->setBrush(greenBrush);
    anchoredRect->setPen(blackOutline);
    anchoredRect->setZValue(0);
    anchoredRect->setTransformOriginPoint(centerX, centerY);

    joint = new QGraphicsEllipseItem(centerX - circleWidth/2, centerY + anchoredHeight - circleWidth/2, circleWidth, circleWidth, anchoredRect);
    joint->setBrush(QBrush(Qt::black));
    joint->setPen(blackOutline);
    joint->setZValue(20);
    joint->setFlag(QGraphicsItem::ItemStacksBehindParent, true);


    float freeHeight = rectHeight * free.length;
    freeRect = new QGraphicsRectItem(centerX - rectWidth/2, centerY + anchoredHeight, rectWidth, freeHeight, joint);
    freeRect->setBrush(QBrush(Qt::blue));
    freeRect->setPen(blackOutline);
    freeRect->setZValue(0);
    freeRect->setTransformOriginPoint(centerX, centerY + anchoredHeight);


    scene->addItem(anchor);

    initializeSimulation();
    drawSimulation();
}

Eigen::Vector2d calculateAcceleration(Eigen::Vector2d position, Eigen::Vector2d velocity, Eigen::Vector2d mass, Eigen::Vector2d length) {
    using std::sin;
    using std::cos;
    Eigen::Vector2d acceleration;
    constexpr double g = 9.80;

    //These lines were taken from the SAGE output and find/replaced into this form (except substitution of ^ for pow, which was manual)
    acceleration(0) = 3*(4*g*mass(0)*sin(position(0)) + 3*g*mass(1)*sin(position(0) - 2*position(1)) + 5*g*mass(1)*sin(position(0)) + 3*length(0)*mass(1)*pow(velocity(0), 2.0)*sin(2*position(0) - 2*position(1)) + 4*length(0)*mass(1)*pow(velocity(1), 2.0)*sin(position(0) - position(1)))/(2*(-4*mass(0) + 9*mass(1)*pow(cos(position(0) - position(1)), 2.0) - 12*mass(1))*length(0));
    acceleration(1) = 3*(-2*(g*sin(position(1)) - length(0)*pow(velocity(0), 2.0)*sin(position(0) - position(1)))*(mass(0) + 3*mass(1)) + 3*(g*mass(0)*sin(position(0)) + 2*g*mass(1)*sin(position(0)) + length(0)*mass(1)*pow(velocity(1), 2.0)*sin(position(0) - position(1)))*cos(position(0) - position(1)))/((4*mass(0) - 9*mass(1)*pow(cos(position(0) - position(1)), 2.0) + 12*mass(1))*length(0));

    return acceleration;
}

double MainWindow::mathToScene(double math) {
    return -180*math/M_PI;
}

MainWindow::~MainWindow()
{
    delete freeRect;
    delete joint;
    delete anchoredRect;
    delete anchor;
    delete timer;
    delete scene;
    delete ui;
}

void MainWindow::initializeSimulation() {
    //Initialize the pendulums to the slider values
    anchored.mass = ui->m1slider->value()/10.0;
    anchored.length = ui->l1slider->value()/100.0;
    anchored.theta = M_PI*ui->theta1slider->value()/180.0;
    anchored.velocity = ui->vel1slider->value()/10.0;
    free.mass = ui->m2slider->value()/10.0;
    free.length = ui->l2slider->value()/100.0;
    free.theta = M_PI*ui->theta2slider->value()/180.0;
    free.velocity = ui->vel2slider->value()/10.0;

    drawSimulation();
}

void MainWindow::drawSimulation()
{
    float centerX = ui->graphicsView->width()/2;
    float centerY = ui->graphicsView->height()/2;

    anchoredRect->setRotation(mathToScene(anchored.theta));
    freeRect->setRotation(mathToScene(free.theta) - mathToScene(anchored.theta));

    scene->update(0, 0, centerX*2, centerY*2);
}

void MainWindow::updateSimulation() {

    constexpr double dt = 0.01;

    if (playing) {
        using Eigen::Vector2d;
            Vector2d initialPos, initialVel, mass, length;
            initialPos(0) = anchored.theta;
            initialPos(1) = free.theta;
            initialVel(0) = anchored.velocity;
            initialVel(1) = free.velocity;
            mass(0) = anchored.mass;
            mass(1) = free.mass;
            length(0) = anchored.length;
            length(1) = free.length;

            Vector2d k0 = dt*initialVel;
            Vector2d l0 = dt*calculateAcceleration(initialPos, initialVel, mass, length);
            Vector2d k1 = dt*(initialVel + l0/2.0);
            Vector2d l1 = dt*calculateAcceleration(initialPos + k0/2.0, initialVel + l0/2.0, mass, length);
            Vector2d k2 = dt*(initialVel + l1/2.0);
            Vector2d l2 = dt*calculateAcceleration(initialPos + k1/2.0, initialVel + l1/2.0, mass, length);
            Vector2d k3 = dt*(initialVel + l2);
            Vector2d l3 = dt*calculateAcceleration(initialPos + k2, initialVel + l2, mass, length);

            Vector2d newPos, newVel;
            newPos = initialPos + 1/6.0*(k0 + 2.0*k1 + 2.0*k2 + k3);
            newVel = initialVel + 1/6.0*(l0 + 2.0*l1 + 2.0*l2 + l3);

            anchored.theta = newPos(0);
            anchored.velocity = newVel(0);
            free.theta = newPos(1);
            free.velocity = newVel(1);

            drawSimulation();
    }
}

void MainWindow::on_l1slider_sliderMoved(int position)
{
    ui->l1label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
    playing = false;
    initializeSimulation();
    initializeScene();
}

void MainWindow::on_l2slider_sliderMoved(int position)
{
    ui->l2label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
    playing = false;
    initializeSimulation();
    initializeScene();
}

void MainWindow::on_m2slider_sliderMoved(int position)
{
    ui->m2label->setText(QString("%1kg").arg(static_cast<double>(position) / 10.0));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_m1slider_sliderMoved(int position)
{
    ui->m1label->setText(QString("%1kg").arg(static_cast<double>(position) / 10.0));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_vel2slider_sliderMoved(int position)
{
    ui->vel2label->setText(QString("%1deg/s").arg(static_cast<double>(position) / 10.0));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_vel1slider_sliderMoved(int position)
{
    ui->vel1label->setText(QString("%1deg/s").arg(static_cast<double>(position) / 10.0));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_theta2slider_sliderMoved(int position)
{
    ui->theta2label->setText(QString("%1deg").arg(position));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_theta1slider_sliderMoved(int position)
{
    ui->theta1label->setText(QString("%1deg").arg(position));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_startButton_clicked()
{
    initializeSimulation();
    playing = true;
}

void MainWindow::on_pauseButton_clicked()
{
    playing = false;
}
