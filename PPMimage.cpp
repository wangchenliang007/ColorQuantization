#include "PPMimage.h"

PPMimage::PPMimage()
{
    //ctor
    name = "";
    width = 0;
    height = 0;
    max_value = 0;           //header
    RGBFile = "";         // the file name of saving rgb information
    HSVFile = "";
    MunsellFile = "";
    //hvcLink = LinkList<HVCData>();
}

PPMimage::~PPMimage()
{
    //dtor
}
