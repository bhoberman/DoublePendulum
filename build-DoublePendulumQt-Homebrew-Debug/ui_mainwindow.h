/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSlider *m1slider;
    QSlider *l1slider;
    QLabel *m1label;
    QLabel *m2label;
    QLabel *l1label;
    QLabel *l2label;
    QSlider *m2slider;
    QSlider *l2slider;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QLabel *label_5;
    QLabel *theta2label;
    QLabel *vel1label;
    QLabel *vel2label;
    QLabel *label_6;
    QSlider *theta1slider;
    QSlider *vel2slider;
    QSlider *vel1slider;
    QLabel *theta1label;
    QLabel *label_7;
    QLabel *label_8;
    QSlider *theta2slider;
    QLabel *label_9;
    QFrame *line;
    QLabel *label_10;
    QFrame *line_2;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(953, 633);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(650, 50, 121, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(650, 80, 121, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(650, 110, 121, 16));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(650, 140, 121, 16));
        m1slider = new QSlider(centralWidget);
        m1slider->setObjectName(QStringLiteral("m1slider"));
        m1slider->setGeometry(QRect(770, 50, 121, 20));
        m1slider->setMinimum(1);
        m1slider->setValue(10);
        m1slider->setOrientation(Qt::Horizontal);
        l1slider = new QSlider(centralWidget);
        l1slider->setObjectName(QStringLiteral("l1slider"));
        l1slider->setGeometry(QRect(770, 110, 121, 20));
        l1slider->setMinimum(1);
        l1slider->setMaximum(100);
        l1slider->setValue(100);
        l1slider->setOrientation(Qt::Horizontal);
        m1label = new QLabel(centralWidget);
        m1label->setObjectName(QStringLiteral("m1label"));
        m1label->setGeometry(QRect(900, 50, 47, 14));
        m2label = new QLabel(centralWidget);
        m2label->setObjectName(QStringLiteral("m2label"));
        m2label->setGeometry(QRect(900, 80, 47, 14));
        l1label = new QLabel(centralWidget);
        l1label->setObjectName(QStringLiteral("l1label"));
        l1label->setGeometry(QRect(900, 110, 47, 14));
        l2label = new QLabel(centralWidget);
        l2label->setObjectName(QStringLiteral("l2label"));
        l2label->setGeometry(QRect(900, 140, 47, 14));
        m2slider = new QSlider(centralWidget);
        m2slider->setObjectName(QStringLiteral("m2slider"));
        m2slider->setGeometry(QRect(770, 80, 121, 20));
        m2slider->setMinimum(1);
        m2slider->setValue(10);
        m2slider->setOrientation(Qt::Horizontal);
        l2slider = new QSlider(centralWidget);
        l2slider->setObjectName(QStringLiteral("l2slider"));
        l2slider->setGeometry(QRect(770, 140, 121, 20));
        l2slider->setMinimum(1);
        l2slider->setMaximum(100);
        l2slider->setValue(100);
        l2slider->setOrientation(Qt::Horizontal);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(650, 540, 80, 22));
        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(740, 540, 80, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(650, 260, 121, 16));
        theta2label = new QLabel(centralWidget);
        theta2label->setObjectName(QStringLiteral("theta2label"));
        theta2label->setGeometry(QRect(900, 230, 47, 14));
        vel1label = new QLabel(centralWidget);
        vel1label->setObjectName(QStringLiteral("vel1label"));
        vel1label->setGeometry(QRect(900, 260, 47, 14));
        vel2label = new QLabel(centralWidget);
        vel2label->setObjectName(QStringLiteral("vel2label"));
        vel2label->setGeometry(QRect(900, 290, 47, 14));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(650, 230, 121, 21));
        theta1slider = new QSlider(centralWidget);
        theta1slider->setObjectName(QStringLiteral("theta1slider"));
        theta1slider->setGeometry(QRect(770, 200, 121, 20));
        theta1slider->setMinimum(0);
        theta1slider->setMaximum(359);
        theta1slider->setValue(90);
        theta1slider->setOrientation(Qt::Horizontal);
        vel2slider = new QSlider(centralWidget);
        vel2slider->setObjectName(QStringLiteral("vel2slider"));
        vel2slider->setGeometry(QRect(770, 290, 121, 20));
        vel2slider->setMinimum(0);
        vel2slider->setMaximum(100);
        vel2slider->setValue(0);
        vel2slider->setOrientation(Qt::Horizontal);
        vel1slider = new QSlider(centralWidget);
        vel1slider->setObjectName(QStringLiteral("vel1slider"));
        vel1slider->setGeometry(QRect(770, 260, 121, 20));
        vel1slider->setMinimum(0);
        vel1slider->setMaximum(100);
        vel1slider->setValue(0);
        vel1slider->setOrientation(Qt::Horizontal);
        theta1label = new QLabel(centralWidget);
        theta1label->setObjectName(QStringLiteral("theta1label"));
        theta1label->setGeometry(QRect(900, 200, 47, 14));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(650, 290, 121, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(650, 200, 121, 16));
        theta2slider = new QSlider(centralWidget);
        theta2slider->setObjectName(QStringLiteral("theta2slider"));
        theta2slider->setGeometry(QRect(770, 230, 121, 20));
        theta2slider->setMinimum(0);
        theta2slider->setMaximum(359);
        theta2slider->setValue(90);
        theta2slider->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(650, 20, 161, 16));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(650, 40, 118, 3));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(650, 170, 161, 16));
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(650, 190, 118, 3));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(15, 11, 621, 561));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 953, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Double Pendulum", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Mass (anchored):", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Mass (free):", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Length (anchored):", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Length (free):", Q_NULLPTR));
        m1label->setText(QApplication::translate("MainWindow", "1.0kg", Q_NULLPTR));
        m2label->setText(QApplication::translate("MainWindow", "1.0kg", Q_NULLPTR));
        l1label->setText(QApplication::translate("MainWindow", "1.0m", Q_NULLPTR));
        l2label->setText(QApplication::translate("MainWindow", "1.0m", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        pauseButton->setText(QApplication::translate("MainWindow", "Pause", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Vel (anchored)", Q_NULLPTR));
        theta2label->setText(QApplication::translate("MainWindow", "90deg", Q_NULLPTR));
        vel1label->setText(QApplication::translate("MainWindow", "0deg/s", Q_NULLPTR));
        vel2label->setText(QApplication::translate("MainWindow", "0deg/s", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Angle (free)", Q_NULLPTR));
        theta1label->setText(QApplication::translate("MainWindow", "90deg", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Vel (free)", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Angle (anchored)", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Pendulum Properties", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Initial Conditions", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
