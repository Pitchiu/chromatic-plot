#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "drawarea.h"
#include "horseshoe.h"
#include "bezier.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(CIEVector& cieVector);
    ~MainWindow();

    QWidget central;
    CIEVector cieVector;

public slots:
    void Draw();

public:
    HorseShoe horseShoeArea;
    Bezier bezierArea;


private:
    Mode mode=bezier;
};
#endif // MAINWINDOW_H
