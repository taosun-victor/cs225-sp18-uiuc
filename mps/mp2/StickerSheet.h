/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using namespace std;
using namespace cs225;


class StickerSheet {

    public:
        StickerSheet(const Image & picture, unsigned max);   
        ~StickerSheet();
        StickerSheet(const StickerSheet & other);
        const StickerSheet & operator=(const StickerSheet & other);
        void changeMaxStickers(unsigned newMax);
        int addSticker(Image & newSticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index) const;
        Image render() const;
        
    private:
        Image * base_;
        Image ** images_;
        int * x_;
        int * y_;
        int image_max;
        int image_count;
        void _copy(const StickerSheet & other);
        void _destroy();
};
#endif
 

