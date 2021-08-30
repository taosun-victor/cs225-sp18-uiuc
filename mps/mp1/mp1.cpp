#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
    PNG in_png;
    in_png.readFromFile(inputFile);

    int width = in_png.width();
    int height = in_png.height();

    PNG out_png(width, height);
    
    for (int x=0; x<width; x++){
        for (int y=0; y<height; y++){
            HSLAPixel * outPixel = out_png.getPixel(x,y);
            HSLAPixel * inPixel = in_png.getPixel(width-1-x,height-1-y);

            outPixel->h = inPixel->h;
            outPixel->s = inPixel->s;
            outPixel->l = inPixel->l;
            outPixel->a = inPixel->a;
        }
    }
	  
    out_png.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
    PNG png(width, height);
  // Part 3
  // Notice to the instructor and TA:
  // This part borrows the fractal algorithm and matlab code from the following source:
  // https://www.douban.com/note/230496472/
 

    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            HSLAPixel * pixel = png.getPixel(i, j);
            pixel->l = 0.0;
        }
    }

    const double Pi = 3.1415926;

    double a[4][7] = {{0.03, 0.0, 0.0, 0.45, 0.0, 0.0, 0.05},
                         {-0.03, 0.0, 0.0, -0.45, 0.0, 0.4, 0.15},
                         {0.56, -0.56, 0.56, 0.56, 0.0, 0.4, 0.4},
                         {0.56, 0.56, -0.56, 0.56, 0.0, 0.4, 0.4}};

    //double x0 = double(width)/2.0, y0 = double(height)/2.0;
    double x0 = 1.0, y0 = 1.0;
    double x1 = 1.0, y1 = 1.0;
    int x = 1, y = 1;

    for (int i=0; i<500000; i++){

        double r = ((double)rand() / (double)(RAND_MAX));

        if (r<=0.05){       
            x1=a[0][0]*x0+a[0][1]*y0+a[0][4];        
            y1=a[0][2]*x0+a[0][3]*y0+a[0][5];}
        else if ((r>0.05) && (r<=0.2)){
            x1=a[1][0]*x0+a[1][1]*y0+a[1][4];        
            y1=a[1][2]*x0+a[1][3]*y0+a[1][5];}
        else if ((r>0.2) && (r<=0.6)){
            x1=a[2][0]*x0+a[2][1]*y0+a[2][4];        
            y1=a[2][2]*x0+a[2][3]*y0+a[2][5];}
        else {
            x1=a[3][0]*x0+a[3][1]*y0+a[3][4];        
            y1=a[3][2]*x0+a[3][3]*y0+a[3][5];}  
 
        x0 = x1;
        y0 = y1; 

        x = int(min(x0*width/3.0 + width*0.5, double(width-1)));
        y = int(min(abs(0.8*height - y0*height/2.5), double(height-1)));

        HSLAPixel * pixel = png.getPixel(x, y);
        pixel->h = 0.5 * (sin(Pi*(double)x/(double)width) + cos(Pi*(double)y/(double)height)) * 360;
        pixel->s = 1.0;
        pixel->l = (double)y/(double)height;
        pixel->a = 1.0;
    }

    return png;
}
