#include "horseshoe.h"

HorseShoe::HorseShoe(CIEVector &cievector) : DrawArea(cievector)
{

}

void HorseShoe::Draw()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for(int i=0; i<cievector.size(); i++)
    {
        auto cie = cievector[i];
        QPointF point(cie.x/(cie.x + cie.y + cie.z), cie.y/(cie.x + cie.y + cie.z));
        DrawPoint(painter, point);
    }
    DrawMargin(painter, labels, labels);

    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    chromaticPoint QPointF(X/(X + Y + Z), Y/(X + Y + Z);
    DrawLabel(chromaticPoint, QString());
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
    QPoint transformed(point.x()*500 + 100, 500*(1.0-point.y());
    painter.drawText(        painter.drawText(QPoint(x, y2+15), QString(xLabels[i].c_str()));
);
}

