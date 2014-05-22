#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <string.h>
#include <Windows.h>
#include "PPMimage.h"
#include "HVCData.h"
#include "LinkNode.h"
#include "Color.h"
using namespace std;

#define imageWidth 640
#define imageHeight 480
#define maxValue 255
#define PI 3.1415926
#define SIMI_THRES 0.0

 double minV(double a, double b, double c){
    double smallest = a;
    for(int i=0;i<3;++i){
        if(a < smallest)    smallest = a;
        if(b < smallest)    smallest = b;
        if(c < smallest)    smallest = c;
    }
    return smallest;
};

double minCompa(double a, double b){
    return (a < b) ? a : b;
};

double maxV(double a, double b, double c){
    double maxim = a;
    for(int i = 0; i < 3; ++i){
        if(a > maxim)    maxim = a;
        if(b > maxim)    maxim = b;
        if(c > maxim)    maxim = c;
    }
    return maxim;
};
double maxCompa(double a, double b){
    return (a > b) ? a : b;
};

PPMimage read_ppm(const char* file_name);
bool finder(LinkList<Color> cp, HVCData& d, LinkNode<Color> * &position, double thres);
PPMimage compute(string filename);
double similarity(PPMimage p1, PPMimage p2);
vector<double> calcSimilarityByKeyWord(string keyWord);
vector<string> get_all_file_names_within_folder_by_keyword(string folder,vector<string> key_words);
double calcSimilarity(string imageName1,string imageName2);
int main()
{

    //calcSimilarity("images/beach2.ppm", "images/beach5.ppm);
    //char * key_word= "sunset";
    vector<string> key_words;//关键字列表
    key_words.push_back("sunset");//关键字
    key_words.push_back("beach");//关键字
    vector<string> v = get_all_file_names_within_folder_by_keyword("images/",key_words);
    cout<<"Possible similar images are:"<<endl;
    for(int i = 0 ; i<v.size();i++){
        cout<<v[i]<<endl;
    }
    cout<<"count = "<<v.size()<<endl;
    cout<<"Calculate similarity";
    for(int i = 0 ; i<v.size();i++){
        string originImage = "images/beach2.ppm";
        string targetImage = "images/"+v[i];
        cout<<"similarity between "<<originImage<<" and "<<targetImage<<" is "<<calcSimilarity(originImage,targetImage)<<endl;
    }

    return 0;
}
double calcSimilarity(string imageName1,string imageName2){

    PPMimage image1 = compute(imageName1);
    PPMimage image2 = compute(imageName2);

    /*ofstream ColorOutfile("beach1_colorSpace.txt");
     for (LinkNode<Color> * p = image1.colorSpaceLink.head; p != NULL; p = p -> next) {
            ColorOutfile << p -> data.hk << " " << p -> data.bk.avx << " " << p -> data.bk.avy << " " << p -> data.dk <<" " << p -> data. number << "\n";
     }
    ColorOutfile.close();*/

    double similarity_Value = similarity(image1, image2);
    cout <<similarity_Value << endl;
    return similarity_Value;
}
vector<double>  calcSimilarityByKeyWord(string keyWord){
    vector<double> v;
    return v;
}
vector<string> get_all_file_names_within_folder_by_keyword(string folder,vector<string> key_words){
    vector<string> filenames;

    char search_path[200];
    sprintf(search_path,"%s*.*",folder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path,&fd);
    if(hFind!=INVALID_HANDLE_VALUE){
            do{
                if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
                        string fname = fd.cFileName;
                        if(key_words.empty()){
                            filenames.push_back(fd.cFileName);
                        }else{
                            for(int i = 0 ; i<key_words.size();i++){
                        string key_word = key_words[i];
                        if(!key_word.empty() && fname.find(key_word)==0){
                            filenames.push_back(fd.cFileName);
                        }else if(key_word.empty()){
                            //如果关键为空则把该目录下所有的文件名都返回
                            filenames.push_back(fd.cFileName);
                        }
                        }

                        }

                }
            }while(::FindNextFile(hFind,&fd));
            ::FindClose(hFind);
    }
    return filenames;
}
double similarity(PPMimage p1, PPMimage p2){        //Spatial Chromatic distance
    double sm = 0.0;
    ofstream ColorOutfile("output.txt");

    for (LinkNode<Color> * p = p1.colorSpaceLink.head; p != NULL; p = p -> next){
        LinkNode<Color> * q;
        double dis = 0;
        if (finder(p2.colorSpaceLink, p -> data.hvcValue, q, 0.0)==true){
                dis = pow((p -> data.bk.avx -  q -> data.bk.avx), 2.0) + pow((p -> data.bk.avy -  q -> data.bk.avy), 2.0);
                dis = sqrt(dis);
                double p1 = minCompa(p -> data.hk, q -> data.hk);
                double p2 = (sqrt(2.0) - dis)/sqrt(2.0);
                double p3 = minCompa(p -> data.dk, q -> data.dk)/maxCompa(p -> data.dk, q -> data.dk);
                sm += ( p1 * (p2 + p3));
                //p2.colorSpaceLink.deleteNode(q);
                ColorOutfile << dis << " " << p1 <<" "<< p2 <<" "<< p3 <<" "<< sm << "\n" ;
        }

    }
    ColorOutfile.close();
    return (int)(sm * 10000.0 + 0.5) / 10000.0;
}

