#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QtWidgets>
#include <QPainter>

#include "fileparser.h"

enum Mode {bezier, lambda};

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(CIEVector &cievector);

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event, const QSize &newSize);
    virtual void Draw() = 0;


protected:
    CIEVector &cievector;
    QImage image;

    void DrawMargin(QPainter &painter, std::string xLabels[8], std::string yLabels[8]);
    virtual void DrawPoint(QPainter &painter, const QPointF &point, QColor color) = 0;
};

#endif // DRAWAREA_H
