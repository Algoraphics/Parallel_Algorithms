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

#define MIN(x, y) ((x < y) ? x : y)
#define MAX(x, y) ((x > y) ? x : y)

using namespace std;

/* 
 * This method implements the brute force method of finding closest points.
 * Use this to test the correctness of the recursive O(nlogn) method on small sets.
 */
void solveClosestPairBrute(PointArray *points, PairResult *result) {
	for (int i = 0; i < points->size(); ++i) {
		for (int j = 0; j < points->size(); ++j) {
			if (i != j) {
				Point *point1 = points->getPoint(i);
				Point *point2 = points->getPoint(j);
				int dist = point1->distance(point2);
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
 *   (1) divide that splits the input sequence in approximately half 
 *   (2) recurse that recursively solves the two halves of the problem
 *   (3) combine that finds the solution to your input
 * The range of the array goes from (begin, end] (inclusive of begin, exclusive of end)
 */
PairResult *closestPairRecHelp(PointArray *pointsx, PointArray *pointsy, int begin, int end) {
	printf("made it to recursive call with index %d and %d for array of size %d\n",begin,end, pointsx->size());
	PairResult *pair = new PairResult();
	if (end - begin == 1) {
		Point *p1 = pointsx->getPoint(begin);
		Point *p2 = pointsx->getPoint(end);
		pair->distance = p1->distance(p2);
		pair->pointOne = p1;
		pair->pointTwo = p2;
		printf("returned pair\n");
	}
	else if (end - begin > 1) {
		int mid = (begin + end)/2;
		printf("left would be %d to %d and right would be %d to %d for mid %d\n",begin, begin + mid, begin + mid + 1, end,mid);
		PairResult *left = closestPairRecHelp(pointsx, pointsy, begin, mid);
		PairResult *right = closestPairRecHelp(pointsx, pointsy, mid + 1, end);
		int minDist = MIN(right->distance,left->distance);
		if (left->distance < right->distance) {
			pair = left;
		}
		else {
			pair = right;
		}
                for (int j = 0; j < pointsy->size() - 1; ++j) {
			int k = j + 1;
			Point *p1 = pointsy->getPoint(j);
			Point *p2 = pointsx->getPoint(k);
			int curDist = p1->distance(p2);
			if (curDist < pair->distance) {
				pair->distance = curDist;
				pair->pointOne = p1;
				pair->pointTwo = p2;
			}
		}
	}
        else {
		printf("returned default pair\n");
	}
	return pair;
}

void solveClosestPairRecurse(PointArray *points, int begin, int end, PairResult *result) {
	points->getPoint(end-1)->print();
	PointArray *pointsx = points->copy();
	PointArray *pointsy = points->copy();
	result = closestPairRecHelp(pointsx,pointsy, begin, end);
}
/* 
 * This is the parallel version of our recrusive method.
 */


void solveClosestPairParallel(PointArray *points, int begin, int end, PairResult *result) {

}

