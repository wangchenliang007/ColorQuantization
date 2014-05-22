#ifndef HVCDATA_H
#define HVCDATA_H
#include <iostream>
using namespace std;

class HVCData
{
    public:
        HVCData();
        double hvc_h;
        double hvc_v;
        double hvc_s;
        virtual ~HVCData();
        HVCData& operator = (HVCData&  x){
            this -> hvc_h = x.hvc_h;
            this ->hvc_v =x.hvc_v;
            this ->hvc_s = x.hvc_s;
            return *this;
        }
       friend inline ostream& operator << (ostream& os, HVCData& d){
            os << d.hvc_h << endl;
            return os;
       }
};
#endif // HVCDATA_H
