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
    void Draw();

    QWidget central;
    CIEVector cieVector;

private:
    HorseShoe horseShoeArea;
    Bezier bezierArea;

};
#endif // MAINWINDOW_H
