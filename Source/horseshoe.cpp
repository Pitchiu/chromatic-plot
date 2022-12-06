#include "horseshoe.h"

HorseShoe::HorseShoe(CIEVector &cievector) : DrawArea(cievector)
{
    plot = QImage("plot.jpg").scaled(410,410);
    //target = QRectF(10.0, 20.0, 80.0, 60.0);
    //source = QRectF(0.0, 0.0, 70.0, 40.0);
}

void HorseShoe::Draw()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);
    painter.drawImage(90,80, plot);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for(int i=0; i<cievector.size(); i++)
    {
        auto cie = cievector[i];
        QPointF point(cie.x/(cie.x + cie.y + cie.z), cie.y/(cie.x + cie.y + cie.z));
        DrawPoint(painter, point);
    }
    DrawMargin(painter, labels, labels);

    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPointF chromaticPoint(X/(X + Y + Z), Y/(X + Y + Z));
    DrawLabel(painter, chromaticPoint);
    DrawPoint(painter, chromaticPoint);
    update();

}



void HorseShoe::DrawPoint(QPainter &painter, const QPointF& point, QColor color)
{
    painter.drawPoint(point.x()*500 + 100, 500*(1.0-point.y()));
}

void HorseShoe::SetXYZ(float X, float Y, float Z)
{
    this->X = X;
    this->Y = Y;
    this->Z = Z;
}

void HorseShoe::DrawLabel(QPainter &painter,const QPointF &point)
{
    QPoint transformed(point.x()*500 + 100, 500*(1.0-point.y()));
    QString strx;
    strx.setNum(point.x(), 'g', 3);
    QString stry;
    stry.setNum(point.y(), 'g', 3);

    QString str = "(" + strx + ", " + stry + ")";

    painter.drawText(QPoint(transformed.x(), transformed.y()+15), str);
}

