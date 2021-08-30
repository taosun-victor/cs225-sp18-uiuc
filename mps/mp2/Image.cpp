#include <iostream>
#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using namespace std;
using namespace cs225;

void Image::lighten(){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l = min(pixel.l+0.1, 1.0);
        }
    }
}

void Image::lighten(double amount){

    int w = this->width();
    int h = this->height();
    
    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l = min(pixel.l+amount, 1.0);
        }
    }
}


void Image::darken(){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l = max(pixel.l-0.1, 0.0);
        }
    }
}


void Image::darken(double amount){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.l = max(pixel.l-amount, 0.0);
        }
    }
}


void Image::saturate(){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = min(pixel.s+0.1, 1.0);
        }
    }
}


void Image::saturate(double amount){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = min(pixel.s+amount, 1.0);
        }
    }
}


void Image::desaturate(){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = max(pixel.s-0.1, 0.0);
        }
    }
}


void Image::desaturate(double amount){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = max(pixel.s-amount, 0.0);
        }
    }
}


void Image::grayscale(){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            pixel.s = 0.0;
        }
    }
}


void Image::rotateColor(double degrees){

    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);
            double h_add = pixel.h + degrees;
            pixel.h = h_add - 360.0 * floor(h_add/360.0);
        }
    }
}


void Image::illinify(){
    
    int w = this->width(); 
    int h = this->height();

    for (int x=0; x<w; x++){
        for (int y=0; y<h; y++){
            HSLAPixel & pixel = this->getPixel(x,y);

            double di_O = min(abs(pixel.h-11), abs(360+11-pixel.h));
            double di_B = min(abs(pixel.h-216), abs(360+216-pixel.h));

            if (di_O <= di_B) {
                pixel.h = 11;
            } 
            else {
                pixel.h = 216;
            }
        }
    }
}


void Image::scale(double factor){	

    int w = this->width();
    int h = this->height();

    int new_w = int(w * factor);
    int new_h = int(h * factor);

    Image * old_image = new Image();
    *old_image = *this;

    this->resize(new_w, new_h);

    for (int x=0; x<new_w; x++){
        for (int y=0; y<new_h; y++){

            int old_y = y/factor;
            int old_x = x/factor;

            HSLAPixel & new_pixel = this->getPixel(x,y);
            HSLAPixel & old_pixel = old_image->getPixel(old_x, old_y);

            new_pixel.h = old_pixel.h;
            new_pixel.s = old_pixel.s;
            new_pixel.l = old_pixel.l;
            new_pixel.a = old_pixel.a;
        }
    }

    delete old_image;
    old_image = NULL;

}



void Image::scale(unsigned w, unsigned h){

    int w_old = this->width();

    double factor = (double)w/(double)w_old;

    this->scale(factor); 

}