PPMimage compute(string filename){
    PPMimage image = read_ppm(filename.c_str());
    int k = 0;
    for (LinkNode<HVCData> * p = image.hvcLink.head; p != NULL; p = p -> next) {
            LinkNode<Color> * position;
            if(finder(image.colorSpaceLink, p -> data, position, SIMI_THRES) == false){
                //cout << "into false loop: k = "  << k <<"\n";
                Color tmpColor;
                tmpColor.hvcValue.hvc_h = p -> data.hvc_h;
                tmpColor.hvcValue.hvc_v = p -> data.hvc_v;
                tmpColor.hvcValue.hvc_s = p -> data.hvc_s;

                tmpColor.number ++;
                tmpColor.px += (k/image.width)/image.width;
                tmpColor.py += (k % image.width)/image.height;
                tmpColor.sx += pow((k/image.width)/image.width, 2.0);
                tmpColor.sy += pow( (k % image.width)/image.height, 2.0);
                image.colorSpaceLink.add(tmpColor);
            }else{
                if (position != NULL) {
                    position->data.number ++;
                    position->data.px += (k/image.width)/image.width;
                    position->data.py += (k % image.width)/image.height;
                    position->data.sx += pow((k/image.width)/image.width, 2.0);
                    position->data.sy += pow((k % image.width)/image.height, 2.0);
                }
            }
            k++;
    }
    cout << "HVClength: " <<image.hvcLink.listLength << "\n";
    cout << "ColorLength: " << image.colorSpaceLink.listLength << "\n";

    ofstream dkOutfile("dk.txt");

    for (LinkNode<Color> * p = image.colorSpaceLink.head; p != NULL; p = p -> next) {
            p -> data.hk = (double)(p -> data.number )/ (image.hvcLink.listLength);
            p -> data.bk.avx = (1.0 / image.width) * (1.0 / p -> data.number) * p -> data.px;
            p -> data.bk.avy = (1.0 / image.height) * (1.0 / p -> data.number) * p -> data.py;
            double distance = p -> data.sx + p -> data.sy -  p -> data.number * pow(p -> data.bk.avx, 2.0) - p -> data.number * pow(p -> data.bk.avy, 2.0);
            p -> data.dk = sqrt((1.0 / p -> data.number) * distance);
            p -> data.dk = (int)(p -> data.dk * 10000.0 +0.5)/10000.0;
            dkOutfile << p -> data.dk << endl;
    }
    dkOutfile.close();
    return image;
}

