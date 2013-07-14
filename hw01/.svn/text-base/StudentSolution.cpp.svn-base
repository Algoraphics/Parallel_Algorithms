// -*- C++ -*-
/*
 * StudentSolution.cpp
 *
 * HW 01, cilk version from the original stocks.sml at CMU
 *
 * THIS is the only file we will look at when we grade your homework.
 * All other changes you made to any other files will be discarded.
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MIN(x, y) ((x < y) ? x : y)
#define MAX(x, y) ((x > y) ? x : y)

// YOUR naive, quadratic stock market algorithm
void solveStocksNaive(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{
    int maxJump = 0;
    int a = 9999999;
    int b = 0;
    //printf("naive: index is %d and length is %d\n",beginIndex, seqLength);
    for (int i = beginIndex; i < beginIndex + seqLength - 1; ++i) {
        int tempa = stockSequence[i];
        for (int j = i + 1; j < beginIndex + seqLength - 1; ++j) {
            int tempb = stockSequence[j];
            maxJump = MAX(maxJump, b - a);
            a = MIN(tempa,a);
            b = MAX(tempb,b);
        }   
    }
    result->jump = maxJump;
    result->bestBuy = a;
    result->bestSell = b;
}

vector<int> RecHelper(const vector<int> &stockSequence, int beginIndex, int seqLength)
{
    vector<int> vec;
    //printf("recursive: index is %d and length is %d\n",beginIndex, seqLength);
    if (seqLength < 2) {
	//printf("base case\n");
        int num = stockSequence[beginIndex];
	vec.push_back(0); //push back jump of 0 first
	vec.push_back(num);
	vec.push_back(num); //push back twice, once as min and once as max
    }
    else if (seqLength == 2) {
	//printf("second base case\n");
        int first = stockSequence[beginIndex];
        int second = stockSequence[beginIndex+1];
	int jump = second - first;
	vec.push_back(jump);
	vec.push_back(MIN(first,second));
	vec.push_back(MAX(first,second));
    }
    else {
	//printf("recursive case\n");
        vector<int> vecL = RecHelper(stockSequence, beginIndex, seqLength/2);
        //printf("beginIndex was at %d and seqLength at %d\n",beginIndex,seqLength/2);
	vector<int> vecR = RecHelper(stockSequence, beginIndex + seqLength/2, (seqLength + 1)/2);
        int jumpL = vecL[0];
        int jumpR = vecR[0];
        int minL = vecL[1];
		int maxR = vecR[2];
        int jumpC = maxR - minL; //get max jump across left and right cases
        //printf("maxR is %d and minL is %d resulting in jumpC = %d\n", maxR,minL,jumpC);
		int maxJump = MAX(jumpC, MAX(jumpL, jumpR));
	//printf("jumpC is %d, jumpL is %d, jumpR is %d, and maxJump is %d\n",jumpC, jumpL, jumpR, maxJump);
		int min = MIN(minL, vecR[1]);
		int max = MAX(vecL[2], maxR);
		vec.push_back(maxJump);
		vec.push_back(min);
		vec.push_back(max);
	/*if (maxJump == jumpL) {
		vec.push_back(jumpL);
		vec.push_back(minL);
		vec.push_back(vecL[2]);
        }
	else if (maxJump == jumpC) {
		vec.push_back(jumpC);
		vec.push_back(minL);
		vec.push_back(maxR);	
	}
	else {	
		vec.push_back(jumpR);
		vec.push_back(vecR[1]);
		vec.push_back(maxR);
	}*/	
    }
    return vec;
}

// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecurse(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{
    for (int i = 0; i < beginIndex + seqLength; ++i) {
	//printf("Sequence item at index %d is %d\n",i,stockSequence[i]);	
    }
    printf("recursive: index is %d and length is %d\n",beginIndex, seqLength);
    vector<int> jumpVec = RecHelper(stockSequence, beginIndex, seqLength);
    result->jump = jumpVec[0];
    result->bestBuy = jumpVec[1];
    result->bestSell = jumpVec[2];
}

vector<int> RecParHelper(const vector<int> &stockSequence, int beginIndex, int seqLength)
{
    vector<int> vec;
    //printf("recursive: index is %d and length is %d\n",beginIndex, seqLength);
    if (seqLength < 2) {
	//printf("base case\n");
        int num = stockSequence[beginIndex];
	vec.push_back(0); //push back jump of 0 first
	vec.push_back(num);
	vec.push_back(num); //push back twice, once as min and once as max
    }
    else if (seqLength == 2) {
	//printf("second base case\n");
        int first = stockSequence[beginIndex];
        int second = stockSequence[beginIndex+1];
	int jump = second - first;
	vec.push_back(jump);
	vec.push_back(MIN(first,second));
	vec.push_back(MAX(first,second));
    }
    else {
	//printf("recursive case\n");
        vector<int> vecL = cilk_spawn(RecParHelper(stockSequence, beginIndex, seqLength/2));
        //printf("beginIndex was at %d and seqLength at %d\n",beginIndex,seqLength/2);
	vector<int> vecR = RecParHelper(stockSequence, beginIndex + seqLength/2, (seqLength + 1)/2);
		cilk_sync;
        int jumpL = vecL[0];
        int jumpR = vecR[0];
        int minL = vecL[1];
		int maxR = vecR[2];
        int jumpC = maxR - minL; //get max jump across left and right cases
        //printf("maxR is %d and minL is %d resulting in jumpC = %d\n", maxR,minL,jumpC);
		int maxJump = MAX(jumpC, MAX(jumpL, jumpR));
	//printf("jumpC is %d, jumpL is %d, jumpR is %d, and maxJump is %d\n",jumpC, jumpL, jumpR, maxJump);
		int min = MIN(minL, vecR[1]);
		int max = MAX(vecL[2], maxR);
		vec.push_back(maxJump);
		vec.push_back(min);
		vec.push_back(max);
	/*if (maxJump == jumpL) {
		vec.push_back(jumpL);
		vec.push_back(minL);
		vec.push_back(vecL[2]);
        }
	else if (maxJump == jumpC) {
		vec.push_back(jumpC);
		vec.push_back(minL);
		vec.push_back(maxR);	
	}
	else {	
		vec.push_back(jumpR);
		vec.push_back(vecR[1]);
		vec.push_back(maxR);
	}*/	
    }
    return vec;
}

// YOUR recursive, divide and conqure stock market algorithm
void solveStocksRecPar(const vector<int> &stockSequence, int beginIndex, int seqLength, StocksResult *result)
{
    vector<int> jumpVec = RecParHelper(stockSequence, beginIndex, seqLength);
    result->jump = jumpVec[0];
    result->bestBuy = jumpVec[1];
    result->bestSell = jumpVec[2];
}
