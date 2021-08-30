#include "../cs225/catch/catch.hpp"
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../list.h"

using namespace cs225;
using namespace std;


TEST_CASE("List::insertFront", "[weight=1][part=1]") {
  List<int> list;
  cout << "an empty list" << endl;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); cout << "fill " << i << endl; }
  //list.printList();
  REQUIRE(list.size() == 10);
}

TEST_CASE("List::insertBack", "[weight=1][part=1]") {
  List<int> list;
  for (unsigned i = 0; i < 10; i++) { list.insertBack(i); }
  REQUIRE(list.size() == 10);
}

TEST_CASE("List::reverse", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserve.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverse();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserve.png");
  INFO("Output image `out` saved as actual-reverse.png");

  REQUIRE( out == expected );
}

/*
TEST_CASE("List::reverse_num", "[weight=1][part=1]"){
  List<int> list;

  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }
  list.printList();
  cout << endl;
 
  //list.reverse(0,9);
  //list.printList();
  //cout << endl;
 
  //list.reverse();
  //list.printList();
  //cout << endl;


  list.reverse(0,1);
  list.printList();
  cout << endl; 

  list.reverse(1,1);
  list.printList();
  cout << endl;

  list.reverse(1,2);
  list.printList();
  cout << endl;

  list.reverse(5,5);
  list.printList();
  cout << endl; 

  list.reverse(5,6);
  list.printList();
  cout << endl;
 
  list.reverse(8,9);
  list.printList();
  cout << endl; 

  list.reverse(9,9);
  list.printList();
  cout << endl;


  //list.reverse();
  //list.printList();

   
  list.reverseNth(1);
  list.printList();
  cout << endl;
  list.reverseNth(2);
  list.printList();
  cout << endl;

  list.reverseNth(3);
  list.printList();
  cout << endl;
  list.reverseNth(4);
  list.printList();
  cout << endl;

  list.reverseNth(5);
  list.printList();
  cout << endl;
  list.reverseNth(6);
  list.printList();
  cout << endl;

  list.reverseNth(7);
  list.printList();
  cout << endl;
  list.reverseNth(8);
  list.printList();
  cout << endl;
  
  list.reverseNth(9);
  list.printList();
  cout << endl;
  list.reverseNth(10);
  list.printList();
  cout << endl;
  
} */



TEST_CASE("List::reverseNth #1", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserveN_1.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 20);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserveN_1.png");
  INFO("Output image `out` saved as actual-reverseN_1.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::reverseNth #2", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserveN_2.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 61);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserveN_2.png");
  INFO("Output image `out` saved as actual-reverseN_2.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::waterfall", "[weight=1][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-waterfall.png");

  List<HSLAPixel> list = imageToList(in);
  list.waterfall();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-waterfall.png");
  INFO("Output image `out` saved as actual-waterfall.png");

  REQUIRE( out == expected );
}
