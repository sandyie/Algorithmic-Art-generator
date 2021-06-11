// File:        pa3.cpp
// Author:      cs221 instructors
// Date:        2021-03-03
// Description: Partial test of PA3 functionality
//              Reads Point data from external files
//              Produces PNG images of the point sets

#include "sqtree.h"

int main() {
  PNG testPNG = PNG(3,3); // [0,2] width [0,2] height

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
        testPNG.getPixel(i,j)->r = 0;
        testPNG.getPixel(i,j)->g = 0;
        testPNG.getPixel(i,j)->b = 0;
    }
    
  }
  

  testPNG.getPixel(0,0)->r = 100;
  testPNG.getPixel(1,0)->r = 150;
  testPNG.getPixel(2,0)->r = 200;
  testPNG.getPixel(1,1)->r = 50;
  testPNG.getPixel(2,2)->r = 7;

  // R VALUES
  //   100  150  200
  //    0   50    0
  //    0    0    7


  testPNG.writeToFile("images/out/testsmall.png");

  stats c = stats(testPNG);
  
  // ---- test Constructor
  vector<vector<long>> sumRed = c.getSumRed();
  vector<vector<long>> sumsqRed = c.getSumsqRed();

  cout << "expected: 450  ||   actual: " << sumRed[2][0] << endl;
  cout << "expected: 300  ||   actual: " << sumRed[1][1] << endl;
  cout << "expected: 100  ||   actual: " << sumRed[0][2] << endl;
  cout << "expected: 507  ||   actual: " << sumRed[2][2] << endl;

  cout << "expected: 10000  ||   actual: " << sumsqRed[0][0] << endl;
  cout << "expected: 75049  ||   actual: " << sumsqRed[2][2] << endl;

  // ----- test getSum()

  cout << "expected: 50  ||   actual: " << c.getGetSum('r', make_pair(1,1), 1, 1) << endl;
  cout << "expected: 57  ||   actual: " << c.getGetSum('r', make_pair(1,1), 2, 2) << endl;
  cout << "expected: 400  ||   actual: " << c.getGetSum('r', make_pair(1,0), 2, 2) << endl;
  cout << "expected: 0  ||   actual: " << c.getGetSum('r', make_pair(0,1), 1, 2) << endl;

  // read in image
  PNG orig;
  orig.readFromFile("images/orig/small1.png");
  /*
  orig.readFromFile("images/orig/small2.png");
  orig.readFromFile("images/orig/pacman.png");
  orig.readFromFile("images/orig/huckleberry_hound.png");
  orig.readFromFile("images/orig/rocky.png");
  orig.readFromFile("images/orig/rocky_bullwinkle.png");
  orig.readFromFile("images/orig/colour.png");
  orig.readFromFile("images/orig/klee-flora-on-sand.png");
  orig.readFromFile("images/orig/stanley-totem-poles.png");
  */
  
  // use it to build a sqtree (try other tolerances)
  SQtree t(orig,10.0);

  // copy the tree (to show you can)
  SQtree tCopy(t);

  // render the sqtree
  PNG pic = t.render();

  // write it out
  pic.writeToFile("images/out/small1.png");

  return 0;
}
