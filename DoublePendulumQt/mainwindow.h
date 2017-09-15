#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGraphicsItem>
#include <iostream>

#include "pendulum.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void playSimulation();
    void pauseSimulation();
    void drawSimulation();
    void initializeSimulation();
    void initializeScene();
    double mathToScene(double math);

    static constexpr int circleWidth = 12;
    static constexpr int rectWidth = 10;

private slots:
    void updateSimulation();
    void on_l1slider_sliderMoved(int position);

    void on_l2slider_sliderMoved(int position);

    void on_m2slider_sliderMoved(int position);

    void on_m1slider_sliderMoved(int position);

    void on_vel2slider_sliderMoved(int position);

    void on_vel1slider_sliderMoved(int position);

    void on_theta2slider_sliderMoved(int position);

    void on_theta1slider_sliderMoved(int position);

    void on_startButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *anchoredRect;
    QGraphicsRectItem *freeRect;
    QGraphicsEllipseItem *anchor;
    QGraphicsEllipseItem *joint;

    QTimer *timer;
    bool playing;

    Pendulum anchored;
    Pendulum free;
};

#endif // MAINWINDOW_H
