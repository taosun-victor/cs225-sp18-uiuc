#include <iostream>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {

    Image sc0220;
    sc0220.readFromFile("sc0220.png");
 
    Image cs_i;
    cs_i.readFromFile("cs_illinois.png");
    cs_i.scale(0.6);

    Image fi;
    fi.readFromFile("fighting_illini.png");
    fi.scale(4.0);

    Image cs;
    cs.readFromFile("cs.png");
    cs.scale(2.0);

 
    StickerSheet * my_sticker = new StickerSheet(sc0220, 5);

    my_sticker->addSticker(cs_i, 2, 600);
    my_sticker->addSticker(fi, 100, 1);
    my_sticker->addSticker(cs, 1600, 800);

    //my_sticker->changeMaxStickers(7);
    //my_sticker->changeMaxStickers(2);

    
    Image result = my_sticker->render();
    result.writeToFile("myImage.png");

    delete my_sticker;
    my_sticker = NULL;
 
 
    return 0;
}

