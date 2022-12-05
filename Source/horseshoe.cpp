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
    update();
}
