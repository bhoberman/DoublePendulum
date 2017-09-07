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

    int centerX, centerY;
    centerX = scene->width()/2;
    centerY = scene->height()/2;
    int circleWidth = 10;

    anchor = new QGraphicsEllipseItem(centerX, centerY, circleWidth, circleWidth);
    anchor->setBrush(greenBrush);
    anchor->setPen(blackOutline);
    scene->addItem(anchor);

    anchoredRect = new QGraphicsRectItem(0, 0, 10, 100, anchor);
    anchoredRect->setRotation(45);
    anchoredRect->setBrush(greenBrush);
    anchoredRect->setPen(blackOutline);
    scene->addItem(anchoredRect);

    joint = new QGraphicsEllipseItem(centerX + 100, centerX + 100, circleWidth, circleWidth, anchoredRect);
    joint->setBrush(greenBrush);
    joint->setPen(blackOutline);
    joint->setTransformOriginPoint(joint->rect().width()/2, joint->rect().height()/2);
    scene->addItem(joint);


    freeRect = new QGraphicsRectItem(centerX + 10, centerY + 100, 10, 100, joint);
    freeRect->setTransformOriginPoint(100, 100);
    freeRect->setRotation(30);
    freeRect->setBrush(QBrush(Qt::blue));
    freeRect->setPen(blackOutline);
    scene->addItem(freeRect);

    drawSimulation();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete anchor;
    delete joint;
    delete anchoredRect;
    delete freeRect;
}

void MainWindow::drawSimulation()
{
    float centerX = ui->graphicsView->width()/2;
    float centerY = ui->graphicsView->height()/2;

    anchoredRect->setRotation(0);
    anchoredRect->setTransformOriginPoint(centerX, centerY);
    anchoredRect->setPos(-anchoredRect->rect().width()/2*0, 0);


    scene->update(0, 0, centerX*2, centerY*2);
}

void MainWindow::on_l1slider_sliderMoved(int position)
{
    ui->l1label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
}

void MainWindow::on_l2slider_sliderMoved(int position)
{
    ui->l2label->setText(QString("%1m").arg(static_cast<double>(position) / 100.0));
}

void MainWindow::on_m2slider_sliderMoved(int position)
{
    ui->m2label->setText(QString("%1kg").arg(static_cast<double>(position) / 10.0));
}

void MainWindow::on_m1slider_sliderMoved(int position)
{
    ui->m1label->setText(QString("%1kg").arg(static_cast<double>(position) / 10.0));
}

void MainWindow::on_vel2slider_sliderMoved(int position)
{
    ui->vel2label->setText(QString("%1deg/s").arg(static_cast<double>(position) / 10.0));
}

void MainWindow::on_vel1slider_sliderMoved(int position)
{
    ui->vel1label->setText(QString("%1deg/s").arg(static_cast<double>(position) / 10.0));
}

void MainWindow::on_theta2slider_sliderMoved(int position)
{
    ui->theta2label->setText(QString("%1deg").arg(position));
}

void MainWindow::on_theta1slider_sliderMoved(int position)
{
    ui->theta1label->setText(QString("%1deg").arg(position));
}
