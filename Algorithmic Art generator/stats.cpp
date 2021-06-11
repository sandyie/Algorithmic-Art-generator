#include "stats.h"

stats::stats(PNG & im){

/* Your code here!! */
int wid = im.width();
int heig = im.height();

sumRed.clear();
sumRed.resize(wid, vector<long>(heig, 0));
sumGreen.clear();
sumGreen.resize(wid, vector<long>(heig, 0));
sumBlue.clear();
sumBlue.resize(wid, vector<long>(heig, 0));
sumsqRed.clear();
sumsqRed.resize(wid, vector<long>(heig, 0));
sumsqGreen.clear();
sumsqGreen.resize(wid, vector<long>(heig, 0));
sumsqBlue.clear();
sumsqBlue.resize(wid, vector<long>(heig, 0));

int y;
for (y = 0; y < heig; y++) {

    int x;
    for (x = 0; x < wid; x++) {
        RGBAPixel * thisPix = im.getPixel(x,y);
    // special case == > x /  y = 0
        if (x == 0 && y == 0) {
                (sumRed[x])[y] = (long) thisPix->r;
                (sumGreen[x])[y] = (long) thisPix->g;
                (sumBlue[x])[y] = (long) thisPix->b;

                (sumsqRed[x])[y] = (long) thisPix->r * thisPix->r;
                (sumsqGreen[x])[y] = (long) thisPix->g * thisPix->g;
                (sumsqBlue[x])[y] = (long) thisPix->b * thisPix->b;
        }

        if (x == 0 && y != 0) {
            (sumRed[x])[y] = (long)(sumRed[x][y-1] + thisPix->r);
            (sumGreen[x])[y] = (long) (sumGreen[x][y-1] + thisPix->g);
            (sumBlue[x])[y] = (long) (sumBlue[x][y-1] + thisPix->b);
            (sumsqRed[x])[y] = sumsqRed[x][y-1] + ((long) thisPix->r * (long) thisPix->r);
            (sumsqGreen[x])[y] = sumsqGreen[x][y-1] + ((long) thisPix->g * (long) thisPix->g);
            (sumsqBlue[x])[y] = sumsqBlue[x][y-1] + ((long) thisPix->b * (long)thisPix->b);
        }

        if (y == 0 && x != 0) {
            (sumRed[x])[y] = (sumRed[x-1])[y] + (int) thisPix->r;
            (sumGreen[x])[y] = (sumGreen[x-1])[y] + (int) thisPix->g;
            (sumBlue[x])[y] = (sumBlue[x-1])[y] + (int) thisPix->b;
            (sumsqRed[x])[y] = (sumsqRed[x-1])[y] + ((int) thisPix->r * (int) thisPix->r);
            (sumsqGreen[x])[y] = (sumsqGreen[x-1])[y] + ((int) thisPix->g * (int) thisPix->g);
            (sumsqBlue[x])[y] = (sumsqBlue[x-1])[y] + ((int) thisPix->b * (int)thisPix->b);
        }

        if (x != 0 && y != 0) {
            (sumRed[x])[y] = (sumRed[x-1])[y] + (sumRed[x])[y-1] - (sumRed[x-1])[y-1] + (int) thisPix->r;
            (sumGreen[x])[y] = (sumGreen[x-1])[y] + (sumGreen[x])[y-1] - (sumGreen[x-1])[y-1] + (int) thisPix->g;
            (sumBlue[x])[y] = (sumBlue[x-1])[y] + (sumBlue[x])[y-1] - (sumBlue[x-1])[y-1] + (int) thisPix->b;
            (sumsqRed[x])[y] = (sumsqRed[x-1])[y] + (sumsqRed[x])[y-1] - (sumsqRed[x-1])[y-1] + ((int) thisPix->r * (int) thisPix->r);
            (sumsqGreen[x])[y] = (sumsqGreen[x-1])[y] + (sumsqGreen[x])[y-1] - (sumsqGreen[x-1])[y-1] + ((int) thisPix->g * (int) thisPix->g);
            (sumsqBlue[x])[y] = (sumsqBlue[x-1])[y] + (sumsqBlue[x])[y-1] - (sumsqBlue[x-1])[y-1] + ((int) thisPix->b * (int) thisPix->b);

        }

    }
}
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
long returnR;
long returnG;
long returnB;

int startX = ul.first;
int startY = ul.second;
if (w == 0 && h == 0) {
    if (startX == 0 && startY == 0) {
        returnR = sumRed[startX][startY];
        returnG = sumGreen[startX][startY];
        returnB = sumBlue[startX][startY];
    }
    if (startX == 0 && startY != 0) {
        returnR = sumRed[startX][startY] - sumRed[startX][startY-1];
        returnG = sumGreen[startX][startY] - sumGreen[startX][startY-1];
        returnB = sumBlue[startX][startY] - sumBlue[startX][startY-1];
    }
    if (startX != 0 && startY == 0) {
        returnR = sumRed[startX][startY] - sumRed[startX-1][startY];
        returnG = sumGreen[startX][startY] - sumGreen[startX-1][startY];
        returnB = sumBlue[startX][startY] - sumBlue[startX-1][startY];
    }
    if (startX != 0 && startY != 0) {
        returnR = sumRed[startX][startY] - sumRed[startX-1][startY] - sumRed[startX][startY-1] + sumRed[startX - 1][startY-1];
        returnG = sumGreen[startX][startY] - sumGreen[startX-1][startY] - sumGreen[startX][startY-1] + sumGreen[startX - 1][startY-1];
        returnB = sumBlue[startX][startY] - sumBlue[startX-1][startY] - sumBlue[startX][startY-1] + sumBlue[startX - 1][startY-1];
    }
}

if (w > 0 && h == 0) {
    if (startY == 0) {
        if (startX == 0) {
        returnR = sumRed[startX + w - 1][startY];
        returnG = sumGreen[startX + w - 1][startY];
        returnB = sumBlue[startX + w - 1][startY];
        }
        if (startX != 0) {
        returnR = sumRed[startX + w - 1][startY] - sumRed[startX - 1][startY - 1];
        returnG = sumGreen[startX + w - 1][startY] - sumGreen[startX - 1][startY - 1];
        returnB = sumBlue[startX + w - 1][startY] - sumBlue[startX - 1][startY - 1];
        }
    }
    if (startY != 0) {
        if (startX == 0) {
        returnR = sumRed[startX + w - 1][startY] - sumRed[startX][startY - 1];
        returnG = sumGreen[startX + w - 1][startY] - sumGreen[startX][startY - 1];
        returnB = sumBlue[startX + w - 1][startY] - sumBlue[startX][startY - 1];
        }
        if (startX != 0) {
        returnR = sumRed[startX + w - 1][startY] - sumRed[startX - 1][startY] - sumRed[startX + w - 1 - 1][startY - 1] + sumRed[startX - 1][startY - 1];
        returnG = sumGreen[startX + w - 1][startY] - sumGreen[startX - 1][startY] - sumGreen[startX + w - 1 - 1][startY - 1] + sumGreen[startX - 1][startY - 1];
        returnB = sumBlue[startX + w - 1][startY] - sumBlue[startX - 1][startY] - sumBlue[startX + w - 1 - 1][startY - 1] + sumBlue[startX - 1][startY - 1];
        }
    }
}
if (w == 0 && h > 0) {
    if (startX == 0) {
        if (startY == 0) {
        returnR = sumRed[startX][startY + h - 1];
        returnG = sumGreen[startX][startY + h - 1];
        returnB = sumBlue[startX][startY + h - 1]; 
        }
        if (startY != 0) {
        returnR = sumRed[startX][startY + h - 1] - sumRed[startX][startY - 1];
        returnG = sumGreen[startX][startY + h - 1] - sumGreen[startX][startY - 1];
        returnB = sumBlue[startX][startY + h - 1] - sumBlue[startX][startY - 1];
        }
    }
    if (startX != 0) {
        if (startY == 0) {
        returnR = sumRed[startX][startY + h - 1] - sumRed[startX + h - 1][startY + h - 1];
        returnG = sumGreen[startX][startY + h - 1] - sumGreen[startX - 1][startY + h - 1];
        returnB = sumBlue[startX][startY + h - 1] - sumBlue[startX - 1][startY + h - 1];
        }
        if (startY != 0) {
        returnR = sumRed[startX][startY + h - 1] - sumRed[startX][startY - 1] - sumRed[startX + h - 1 - 1][startX + h - 1] + sumRed[startX - 1][startY - 1];
        returnG = sumGreen[startX][startY + h - 1] - sumGreen[startX][startY - 1] - sumGreen[startX + h - 1 - 1][startX + h - 1] + sumGreen[startX - 1][startY - 1];
        returnB = sumBlue[startX][startY + h - 1] - sumBlue[startX][startY - 1] - sumBlue[startX + h - 1 - 1][startX + h - 1] + sumBlue[startX - 1][startY - 1];
        }
    }
}
if (w > 0 && h > 0) {
    if (startX == 0 && startY == 0) {
        returnR = sumRed[startX + w - 1][startY + h - 1];
        returnG = sumGreen[startX + w - 1][startY + h - 1];
        returnB = sumBlue[startX + w - 1][startY + h - 1];
    }
    if (startX == 0 && startY != 0) {
        returnR = sumRed[startX + w - 1][startY + h - 1] - sumRed[startX + w - 1][startY - 1];
        returnG = sumGreen[startX + w - 1][startY + h - 1] - sumGreen[startX + w - 1][startY - 1];
        returnB = sumBlue[startX + w - 1][startY + h - 1] - sumBlue[startX + w - 1][startY - 1];
    }
    if (startX != 0 && startY == 0) {
        returnR = sumRed[startX + w - 1][startY + h - 1] - sumRed[startX - 1][startY + h - 1];
        returnG = sumGreen[startX + w - 1][startY + h - 1] - sumGreen[startX - 1][startY + h - 1];
        returnB = sumBlue[startX + w - 1][startY + h - 1] - sumBlue[startX - 1][startY + h - 1];
    }
    if (startX != 0 && startY != 0) {
        returnR = sumRed[startX + w - 1][startY + h - 1] - sumRed[startX + w - 1][startY - 1] - sumRed[startX - 1][startY + h - 1] + sumRed[startX - 1][startY - 1];
        returnG = sumGreen[startX + w - 1][startY + h - 1] - sumGreen[startX + w - 1][startY - 1] - sumGreen[startX - 1][startY + h - 1] + sumGreen[startX - 1][startY - 1];
        returnB = sumBlue[startX + w - 1][startY + h - 1] - sumBlue[startX + w - 1][startY - 1] - sumBlue[startX - 1][startY + h - 1] + sumBlue[startX - 1][startY - 1];
    }
}
if (channel == 'r' ) {
    return (returnR);
} if (channel == 'g') {
    return (returnG);
} else {
    return (returnB);
}
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
long returnR;
long returnG;
long returnB;

int startX = ul.first;
int startY = ul.second;
if (w == 0 && h == 0) {
    if (startX == 0 && startY == 0) {
        returnR = sumsqRed[startX][startY];
        returnG = sumsqGreen[startX][startY];
        returnB = sumsqBlue[startX][startY];
    }
    if (startX == 0 && startY != 0) {
        returnR = sumsqRed[startX][startY] - sumsqRed[startX][startY-1];
        returnG = sumsqGreen[startX][startY] - sumsqGreen[startX][startY-1];
        returnB = sumsqBlue[startX][startY] - sumsqBlue[startX][startY-1];
    }
    if (startX != 0 && startY == 0) {
        returnR = sumsqRed[startX][startY] - sumsqRed[startX-1][startY];
        returnG = sumsqGreen[startX][startY] - sumsqGreen[startX-1][startY];
        returnB = sumsqBlue[startX][startY] - sumsqBlue[startX-1][startY];
    }
    if (startX != 0 && startY != 0) {
        returnR = sumsqRed[startX][startY] - sumsqRed[startX-1][startY] - sumsqRed[startX][startY-1] + sumsqRed[startX - 1][startY-1];
        returnG = sumsqGreen[startX][startY] - sumsqGreen[startX-1][startY] - sumsqGreen[startX][startY-1] + sumsqGreen[startX - 1][startY-1];
        returnB = sumsqBlue[startX][startY] - sumsqBlue[startX-1][startY] - sumsqBlue[startX][startY-1] + sumsqBlue[startX - 1][startY-1];
    }
}
if (w > 0 && h == 0) {
    if (startY == 0) {
        if (startX == 0) {
        returnR = sumsqRed[startX + w - 1][startY];
        returnG = sumsqGreen[startX + w - 1][startY];
        returnB = sumsqBlue[startX + w - 1][startY];
        }
        if (startX != 0) {
        returnR = sumsqRed[startX + w - 1][startY] - sumsqRed[startX - 1][startY - 1];
        returnG = sumsqGreen[startX + w - 1][startY] - sumsqGreen[startX - 1][startY - 1];
        returnB = sumsqBlue[startX + w - 1][startY] - sumsqBlue[startX - 1][startY - 1];
        }
    }
    if (startY != 0) {
        if (startX == 0) {
        returnR = sumsqRed[startX + w - 1][startY] - sumsqRed[startX][startY - 1];
        returnG = sumsqGreen[startX + w - 1][startY] - sumsqGreen[startX][startY - 1];
        returnB = sumsqBlue[startX + w - 1][startY] - sumsqBlue[startX][startY - 1];
        }
        if (startX != 0) {
        returnR = sumsqRed[startX + w - 1][startY] - sumsqRed[startX - 1][startY] - sumsqRed[startX + w - 1 - 1][startY - 1] + sumsqRed[startX - 1][startY - 1];
        returnG = sumsqGreen[startX + w - 1][startY] - sumsqGreen[startX - 1][startY] - sumsqGreen[startX + w - 1 - 1][startY - 1] + sumsqGreen[startX - 1][startY - 1];
        returnB = sumsqBlue[startX + w - 1][startY] - sumsqBlue[startX - 1][startY] - sumsqBlue[startX + w - 1 - 1][startY - 1] + sumsqBlue[startX - 1][startY - 1];
        }
    }
}
if (w == 0 && h > 0) {
    if (startX == 0) {
        if (startY == 0) {
        returnR = sumsqRed[startX][startY + h - 1];
        returnG = sumsqGreen[startX][startY + h - 1];
        returnB = sumsqBlue[startX][startY + h - 1]; 
        }
        if (startY != 0) {
        returnR = sumsqRed[startX][startY + h - 1] - sumsqRed[startX][startY - 1];
        returnG = sumsqGreen[startX][startY + h - 1] - sumsqGreen[startX][startY - 1];
        returnB = sumsqBlue[startX][startY + h - 1] - sumsqBlue[startX][startY - 1];
        }
    }
    if (startX != 0) {
        if (startY == 0) {
        returnR = sumsqRed[startX][startY + h - 1] - sumsqRed[startX + h - 1][startY + h - 1];
        returnG = sumsqGreen[startX][startY + h - 1] - sumsqGreen[startX - 1][startY + h - 1];
        returnB = sumsqBlue[startX][startY + h - 1] - sumsqBlue[startX - 1][startY + h - 1];
        }
        if (startY != 0) {
        returnR = sumsqRed[startX][startY + h - 1] - sumsqRed[startX][startY - 1] - sumsqRed[startX + h - 1 - 1][startX + h - 1] + sumsqRed[startX - 1][startY - 1];
        returnG = sumsqGreen[startX][startY + h - 1] - sumsqGreen[startX][startY - 1] - sumsqGreen[startX + h - 1 - 1][startX + h - 1] + sumsqGreen[startX - 1][startY - 1];
        returnB = sumsqBlue[startX][startY + h - 1] - sumsqBlue[startX][startY - 1] - sumsqBlue[startX + h - 1 - 1][startX + h - 1] + sumsqBlue[startX - 1][startY - 1];
        }
    }
}
if (w > 0 && h > 0) {
    if (startX == 0 && startY == 0) {
        returnR = sumsqRed[startX + w - 1][startY + h - 1];
        returnG = sumsqGreen[startX + w - 1][startY + h - 1];
        returnB = sumsqBlue[startX + w - 1][startY + h - 1];
    }
    if (startX == 0 && startY != 0) {
        returnR = sumsqRed[startX + w - 1][startY + h - 1] - sumsqRed[startX + w - 1][startY - 1];
        returnG = sumsqGreen[startX + w - 1][startY + h - 1] - sumsqGreen[startX + w - 1][startY - 1];
        returnB = sumsqBlue[startX + w - 1][startY + h - 1] - sumsqBlue[startX + w - 1][startY - 1];
    }
    if (startX != 0 && startY == 0) {
        returnR = sumsqRed[startX + w - 1][startY + h - 1] - sumsqRed[startX - 1][startY + h - 1];
        returnG = sumsqGreen[startX + w - 1][startY + h - 1] - sumsqGreen[startX - 1][startY + h - 1];
        returnB = sumsqBlue[startX + w - 1][startY + h - 1] - sumsqBlue[startX - 1][startY + h - 1];
    }
    if (startX != 0 && startY != 0) {
        returnR = sumsqRed[startX + w - 1][startY + h - 1] - sumsqRed[startX + w - 1][startY - 1] - sumsqRed[startX - 1][startY + h - 1] + sumsqRed[startX - 1][startY - 1];
        returnG = sumsqGreen[startX + w - 1][startY + h - 1] - sumsqGreen[startX + w - 1][startY - 1] - sumsqGreen[startX - 1][startY + h - 1] + sumsqGreen[startX - 1][startY - 1];
        returnB = sumsqBlue[startX + w - 1][startY + h - 1] - sumsqBlue[startX + w - 1][startY - 1] - sumsqBlue[startX - 1][startY + h - 1] + sumsqBlue[startX - 1][startY - 1];
    }
}

if (channel == 'r' ) {
    return (returnR);
} if (channel == 'g') {
    return (returnG);
} else {
    return (returnB);
}

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */
int area = w * h;
if (area == 0) {
    return 0.0;
}
// var red
long sqRed = getSumSq('r', ul, w, h); 
long Red = getSum('r', ul, w, h);
double varR = sqRed - ((Red * Red) / abs(area));

long sqGreen = getSumSq('g', ul, w, h); 
long Green = getSum('g', ul, w, h);
double varG = sqGreen - ((Green * Green) / abs(area));

long sqBlue = getSumSq('b', ul, w, h); 
long Blue = getSum('b', ul, w, h);
double varB = sqBlue - ((Blue * Blue) / abs(area));

double totalV = varR + varG + varB;
return totalV;

}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */
// get sum red green blue, each divide by area
// create new pixel
int thisArea = w * h;
if (thisArea == 0) {
    return  RGBAPixel(0,0,0,1.0);
}

long avgR = getSum('r', ul, w, h);
long avgG = getSum('g', ul, w, h);
long avgB = getSum('b', ul, w, h);

if (thisArea != 0) {
    avgR = avgR / thisArea;
    avgG = avgG / thisArea;
    avgB = avgB / thisArea;
}
RGBAPixel avgColour = RGBAPixel((int) avgR, (int) avgG, (int) avgB);
return avgColour;

}