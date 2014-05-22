#include "Color.h"

Color::Color()
{
    number = 0;
    hvcValue.hvc_h = 0;
    hvcValue.hvc_v = 0;
    hvcValue.hvc_s = 0;
    hk = 0;
    bk.avx = 0;
    bk.avy = 0;
    px = 0;
    py = 0;
    dk = 0;
}

Color::~Color()
{
    //dtor
}
