#include <iostream>
#include <cmath>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"

using namespace std;
using namespace cs225;

// be careful with the image_count and image_max
// manually initialize pointers to be NULL is needed.
void StickerSheet::_destroy(){

    if (x_ != NULL){
        delete [] x_;
        x_ = NULL;
    }

    if (y_ != NULL){
        delete [] y_;
        y_ = NULL;
    }

    if (base_ != NULL){
        delete base_;
        base_ = NULL;
    }


    if (images_ != NULL){
        for (int i=0; i<image_max; i++){
            if (images_[i] != NULL){
                delete images_[i];
                images_[i] = NULL;
            }
        }

        delete [] images_;
        images_ = NULL;
    }
    
    image_count = 0;
    image_max = 0;


}


void StickerSheet::_copy(const StickerSheet & other){

    image_max = other.image_max;
    image_count = other.image_count;

    base_ = new Image(*(other.base_)); 

    x_ = new int [image_max];
    y_ = new int [image_max];
    images_ = new Image * [image_max];

    for (int i=0; i<image_max; i++){
        x_[i] = -1;
        y_[i] = -1;
        images_[i] = NULL;
    }

    for (int i=0; i<image_max; i++){
        if (other.images_[i] != NULL){
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
            images_[i] = new Image(*(other.images_[i]));
        }
    }


}


StickerSheet::StickerSheet(const Image & picture, unsigned max){

    image_max = max;
    image_count = 0;
    base_ = new Image(picture);
   
    x_ = new int [image_max];
    y_ = new int [image_max];
    images_ = new Image * [image_max];

    for (int i=0; i<image_max; i++){
        x_[i] = -1;
        y_[i] = -1;
        images_[i] = NULL;
    }
}


StickerSheet::~StickerSheet(){
    _destroy();    
}


StickerSheet::StickerSheet(const StickerSheet & other){
    _copy(other); 
}


const StickerSheet & StickerSheet::operator=(const StickerSheet & other){

    if (this != &other){
        _destroy();
        _copy(other);
    }

    return *this;
}


// this function is written in a strange way. Need double check.
void StickerSheet::changeMaxStickers(unsigned newMax){

    int boundary = min(image_max, int(newMax));
    
    StickerSheet * oldStickerSheet = new StickerSheet(*this);

    _destroy();

    image_max = newMax;
    image_count = 0;

    base_ = new Image(*(oldStickerSheet->base_)); 

    x_ = new int [newMax];
    y_ = new int [newMax];
    images_ = new Image * [newMax];


    for (int i=0; i<image_max; i++){
        x_[i] = -1;
        y_[i] = -1;
        images_[i] = NULL;
    }

    for (int i=0; i<boundary; i++){
        if (oldStickerSheet->images_[i] != NULL){
            x_[i] = oldStickerSheet->x_[i];
            y_[i] = oldStickerSheet->y_[i];
            images_[i] = new Image(*(oldStickerSheet->images_[i]));
            image_count += 1;
        }
    }

   
    delete oldStickerSheet;
    oldStickerSheet = NULL;
}



int StickerSheet::addSticker(Image & newSticker, unsigned x, unsigned y){

    int feedback = -1;    

    if (image_count < image_max){
        for (int i=0; i<image_max; i++){
            if (images_[i] == NULL){
                x_[i] = x;
                y_[i] = y;
                images_[i] = new Image(newSticker);
                feedback = i;
                image_count += 1;
                break;
            }
        }
    }
 
    return feedback;
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){

    bool feedback = false;

    if ((int(index) < image_max) && (images_[index] != NULL)) {
        x_[index] = x;
        y_[index] = y;
        feedback = true;    
    }
   
    return feedback;
}


void StickerSheet::removeSticker(unsigned index){
    
    if ((int(index) < image_max) && (images_[index] != NULL)){
        x_[index] = -1;
        y_[index] = -1;
        delete images_[index];
        images_[index] = NULL;
        image_count -= 1;
    }
}


Image * StickerSheet::getSticker(unsigned index) const{

    Image * feedback = NULL;
   
    if ((int(index) < image_max) && (images_[index] != NULL)){    
        feedback = images_[index];
    }

    return feedback;
}


Image StickerSheet::render() const {

    int w_base = base_->width();
    int h_base = base_->height();

    unsigned int w_render = w_base;  
    unsigned int h_render = h_base;

    for (int i=0; i<image_max; i++){
        if (images_[i] != NULL){

            if ((images_[i]->width() + x_[i]) > w_render)
                w_render = images_[i]->width() + x_[i];

            if ((images_[i]->height() + y_[i]) > h_render)
                h_render = images_[i]->height() + y_[i];

        }
    } 

    Image render;
    render.resize(w_render, h_render);

    for (int x=0; x<w_base; x++){
        for (int y=0; y<h_base; y++){

            HSLAPixel & base_pixel = base_->getPixel(x,y);
            HSLAPixel & render_pixel = render.getPixel(x,y);
    
            render_pixel.h = base_pixel.h;
            render_pixel.s = base_pixel.s;
            render_pixel.l = base_pixel.l;
            render_pixel.a = base_pixel.a;
        }
    }


 
    for (int i=0; i<image_max; i++){
        if (images_[i] != NULL){

            int wi = images_[i]->width();
            int hi = images_[i]->height();

            for (int x=0; x<wi; x++){
                for (int y=0; y<hi; y++){

                    HSLAPixel & image_pixel = images_[i]->getPixel(x,y);

                    if (image_pixel.a != 0){

                        HSLAPixel & render_pixel = render.getPixel(x + x_[i], y + y_[i]);

                        render_pixel.h = image_pixel.h;
                        render_pixel.s = image_pixel.s;
                        render_pixel.l = image_pixel.l;
                        render_pixel.a = image_pixel.a;

                    }
                }
            }
        }
    }

    return render;

}


