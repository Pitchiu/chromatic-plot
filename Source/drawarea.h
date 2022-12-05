#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QtWidgets>
#include <QPainter>

#include "fileparser.h"
class DrawArea : public QWidget
{
public:
    DrawArea(CIEVector &cievector);

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event, const QSize &newSize);
    virtual void Draw() = 0;

    void DrawPoint(QPointF);


protected:
    CIEVector &cievector;
    QImage image;

    void DrawMargin(QPainter &painter, std::string xLabels[8], std::string yLabels[8]);
    void DrawPoint(QPainter &painter, const QPointF &point);
};

#endif // DRAWAREA_H
