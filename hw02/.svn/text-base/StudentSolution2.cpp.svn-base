// -*- C++ -*-

/*
 * StudentSolution.cpp
 *
 * HW 02, two ways of solving ClosestPair 
 *
 * THIS is the only file we will look at when we grade your homework.
 * All other changes you made to any other files will be discarded.
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <cilk/reducer_min.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <cmath>

#define MIN(x, y) ((x < y) ? x : y)
#define MAX(x, y) ((x > y) ? x : y)

using namespace std;

/* 
 * This method implements the brute force method of finding closest points.
 * Use this to test the correctness of the recursive O(nlogn) method on small sets.
 * The points don't need to be sorted
 */
void solveClosestPairBrute(PointArray *points, PairResult *result) {
	for (int i = 0; i < points->size(); ++i) {
		for (int j = 0; j < points->size(); ++j) {
			if (i != j) {
				Point *point1 = points->getPoint(i);
				Point *point2 = points->getPoint(j);
				double dist = point1->distance(point2);
				//printf("found distance %d from points ",dist);
				//point1->print(); printf(" and "); point2->print();
				if (dist < result->distance) {
					result->distance = dist;
					result->pointOne = point1;
					result->pointTwo = point2;
				}
			}	
		}
	}
}

/* 
 * This is the recursive method that you will complete to solve
 * the closest pair problem. It should:
 *   (1) divide -- split the input sequence in approximately half 
 *   (2) recurse -- recursively solve the two halves of the problem
 *   (3) combine -- find the solution to your input
 * The two arrays xPoints and yPoints are already sorted by x and y respectively.
 * The range of each array is (begin, end] (inclusive of begin, exclusive of end]
 */
PairResult closestPairRecHelp(PointArray *pointsx, PointArray *pointsy, int begin, int end) {
	//printf("made it to recursive call with index %d and %d\n",begin,end);
	PairResult pair = PairResult();
	if (end - begin == 1) {
		Point *p1 = pointsx->getPoint(begin);
		Point *p2 = pointsx->getPoint(end);
		pair.distance = p1->distance(p2);
		pair.pointOne = p1;
		pair.pointTwo = p2;
	}
	else if (end - begin > 1) {
		int mid = (begin + end)/2;
		Point * midPoint = pointsx->getPoint(mid);
		PointArray * yLeft = new PointArray(mid - begin + 1);
		PointArray * yRight = new PointArray(end - mid);
		for (int i = 0; i < pointsy->size(); ++i) {
			Point * p = pointsy->getPoint(i);
			int compare = Point::compareX(&p, &midPoint);
			if (compare <= 0) {
				yLeft->append(p);
			}
			else {
				yRight->append(p);
			}
		}
		PairResult left = closestPairRecHelp(pointsx, yLeft, begin, mid);
		PairResult right = closestPairRecHelp(pointsx, yRight, mid + 1, end);
		double minDist;
		if (left.distance < right.distance) {
			pair = left;
			minDist = left.distance;	
		}
		else {
			pair = right;
			minDist = right.distance;
		}
		vector<Point*> yStrip;
        for (int i = 0; i < pointsy->size(); ++i) {
			Point * p = pointsy->getPoint(i);
			if (abs(p->getX() - midPoint->getX()) < minDist) {
				yStrip.push_back(p);
			}
		}
		for (int j = 0; j < yStrip.size() - 1; ++j) {
			int k = j + 1;
			Point *p1 = yStrip[j];
			Point *p2 = yStrip[k];
			double curDist = p1->distance(p2);
			if (curDist < pair.distance) {
				pair.distance = curDist;
				pair.pointOne = p1;
				pair.pointTwo = p2;
			}
		}
	}
        else {
		//printf("returned default pair\n");
	}
	return pair;
}

void solveClosestPairRecurse(PointArray *xPoints, int beginX, int endX, PointArray *yPoints, int beginY, int endY, PairResult *result) {
	PairResult temp = closestPairRecHelp(xPoints,yPoints, beginX, endX-1);
	result->distance = temp.distance;
	result->pointOne = temp.pointOne;
	result->pointTwo = temp.pointTwo;
}

/* 
 * This is the parallel version of our recrusive method.
 */
 
 //implements scan-style prefixSum
vector<int> prefixSum (vector<int> inArr) {
	int size = inArr.size();
	if (size == 2) {
		return inArr;
	}
	else if (size == 3) {
		inArr[2] = inArr[1] + inArr[2];
		return inArr;
	}
	else {
		vector<int> smaller(size/2 + 1);
		smaller[0] = 0;
		cilk_for (int i = 1; i < size; i+=2) {
			int j = (i + 1)/2;
			if (i == size - 1) {
				smaller[j] = inArr[i];
			}
			else {
				smaller[j] = inArr[i] + inArr[i + 1];
			}
		}
		vector<int> smallSum = prefixSum(smaller);
		cilk_for (int k = 0; k < size; ++k) {
			if (k%2 == 0) {
				inArr[k] = smallSum[k/2];
			}
			else {
				inArr[k] = inArr[k] + smallSum[(k-1)/2];
			}
		}
		return inArr;
	}
}
 
 //makes the strip for the divide and conquer part
