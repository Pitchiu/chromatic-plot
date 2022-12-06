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

    QPushButton *equalSpectrumButton = new QPushButton("EQUAL SPECTRUM");
    connect(equalSpectrumButton, &QPushButton::clicked, this, [&](){bezierArea.GenerateEqualSpectrum();});

    QPushButton *loadButton = new QPushButton("LOAD");
    connect(loadButton, &QPushButton::clicked, this, [&](){bezierArea.Load();});

    QPushButton *saveButton = new QPushButton("SAVE");
    connect(saveButton, &QPushButton::clicked, this, [&](){bezierArea.Save();});

    QGroupBox *spectrumBox = new QGroupBox();
    QVBoxLayout* spectrumLayout = new QVBoxLayout;
    spectrumLayout->setAlignment(Qt::AlignTop);

    QRadioButton* defaultLambdaButton = new QRadioButton("Bezier curve");
    defaultLambdaButton->setChecked(true);
    QRadioButton* lambdaButton = new QRadioButton("Lambda");
    connect(defaultLambdaButton, &QRadioButton::clicked, this, [&](bool checked){if(checked)mode=bezier; Draw();});
    connect(lambdaButton, &QRadioButton::clicked, this, [&](bool checked){if(checked)mode=lambda; Draw();});


    spectrumLayout->addWidget(defaultLambdaButton);
    spectrumLayout->addWidget(lambdaButton);

    spectrumBox->setLayout(spectrumLayout);

    centralPanelLayout->addWidget(equalSpectrumButton);
    centralPanelLayout->addWidget(spectrumBox);
    centralPanelLayout->addWidget(saveButton);
    centralPanelLayout->addWidget(loadButton);



    grid->addWidget(&bezierArea, 0,0);
    grid->addWidget(centralPanel, 0, 1);
    grid->addWidget(&horseShoeArea, 0,2);




    connect(&bezierArea, &Bezier::DrawEvent, this, &MainWindow::Draw);

    setFixedSize(1400,600);
    central.setLayout(grid);
    Draw();
}

MainWindow::~MainWindow()
{
}

void MainWindow::Draw()
{
    if(mode==bezier)
    {
        bezierArea.Draw();
        horseShoeArea.SetXYZ(bezierArea.X, bezierArea.Y, bezierArea.Z);
        horseShoeArea.Draw();
    }
    else
    {
        bezierArea.DrawLambda();
    }
}