bool finder(LinkList<Color> cp, HVCData& d, LinkNode<Color> * &position, double thres){
    for(LinkNode<Color> * p = cp.head; p != NULL; p = p -> next){
        //cout << "into for loop; \n";
        if( fabs(p -> data.hvcValue.hvc_h - d.hvc_h) <= thres && fabs(p -> data.hvcValue.hvc_v - d.hvc_v) <= thres && fabs(p -> data.hvcValue.hvc_s - d.hvc_s) <= thres){
            position = p;
            return true;
        }
    }
    position = NULL;
    return false;
}

PPMimage read_ppm(const char* file_name) {
    PPMimage tmpImage;
    ifstream fin(file_name,  std::ifstream::binary);
	if (fin.fail())
		cout<<"Could not open the file!"<<endl;

	string readline;
    //image size & max_value
    unsigned int width = 0 , height = 0, max_value = 0;
    string imageName(file_name);
    imageName = imageName.substr(imageName.find('/')+1, imageName.find('.') - 1 - imageName.find('/'));
    tmpImage.name = imageName;      //assigning value
    string tmpName = imageName;
    string outfilename = tmpName.append("_rgb.txt");
    //ofstream outfile(imageName.append("_rgb.txt").c_str() );  // imageName_rgb.txt
     tmpImage.RGBFile = outfilename;
     //cout << outfilename << endl;
    ofstream rgbOutfile(outfilename.c_str() );         // outfilename : imagename + _rgb.txt
    tmpName = tmpName.substr(0, tmpName.find('_') );
    ofstream hsvOutfile(tmpName.append("_hsv.txt").c_str());
    tmpImage.HSVFile = tmpName;
    //cout << tmpName << endl;
    tmpName = tmpName.substr(0, tmpName.find('_') );
    ofstream hvcOutfile(tmpName.append("_hvc.txt").c_str());
    tmpImage.MunsellFile = tmpName;
    //cout << tmpName << endl;

   // tmpImage.hvcArray = new HVCNode[width*height];

	if (getline(fin, readline, '\n'))       //ppm file has contents ; readline is the header for this ppm file.  such as this one : P6 640 480 255\n
	{
	    //cout << "Header length: " << readline.length()<< endl;
	    if ( readline[1] != '6' )
			cout<<"Invalid PPM header or signature"<<endl;
        else {
            //cout << readline << endl;
            int spacePos1, spacePos2, spacePos3;        // the index of three spaces
            spacePos1 = readline.find(" ");
            spacePos2 = readline.find(" ",spacePos1+1);
            spacePos3 = readline.find(" ",spacePos2+1);
            //cout << "backspace pos: " << spacePos1 << " "<< spacePos2 <<" " << spacePos3<< endl;
            for(int i =spacePos2 - 1; i > spacePos1 ; --i ){        // width of the image
                width += (readline[i]-'0')*exp((spacePos2-1-i)*log(10));     //using pow(x,y) will not be accurate for int
            }
            for (int i = spacePos3 - 1; i > spacePos2; --i ){       // height of the image
                height += (readline[i]-'0')*exp((spacePos3-1-i)*log(10));
            }
            for(int i = readline.length()-1; i >spacePos3;--i){         //max value for each r,g or b(usually 255)
                max_value += (readline[i]-'0')*exp((readline.length()-1-i)*log(10));
            }
            //cout << "width: " << width<< endl << "height: " << height << endl << "maxValue: " << max_value<< endl;
            tmpImage.height = height;
            tmpImage.width = width;
            tmpImage.max_value = max_value;
        }
	}else
		cout<<"Cannot read the PPM type!"<<endl;

	double inv_max_value = 1.0 / (double)max_value;
	string rgb( ( istreambuf_iterator<char>(fin) ),istreambuf_iterator<char>() );
	if ( rgb.size() != (width*height)*3){              // 15 is the length of header + '/n'
        cout << "Invalid pixel number!" << endl;
        cout << rgb.size() << endl;
        exit(1);
	}
    unsigned char red;
	unsigned char green;
	unsigned char blue;
	//vector<RGBColor> pixel;
	for (unsigned int i = 0; i < (width*height) ; i++){
		red		= rgb[ 3*i ];
		green	= rgb[ 3*i + 1 ];
		blue	= rgb[ 3*i + 2 ];
		double r = red   * inv_max_value;
		double g = green * inv_max_value;
		double b = blue  * inv_max_value;
		//pixels.push_back(RGBColor(r, g, b));
		//cout << "i: " << i<< ",r: "<< r <<", g: " << g <<", b: "<<b<<endl;
		if (rgbOutfile.is_open()){
            rgbOutfile << (int)(r  * 100 + 0.5)/100.0<<" "<< (int)(g  * 100 + 0.5)/100.0 << " " << (int)(b  * 100 + 0.5)/100.0 << "\n";
		}

		//**************************************convert to HSV******************************
		double v = pow(3.0, -0.5)*(r+g+b);
		double s = 1 - pow(3.0, 0.5)/v*minV(r,g,b);
        double down = pow((r-g)*(r-g) + (r-b)*(g-b), 0.5);
        double t = cos(0.5*(2*r-g-b)/down);
        double angle = 1/t;
        double h;
        if( g>=b )  h = angle;
        else    h = 2*PI - angle;
        if (hsvOutfile.is_open()){
            hsvOutfile << (int)(h  * 100 + 0.5)/100.0 << " " << (int)(s  * 100 + 0.5)/100.0 << " " << (int)(v  * 100 + 0.5)/100.0 << "\n";
        }

        /*************************************************Munsell*********************/
        double hvc_h, hvc_v, hvc_s;
        double m = maxV(r, g, b);
        double n = minV(r, g, b);
        hvc_v = m;
        if (m == 0){
            hvc_s = 0;
        }else { hvc_s = (m - n)/m; }

        if( hvc_s == 0){
            hvc_h = 0;
        }else if ( r == m && g >= b){
            hvc_h = 60 * (g - b) / (m - n);
        }else if ( r == m && g < b){
            hvc_h = 360 + 60 * (g - b) / (m - n);
        }else if (g == m){
            hvc_h = 120 + 60 * (b -r ) / (m - n);
        }else if (b == m){
            hvc_h = 240 + 60 * (r - g) / (m - n);
        }
        //hvc_h = (int)(hvc_h * 100.0 + 0.5)/100.0;
        //hvc_v = (int)(hvc_v * 100.0 + 0.5)/100.0;
        //hvc_s = (int)(hvc_s * 100.0  + 0.5)/100.0;

        hvc_h = (int)(hvc_h  + 0.5);
        hvc_v = (int)(hvc_v  + 0.5);
        hvc_s = (int)(hvc_s   + 0.5);

        if (hvcOutfile.is_open()){
                hvcOutfile << hvc_h<< " " << hvc_v << " " << hvc_s << "\n";
        }
        HVCData tmpHvc;
        tmpHvc.hvc_h = hvc_h;
        tmpHvc.hvc_v =  hvc_v;
        tmpHvc.hvc_s = hvc_s;

        //tmpImage.hvcLink;
        HVCData tmpData;
        tmpData.hvc_h = hvc_h;
        tmpData.hvc_v = hvc_v;
        tmpData.hvc_s = hvc_s;
        tmpImage.hvcLink.add(tmpData);
        /***************************************************************************/
	}
	rgbOutfile.close();
	hsvOutfile.close();
	hvcOutfile.close();
	fin.close();
	//*************************************************************************************************************have read the rgb and hsv, and hvc***************************
	return tmpImage;
}

//note: readline will continue to read the file from the position end last time. NOT reading from the beginning.
