
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG png1;
  png1.readFromFile("./group-presentations-team.png");

  BFS bfs(png1, Point(150,150), 0.2);
  MyColorPicker mypicker((double)png1.width(), (double)png1.height());

  FloodFilledImage myImage1(png1);
  myImage1.addFloodFill(bfs, mypicker);
  
  Animation animation1 = myImage1.animate(1000);
  PNG lastFrame1 = animation1.getFrame(animation1.frameCount() -1);
  lastFrame1.writeToFile("last1.png");
  animation1.write("first.gif");

// -----------------------------------------------------------------------

  PNG png2;
  png2.readFromFile("./last1.png");

  DFS dfs(png2, Point(8,8), 1.02);
  HSLAPixel color1(270, 1, 0.5);
  SolidColorPicker solid(color1);

  FloodFilledImage myImage2(png2);
  myImage2.addFloodFill(dfs, solid);
  
  Animation animation2 = myImage2.animate(1000);
  PNG lastFrame2 = animation2.getFrame(animation2.frameCount() -1);
  lastFrame2.writeToFile("myFloodFill.png");
  animation2.write("second.gif");

  system("convert first.gif second.gif result.gif");

  return 0;
}
