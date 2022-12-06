#ifndef BEZIER_H
#define BEZIER_H

#include "drawarea.h"
#include <QVector>

constexpr float MINWL = 380;
constexpr float MAXWL = 780;
constexpr float MINFACTOR = 0;
constexpr float MAXFACTOR = 1.8;

class Bezier : public DrawArea
{
    Q_OBJECT
public:
    Bezier(CIEVector &cievector);
    void Draw();
    void Reset(int number);

    float X=-1, Y=-1, Z=-1;

signals:
    void DrawEvent();

private:

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    std::string labelsX[9] = {"380", "430", "480", "530", "580", "630", "680", "730", "780"};
    std::string labelsY[9] = {"0,2", "0,4", "0,6", "0,8", "1", "1,2", "1,4", "1,6", "1,8"};

    bool moving = false;
    int pointsCount = 2;
    int activeIndex;
    QVector<QPointF> points;

    QVector<QPointF> CalculateBezierCurve(const QVector<QPointF> &points);
    float CalculateIntegral(const QVector<QPointF> &points);
    float CalculateRecursiveBezier(const QVector<QPointF> &points, int first, int last, float t);
    void CalculateChromatic(const QVector<QPointF> &curve);


protected:
    void DrawPoint(QPainter &painter, const QPointF &point, QColor color = Qt::black);
    void DrawLine(QPainter &painter, const QLineF &line, QColor color = Qt::black, qreal width=3, Qt::PenStyle style=Qt::SolidLine);
};

#endif // BEZIER_H
