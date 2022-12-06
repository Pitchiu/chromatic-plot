 #include "bezier.h"

Bezier::Bezier(CIEVector &cievector) : DrawArea(cievector)
{
    setMouseTracking(true);
}

void Bezier::DrawLambda()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);

    DrawMargin(painter, labelsX, labelsY);

    QVector<QPointF> lambdaVecX(cievector.size());
    QVector<QPointF> lambdaVecY(cievector.size());
    QVector<QPointF> lambdaVecZ(cievector.size());

    for(int i = 0; i<cievector.size(); i++)
    {
        lambdaVecX[i] = QPointF(cievector[i].waveLength, cievector[i].x);
        lambdaVecY[i] = QPointF(cievector[i].waveLength, cievector[i].y);
        lambdaVecZ[i] = QPointF(cievector[i].waveLength, cievector[i].z);
    }
    for(int i=0; i<cievector.size()-1; i++)
    {
        DrawLine(painter, QLineF(lambdaVecX[i],lambdaVecX[i+1]), Qt::red, 3);
        DrawLine(painter, QLineF(lambdaVecY[i],lambdaVecY[i+1]), Qt::green, 3);
        DrawLine(painter, QLineF(lambdaVecZ[i],lambdaVecZ[i+1]), Qt::blue, 3);
    }
    update();
}

void Bezier::Draw()
{
    image.fill(qRgb(255, 255, 255));
    QPainter painter(&image);

    DrawMargin(painter, labelsX, labelsY);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for(int i=0; i<points.size(); i++)
    {
        DrawPoint(painter, points[i], Qt::red);
    }
    DrawLine(painter, QLineF(points[0], QPointF(points[0].x(),0)));
    DrawLine(painter, QLineF(points[pointsCount-1], QPointF(points[pointsCount-1].x(), 0)));

    QVector<QPointF> curve = CalculateBezierCurve(points);
    for(int i=0; i<curve.size()-2; i++)
        DrawLine(painter, QLineF(curve[i], curve[i+1]));

    for(int i=0; i<pointsCount-1; i++)
    {
        DrawLine(painter, QLineF(points[i],points[i+1]), Qt::red, 2, Qt::DashLine);
    }
    CalculateChromatic(curve);


    update();
}

void Bezier::CalculateChromatic(const QVector<QPointF> &curve)
{
    int first=-1;
    int n = curve.size();

    for(int i=0; i<cievector.size(); i++)
    {
        if((int)curve.first().x() == cievector[i].waveLength)
        {
            first = i;
            break;
        }
    }
    if(first==-1 || n > cievector.size() - first) return;

    QVector<QPointF> curveX(n), curveY(n), curveZ(n);
    for(int i = 0; i<curve.size(); i++, first++)
    {
        CIE cie = cievector[first];
        QPointF curvePoint = curve[i];
        curveX[i] = QPointF(curvePoint.x(), curvePoint.y()*cie.x);
        curveY[i] = QPointF(curvePoint.x(), curvePoint.y()*cie.y);
        curveZ[i] = QPointF(curvePoint.x(), curvePoint.y()*cie.z);
    }
    X = CalculateIntegral(curveX);
    Y = CalculateIntegral(curveY);
    Z = CalculateIntegral(curveZ);
}


void Bezier::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;
    QPointF pos = event->pos();


    if(!moving)
    {
        for(int i=0; i< points.size(); i++)
        {
            QPointF transformed(points[i].x() - 230, (2.0 - points[i].y())*250);
            if(QLineF(transformed, pos).length() < 10)
            {
                moving = true;
                activeIndex = i;
                return;
            }
        }
    }

    moving = false;
}

void Bezier::mouseMoveEvent(QMouseEvent *event)
{
    if(!moving) return;
    QPointF position(event->pos().x() + 230, 2.0f - ((float)event->pos().y()/250.0f));

    if(position.x() > MAXWL || position.x()<MINWL || position.y() <MINFACTOR || position.y()>MAXFACTOR)
        return;
    if(activeIndex != 0 && position.x() <= points[activeIndex-1].x())
        return;
    if(activeIndex != pointsCount-1 && position.x() >= points[activeIndex+1].x())
        return;

    points[activeIndex] = position;
    DrawEvent();
}

void Bezier::Reset(int number)
{
    pointsCount = number;
    points.clear();
    float step = (MAXWL-MINWL)/(number-1);
    float mid = 0.9;

    points.append(QPointF(MINWL, mid));
    QPointF currentPoint(MINWL + step, mid +0.2);
    for(int i=0; i<number-2; i++)
    {
        points.append(currentPoint);
        currentPoint.setX(currentPoint.x() + step);
    }
    points.append(QPointF(MAXWL, mid));

    DrawEvent();
}


void Bezier::DrawPoint(QPainter &painter, const QPointF& point, QColor color)
{
    painter.setPen(QPen(color, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPoint newpoint(point.x() -230, 250*(2.0-point.y()));
    painter.drawPoint(newpoint);
}

void Bezier::DrawLine(QPainter &painter, const QLineF &line, QColor color, qreal width, Qt::PenStyle style)
{
    painter.setPen(QPen(color, width, style, Qt::RoundCap, Qt::RoundJoin));
    QPoint p1(line.p1().x() -230, 250*(2.0-line.p1().y()));
    QPoint p2(line.p2().x() -230, 250*(2.0-line.p2().y()));

    painter.drawLine(p1, p2);
}

QVector<QPointF> Bezier::CalculateBezierCurve(const QVector<QPointF> &points)
{
    int first = points.first().x();
    int last  = points.last().x();
    int size = last - first + 1;
    QVector<QPointF> result(size);
    //t scaled to 0-1
    for(int x = first, i=0; x<=last; x++, i++)
    {
        float t = (float)(x-first)/(float)(last - first);
        result[i] = QPointF(x, CalculateRecursiveBezier(points, 0, points.size()-1,t));
    }
    return result;
}

void Bezier::GenerateEqualSpectrum()
{
    for(int i=0; i < pointsCount; i++)
    {
        points[i].setY(1.0);
    }
    DrawEvent();
}


float Bezier::CalculateRecursiveBezier(const QVector<QPointF> &controlPoints, int first, int last, float t)
{
    if(first==last)
        return controlPoints[first].y();
    return (1.0-t)*CalculateRecursiveBezier(controlPoints, first, last-1, t) + t*CalculateRecursiveBezier(controlPoints, first+1, last, t);
}


float Bezier::CalculateIntegral(const QVector<QPointF> &points)
{
    float step = (points.last().x()-points.first().x())/(points.size()-1);
    float sum = 0;
    for(int i=0; i < points.size()-1; i++)
        sum+= points[i].y()*step;
    return sum;
}

void Bezier::Save()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "", "*.txt");
    QFile f( fileName );
    f.open(QIODevice::WriteOnly);

    if(f.isOpen())
    {
        QTextStream out(&f);
        for(int i=0; i< pointsCount; i++)
            out << points[i].x() << " " <<points[i].y() <<"\n";
        f.close();
    }
}

void Bezier::Load()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", "", "*.txt");

    QFile f( fileName );
    f.open(QIODevice::ReadOnly);

    if(f.isOpen())
    {
        QTextStream in(&f);
        QString line;
        points.clear();
        line = in.readLine();
        while(!line.isNull())
        {
            QStringList list = line.split(" ");
            if(list.size()!=2) break;
            QPointF point = QPointF(list[0].toFloat(), list[1].toFloat());
            points.append(point);
            line=in.readLine();
        }
        pointsCount = points.size();
        f.close();
        DrawEvent();
    }
}
