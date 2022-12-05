#ifndef BEZIER_H
#define BEZIER_H

#include "drawarea.h"

class Bezier : public DrawArea
{
public:
    Bezier(CIEVector &cievector);
    void Draw();

private:
    std::string labelsX[9] = {"380", "430", "480", "530", "580", "630", "680", "730", "780"};
    std::string labelsY[9] = {"0,2", "0,4", "0,6", "0,8", "1", "1,2", "1,4", "1,6", "1,8"};

};

#endif // BEZIER_H
