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

    QComboBox *comboBox = new QComboBox();;
    for(int i=4; i<=100; i++)
        comboBox->addItem(QString(std::to_string(i).c_str()), i);

    connect(comboBox, &QComboBox::currentTextChanged, this, [&](const QString &text){bezierArea.Reset(text.toInt());});
    comboBox->setCurrentIndex(4);

    QVBoxLayout *centralPanelLayout = new QVBoxLayout;
    QGroupBox *centralPanel = new QGroupBox;
    centralPanelLayout->setAlignment(Qt::AlignTop);
    centralPanelLayout->addWidget(comboBox);
    centralPanel->setLayout(centralPanelLayout);
    comboBox ->setGeometry( 100 , 100 , 100 , 20 );

    QPushButton *drawButton = new QPushButton();
    drawButton->setText("DRAW");
    connect(drawButton, &QPushButton::clicked, this, [&](){Draw();});

    centralPanelLayout->addWidget(drawButton);

    grid->addWidget(&bezierArea, 0,0);
    grid->addWidget(centralPanel, 0, 1);
    grid->addWidget(&horseShoeArea, 0,2);


    //bezierArea.seta

    setFixedSize(1400,600);
    central.setLayout(grid);
}

MainWindow::~MainWindow()
{
}

void MainWindow::Draw()
{
    bezierArea.Draw();
    horseShoeArea.SetXYZ(bezierArea.X, bezierArea.Y, bezierArea.Z);
    horseShoeArea.Draw();
}

