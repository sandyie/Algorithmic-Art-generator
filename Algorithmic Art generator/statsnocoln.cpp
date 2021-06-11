#include "stats.h"


#include "stats.h"

stats::stats(PNG & im){

/* Your code here!! */
int wid = im.width();
int heig = im.height();

int x;
for (x = 0; x < wid; x++) {
    int redcoln = 0;
    int greencoln = 0;
    int bluecoln = 0;

    int redseqcoln = 0;
    int greenseqcoln = 0;
    int blueseqcoln = 0;

    int y;
    for (y = 0; y < heig; y++) {
    // special case == > x /  y = 0
        if (x == 0) {
            if (x == 0 && y == 0) {
                RGBAPixel * thisPix = im.getPixel(x,y);
                sumRed[x].push_back(thisPix->r);
                sumGreen[x].push_back(thisPix -> g);
                sumBlue[x].push_back(thisPix -> b);

                sumsqRed[x].push_back(thisPix->r*thisPix->r);
                sumsqGreen[x].push_back(thisPix->g*thisPix->g);
                sumsqBlue[x].push_back(thisPix->b*thisPix->b);
            }
            RGBAPixel * thisPix = im.getPixel(0,y);
            int SRed = redcoln;
            SRed = SRed + thisPix->r;
            sumRed[x].push_back(SRed);

            int SGreen = greencoln;
            SGreen = SGreen + thisPix->g;
            sumGreen[x].push_back(SGreen);

            int SBlue = blueseqcoln;
            SBlue = SBlue + thisPix->b;
            sumBlue[x].push_back(SBlue);

            int SqRed = redseqcoln;
            SqRed = SqRed + thisPix->r*thisPix->r;
            sumsqRed[x].push_back( SqRed );

            int SqGreen = greenseqcoln;
            SqGreen = SqGreen + thisPix->g*thisPix->g;
            sumsqGreen[x].push_back( SqGreen );

            int SqBlue = blueseqcoln; 
            SqBlue = SqBlue + thisPix->b*thisPix->b;
            sumsqBlue[x].push_back( SqBlue );
        }

        if (y == 0) {
            RGBAPixel * thisPix = im.getPixel(x,0);
            sumRed[x].push_back(thisPix -> r + (sumRed[x-1])[y] );
            sumGreen[x].push_back(thisPix -> g + (sumGreen[x-1])[y] );
            sumBlue[x].push_back(thisPix -> b + (sumBlue[x-1])[y] );
            sumsqRed[x].push_back(thisPix -> r*thisPix -> r  + (sumsqRed[x-1])[y] );
            sumsqGreen[x].push_back(thisPix -> g*thisPix -> g + (sumsqGreen[x-1])[y] );
            sumsqBlue[x].push_back(thisPix -> b*thisPix -> b + (sumsqBlue[x-1])[y] );
        }

    // used index (3 times )
    //    for (int x1 = 0; x1 <= x; x ++) {
    //        for (int y1 = 0; y1 <= y; y ++) {
    //            // get sum of all point to this current 
    //            //   vector< vector< long >> sumRed; index to get sum at 
    //        }
    //    }

       // redone: (x-1, y-1)
       // sum red; sum green; sum blue
       // sum red; sum green; sum blue -- >square
       // put into vector
       else{
            int prevRed = redcoln + (sumRed[x - 1])[y] - (sumRed[x - 1])[y - 1] ;
            int prevGreen = greencoln + (sumGreen[x - 1])[y] - (sumGreen[x - 1])[y - 1];
            int prevBlue = bluecoln + (sumBlue[x - 1])[y] - (sumBlue[x - 1])[y - 1];
            int sqrRed = (redseqcoln) +  (sumsqRed[x - 1])[y] - (sumsqRed[x - 1])[y - 1];
            int sqrGreen = (greenseqcoln) + (sumsqGreen[x - 1])[y] - (sumsqGreen[x - 1])[y - 1];
            int sqrBlue = (blueseqcoln) +   (sumsqBlue[x - 1])[y] - (sumsqBlue[x - 1])[y - 1];

    // int redoRed = (sumRed[x - 1])[y - 1];
    // int redoGreen = (sumGreen[x - 1])[y - 1];
    // int redoBlue = (sumBlue[x - 1])[y - 1];
    // int redoSqRed = (sumsqRed[x - 1])[y - 1];
    // int redoSqGreen = (sumsqGreen[x - 1])[y - 1];
    // int redoSqBlue = (sumsqBlue[x - 1])[y - 1];

            RGBAPixel * thisPix = im.getPixel(x,y);
            prevRed = prevRed + thisPix->r;
            prevGreen = prevGreen + thisPix->g;
            prevBlue = prevBlue + thisPix->b;
            sqrRed = sqrRed + thisPix->r*thisPix->r;
            sqrGreen = sqrGreen + thisPix->g*thisPix->g;
            sqrBlue = sqrBlue + thisPix->b*thisPix->b;

            sumRed[x].push_back( prevRed );
            sumGreen[x].push_back( prevGreen );
            sumBlue[x].push_back( prevBlue );
            sumsqRed[x].push_back( sqrRed );
            sumsqGreen[x].push_back( sqrGreen );
            sumsqBlue[x].push_back( sqrBlue );
       }
    }

    // sumRed.push_back(redcoln);
    // sumGreen.push_back(greencoln);
    // sumBlue.push_back(bluecoln);
    // sumsqRed.push_back(redseqcoln);
    // sumsqGreen.push_back(greenseqcoln);
    // sumsqBlue.push_back(blueseqcoln);
}
}


long stats::getSum(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    int x = ul.first + w ;
    int y = ul.second + h ;
if (channel == 'r' ) {
    return (sumRed[x][y]);
} if (channel == 'g') {
    return (sumGreen[x][y]);
} else {
    return (sumBlue[x][y]);
}
}

long stats::getSumSq(char channel, pair<int,int> ul, int w, int h){
/* Your code here!! */
    int x = ul.first + w ;
    int y = ul.second + h ;
if (channel == 'r' ) {
    return (sumsqRed[x][y]);
} if (channel == 'g') {
    return (sumsqGreen[x][y]);
} else {
    return (sumsqBlue[x][y]);
}
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int,int> ul, int w, int h){
/* Your code here!! */


}
		
RGBAPixel stats::getAvg(pair<int,int> ul, int w, int h){
/* Your code here!! */
int x = ul.first + w ;
int y = ul.second = h ;
// get sum red green blue, each divide by area
// create new pixel
int thisArea = w * h;
int avgR = sumRed[x][y];
int avgG = sumGreen[x][y];
int avgB = sumBlue[x][y];
avgR = avgR / thisArea;
avgG = avgG / thisArea;
avgB = avgB / thisArea;
RGBAPixel avgColour = RGBAPixel(avgR, avgG, avgB);
return avgColour;
}