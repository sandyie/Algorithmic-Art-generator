/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"
#include <utility>
#include <cmath>

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  // Your code here.
  stats picStat = stats(imIn);
  pair<int,int> origin = make_pair(0,0);
  root = buildTree(picStat, origin, imIn.width(), imIn.height(), tol );

}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  // Your code here.
  Node * rNode = new Node (s, ul, w, h);;

  if (rNode->var <= tol) {
    return rNode;
  }
  
  if (w == 1 && h == 1) {
    return rNode;
  }
  
  int xSpilt = 0;
  int ySpilt = 0;

  pair<int, int> XYline = findBest (s, rNode, xSpilt, ySpilt); 
  xSpilt = XYline.first;
  ySpilt = XYline.second;

  pair<int, int> pairSW = make_pair(ul.first, ul.second + ySpilt);
  pair<int, int> pairNE = make_pair(ul.first + xSpilt, ul.second);
  pair<int, int> pairSE = make_pair(ul.first + xSpilt, ul.second + ySpilt);

  if (xSpilt == 0 && ySpilt!= 0) {
    rNode->NE = buildTree ( s, pairNE, w - xSpilt, ySpilt , tol );
    rNode->SE = buildTree ( s, pairSE , w - xSpilt, h - ySpilt , tol );
  }

  if (xSpilt != 0 && ySpilt == 0) {
    rNode->SW = buildTree ( s, pairSW , xSpilt, h - ySpilt , tol );
    rNode->SE = buildTree ( s, pairSE , w - xSpilt, h - ySpilt , tol );
  }

  if (xSpilt != 0 && ySpilt != 0) {
    rNode->NW = buildTree ( s, ul, xSpilt, ySpilt , tol );
    rNode->SW = buildTree ( s, pairSW , xSpilt, h - ySpilt , tol );
    rNode->NE = buildTree ( s, pairNE, w - xSpilt, ySpilt , tol );
    rNode->SE = buildTree ( s, pairSE , w - xSpilt, h - ySpilt , tol );
  }
  return rNode;
}


pair <int, int> SQtree:: findBest (stats & s, Node * toSplit, int xsp, int ysp) {
  pair<int,int> ul = toSplit->upLeft;
  int w = toSplit->width;
  int h = toSplit->height;
  int spitX = xsp;
  int spitY = ysp;
  double curMaxVar;
  double minVar = toSplit -> var;

  bool allEqual = true;

  for (int x = 0; x < w; x ++) {
    for (int y = 0; y < h; y++) {
      if (! (x == 0 && y == 0)) {
        
        pair<int,int> NEpair = make_pair(ul.first + x, ul.second); // NE pair
        pair<int,int> SWpair = make_pair(ul.first, ul.second + y);  // SW pair
        pair<int,int> SEpair = make_pair(ul.first + x, ul.second + y); // SE pair

        double NWval = s.getVar(ul, x, y); // upper left (for NW)
        double NEval = s.getVar(NEpair, w - x, y);   // upper right (for NE)
        double SWval = s.getVar(SWpair, x, h - y); // lower left (for SW)
        double SEval = s.getVar(SEpair, w - x, h - y); // lower right (for SE) 

        curMaxVar = max ({NWval,NEval,SWval, SEval});

        if (curMaxVar != minVar) {
          allEqual = false;
        }
        
        if (curMaxVar < minVar) {
          minVar = curMaxVar;
          spitX = x;
          spitY = y;
        }
      }
    }    
  }

  if (allEqual) {
    spitX =  (w / 2);
    spitY =  (h / 2);
  }
  
  pair <int, int> returnPair = make_pair(spitX, spitY);
  return returnPair;

}
  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  // Your code here.]
  PNG resultPic = PNG (root->width, root->height);

  renderTree (root, resultPic);
  return resultPic;
}

void SQtree::renderTree(Node* treePrev, PNG & picToDraw) {
  if (treePrev == NULL) {
    return;
  }

  if (treePrev->SE == NULL) {
    for (int x = treePrev->upLeft.first; x < (treePrev->upLeft.first) + treePrev -> width; x++) {
      for (int y = treePrev->upLeft.second; y< (treePrev->upLeft.second) + treePrev->height; y++) {
        RGBAPixel* currPic = picToDraw.getPixel(x,y);
        *currPic = treePrev->avg;
      }
    }
    return;
  }
  renderTree(treePrev->NW, picToDraw);
  renderTree(treePrev->NE, picToDraw);
  renderTree(treePrev->SW, picToDraw);
  renderTree(treePrev->SE, picToDraw);
}



/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  // Your code here.
  // Node * treeTop = root;
  // clearSub (root);
  // delete treeTop;

  clearSub(root);
}

void SQtree::clearSub(Node* parentNode) {
  if (parentNode == NULL) {
    return;
  }
  clearSub(parentNode->NW);
  clearSub(parentNode->NE);
  clearSub(parentNode->SW);
  clearSub(parentNode->SE);
  delete (parentNode);
  parentNode = NULL;
}

void SQtree::copy(const SQtree & other) {
  // Your code here.
  root = copyHelp (other.root);
}

SQtree::Node * SQtree::copyHelp (Node * thisCur) {
  if (thisCur != NULL) {
  Node * cur = new Node (thisCur->upLeft, thisCur->width, thisCur->height, thisCur->avg, thisCur->var);
  cur->NW = copyHelp(thisCur -> NW);
  cur->NE = copyHelp(thisCur -> NE);
  cur->SW = copyHelp(thisCur -> SW);
  cur->SE = copyHelp(thisCur -> SE);
  return cur;
  }
  return NULL;
}


int SQtree::size() {
  // Your code here.
  int totalNode = 0;
  totalNode = countChild (root);
  return totalNode;
}

int SQtree::countChild(Node* toCount) {
  if (toCount == NULL) {
    return 0; 
  }
  int totalNode;
  totalNode = 1 + countChild (toCount -> NW) + countChild (toCount -> NE) + countChild (toCount -> SW) + countChild (toCount -> SE); 
  return totalNode;
}