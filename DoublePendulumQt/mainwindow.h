#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGraphicsItem>
#include <iostream>

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
    void updateSimulation();
    void drawSimulation();

private slots:
    void on_l1slider_sliderMoved(int position);

    void on_l2slider_sliderMoved(int position);

    void on_m2slider_sliderMoved(int position);

    void on_m1slider_sliderMoved(int position);

    void on_vel2slider_sliderMoved(int position);

    void on_vel1slider_sliderMoved(int position);

    void on_theta2slider_sliderMoved(int position);

    void on_theta1slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *anchoredRect;
    QGraphicsRectItem *freeRect;
    QGraphicsEllipseItem *anchor;
    QGraphicsEllipseItem *joint;
};

#endif // MAINWINDOW_H
