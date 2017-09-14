#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    drawSimulation();

    playing = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSimulation()));
    timer->start(5);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete anchor;
    delete joint;
    delete anchoredRect;
    delete freeRect;
    delete timer;
}

void MainWindow::initializeSimulation() {
    //Initialize the pendulums to the slider values
    anchored.mass = ui->m1slider->value()/10.0;
    anchored.length = ui->l1slider->value()/100.0;
    anchored.theta = ui->theta1slider->value();
    anchored.velocity = ui->vel1slider->value()/10.0;
    free.mass = ui->m2slider->value()/10.0;
    free.length = ui->l2slider->value()/100.0;
    free.theta = ui->theta2slider->value();
    free.velocity = ui->vel2slider->value()/10.0;

    drawSimulation();
}

void MainWindow::drawSimulation()
{
    float centerX = ui->graphicsView->width()/2;
    float centerY = ui->graphicsView->height()/2;

    anchoredRect->setRotation(anchored.theta);
    freeRect->setRotation(free.theta);

    scene->update(0, 0, centerX*2, centerY*2);
}

void MainWindow::updateSimulation() {
    if (playing) {
        std::cout << "kekek" << std::endl;
    }
}

void MainWindow::on_l1slider_sliderMoved(int position)
{
    ui->l1label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
    playing = false;
    initializeSimulation();
}

void MainWindow::on_l2slider_sliderMoved(int position)
{
    ui->l2label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
    playing = false;
    initializeSimulation();
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
    playing = true;
}

void MainWindow::on_pauseButton_clicked()
{
    playing = false;
}
