 #include "bezier.h"

Bezier::Bezier(CIEVector &cievector) : DrawArea(cievector)
{

}

void Bezier::Draw()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);

    DrawMargin(painter, labelsX, labelsY);
    update();

}
