/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
   
    int height = theSource.getRows();
    int width = theSource.getColumns();
    MosaicCanvas* myMosaic = new MosaicCanvas(height, width);

    int size = theTiles.size();
    vector<Point<3>> points;
    map<Point<3>, int> tileAvgMap;
    for (int i = 0; i < size; i++){
      HSLAPixel tileColor = theTiles[i].getAverageColor();
      Point<3> p = convertToLAB(tileColor);
      tileAvgMap[p] = i;
      points.push_back(p);
      //cout << p << endl;
    }

    KDTree<3> tree(points);
    //tree.printTree(cout);

    for (int x = 0; x < height; x++) {
      for (int y = 0; y < width; y++)  {
        HSLAPixel currColor = theSource.getRegionColor(x, y);
        TileImage* tileImage = get_match_at_idx(tree, tileAvgMap, theTiles, theSource, x, y);
        myMosaic->setTile(x, y, tileImage);
      }
    } 

    return myMosaic;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    //cout << avgPoint << endl;
    //tree.printTree(cout);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);
    //cout << nearestPoint << endl;
    //cout << endl;

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
