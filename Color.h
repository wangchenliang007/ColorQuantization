#ifndef COLOR_H
#define COLOR_H
#include "HVCData.h"

struct Baricenter{
    double avx, avy;         //average x and average y
};

class Color
{
    public:
        Color();
        ~Color();
        int number;
        HVCData hvcValue;
        int px, py;     // sum of all x
        int sx, sy;     // sum of all quare(x)
        double hk;
        Baricenter bk;
        double dk;
};

#endif // COLOR_H
