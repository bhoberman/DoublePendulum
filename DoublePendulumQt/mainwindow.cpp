#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::blue);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
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
