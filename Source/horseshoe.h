#ifndef HORSESHOE_H
#define HORSESHOE_H

#include "drawarea.h"

class HorseShoe : public DrawArea
{
public:
    HorseShoe(CIEVector &cievector);
    void Draw();
private:
    std::string labels[9] = {"0,1", "0,2", "0,3", "0,4", "0,5", "0,6", "0,7", "0,8", "0,9"};
};

#endif // HORSESHOE_H
