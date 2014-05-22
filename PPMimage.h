#ifndef PPMIMAGE_H
#define PPMIMAGE_H
#include <string>
#include "LinkList.h"
#include "HVCData.h"
#include "Color.h"
using namespace std;

class PPMimage
{
    public:
        PPMimage();
        virtual ~PPMimage();
        string name;
        int width, height, max_value;           //header
        string RGBFile;         // the file name of saving rgb information
        string HSVFile;
        string MunsellFile;     //HVC
        LinkList<HVCData>   hvcLink;
        LinkList<Color> colorSpaceLink;
        int numOfColorsInSpace;
    protected:
    private:
};

#endif // PPMIMAGE_H
