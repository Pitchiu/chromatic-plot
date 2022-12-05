#include "mainwindow.h"
#include "drawarea.h"
#include <QPainter>
#include <QFileDialog>
#include <QWidget>
#include <QGridLayout>
#include <fstream>


MainWindow::MainWindow(CIEVector& cieVector) : cieVector(cieVector), horseShoeArea(cieVector), bezierArea(cieVector),
    QMainWindow()
{
    QGridLayout *grid = new QGridLayout();
    setCentralWidget(&central);

    grid->addWidget(&horseShoeArea, 0,1);
    grid->addWidget(&bezierArea, 0,0);

    setFixedSize(1200,600);
    central.setLayout(grid);
}

MainWindow::~MainWindow()
{
}

void MainWindow::Draw()
{
    horseShoeArea.Draw();
    bezierArea.Draw();
}