PointArray * makeStrip(PointArray * inArr, double midX, double minDist) {
	vector<int> prefix(inArr->size() + 1); prefix[0] = 0;
	cilk_for (int i = 0; i < inArr->size(); ++i) {
		Point * p = inArr->getPoint(i);
		if (std::abs(p->getX() - midX) < minDist) {
			prefix[i + 1] = 1;
		}
		else {
			prefix[i + 1] = 0;
		}
	}
	vector<int> pSum = prefixSum(prefix);
	PointArray * yStrip = new PointArray(pSum[pSum.size() - 1]);
	cilk_for (int j = 0; j < pSum.size() - 1; ++j) {
		if (j == 0 && pSum[j+1] == 1) {
			yStrip->insert(pSum[j+1] - 1,inArr->getPoint(j));
		}
		else if (j > 0 && pSum[j+1] != pSum[j]) {
			yStrip->insert(pSum[j+1] - 1,inArr->getPoint(j));
		}
	}
	return yStrip;
}

//Can be used to make either the left or right y-sorted arrays
PointArray * makeLorR(PointArray * inArr, Point * midPoint, int isL) {
	vector<int> prefix(inArr->size() + 1); prefix[0] = 0;
	cilk_for (int i = 0; i < inArr->size(); ++i) {
		Point * p = inArr->getPoint(i);
		int compare = Point::compareX(&p, &midPoint);
		if (compare <= 0) {
			prefix[i+1] = isL;
		}
		else {
			prefix[i+1] = 1 - isL;
		}
	}
	vector<int> preSum = prefixSum(prefix);
	PointArray * pArr = new PointArray(preSum[preSum.size() - 1]);
	cilk_for (int j = 0; j < preSum.size() - 1; ++j) {
		if (j == 0 && preSum[j+1] == 1) {
			pArr->insert(preSum[j+1] - 1,inArr->getPoint(j));
		}
		else if (j > 0 && preSum[j+1] != preSum[j]) {
			pArr->insert(preSum[j+1] - 1,inArr->getPoint(j));
		}
	}
	return pArr;
}

//a parallel divide-and-conquer min finder to get the minimum distance across an array of pairs
PairResult getMinPair(vector<PairResult> inVec,int begin,int end) {
	int size = end - begin;
	if (size == 0) {
		return inVec[begin];
	}
	if (size == 1) {
		if (inVec[begin].distance < inVec[end].distance) {
			return inVec[begin];
		}
		else return inVec[end];
	}
	else {
		PairResult left = cilk_spawn(getMinPair(inVec,begin,begin + size/2));
		PairResult right = getMinPair(inVec,begin + size/2 + 1,end);
		cilk_sync;
		if (left.distance < right.distance) {
			return left;
		}
		else return right;
	}
}
 
PairResult closestPairRecParHelp(PointArray *pointsx, PointArray *pointsy, int begin, int end) {
	PairResult pair = PairResult();
	if (end - begin == 1) {
		Point *p1 = pointsx->getPoint(begin);
		Point *p2 = pointsx->getPoint(end);
		pair.distance = p1->distance(p2);
		pair.pointOne = p1;
		pair.pointTwo = p2;
	}
	else if (end - begin > 1) {
		int mid = (begin + end)/2;
		Point * midPoint = pointsx->getPoint(mid);
		PointArray * yLeft = makeLorR(pointsy,midPoint,1);
		PointArray * yRight = makeLorR(pointsy,midPoint,0);
		PairResult left = cilk_spawn(closestPairRecParHelp(pointsx, yLeft, begin, mid));
		PairResult right = closestPairRecParHelp(pointsx, yRight, mid + 1, end);
		cilk_sync;
		double minDist;
		if (left.distance < right.distance) {
			pair = left;
			minDist = left.distance;	
		}
		else {
			pair = right;
			minDist = right.distance;
		}
		PointArray * yStrip = makeStrip(pointsy,midPoint->getX(),minDist);
		vector<PairResult> pairVec(yStrip->size());
		cilk_for (int j = 0; j < yStrip->size() - 1; ++j) {
			pairVec[j] = PairResult();
			int k = j + 1;
			Point *p1 = yStrip->getPoint(j);
			Point *p2 = yStrip->getPoint(k);
			double curDist = p1->distance(p2);
			if (curDist < pair.distance) {
				pairVec[j].distance = curDist;
				pairVec[j].pointOne = p1;
				pairVec[j].pointTwo = p2;
			}
		}
		pairVec[yStrip->size() - 1] = pair;
		pair = getMinPair(pairVec,0,pairVec.size() - 1);
	}
	return pair;
}

void solveClosestPairParallel(PointArray *xPoints, int beginX, int endX, PointArray *yPoints, int beginY, int endY, PairResult *result) {
	PairResult temp = closestPairRecParHelp(xPoints,yPoints, beginX, endX-1);
	result->distance = temp.distance;
	result->pointOne = temp.pointOne;
	result->pointTwo = temp.pointTwo;

}

