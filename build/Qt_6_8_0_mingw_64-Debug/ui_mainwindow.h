/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *playlist;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnLoad;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        playlist = new QListWidget(centralwidget);
        playlist->setObjectName("playlist");
        playlist->setGeometry(QRect(160, 40, 256, 192));
        btnPlay = new QPushButton(centralwidget);
        btnPlay->setObjectName("btnPlay");
        btnPlay->setGeometry(QRect(140, 250, 80, 24));
        btnPause = new QPushButton(centralwidget);
        btnPause->setObjectName("btnPause");
        btnPause->setGeometry(QRect(240, 250, 80, 24));
        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");
        btnStop->setGeometry(QRect(340, 250, 80, 24));
        btnLoad = new QPushButton(centralwidget);
        btnLoad->setObjectName("btnLoad");
        btnLoad->setGeometry(QRect(430, 250, 80, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindow", "btnPlay", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindow", "btnPause", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "btnStop", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "btnLoad", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
