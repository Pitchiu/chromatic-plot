#include "drawarea.h"

DrawArea::DrawArea(CIEVector &cievector) : image(600,600, QImage::Format_RGB32), cievector(cievector)
{
    setFixedSize(600,600);
}


void DrawArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawArea::DrawMargin(QPainter &painter, std::string xLabels[9], std::string yLabels[9])
{
    QLine axisOne(0,500, 600, 500);
    QLine axisTwo(100,600, 100, 0);

    //horizontal
    painter.drawLine(axisOne);
    int x=150, y1=495, y2=505;
    for(int i=0; i<9; i++)
    {
        painter.drawLine(x, y1, x,y2);
        painter.drawText(QPoint(x, y2+15), QString(xLabels[i].c_str()));
        x+=50;
    }


    painter.drawLine(axisTwo);
    int y=450, x1=95, x2=105;
    for(int i=0; i<9; i++)
    {
        painter.drawLine(x1, y, x2,y);
        painter.drawText(QPoint(x1 - 20, y), QString(yLabels[i].c_str()));
        y-=50;
    }
}
