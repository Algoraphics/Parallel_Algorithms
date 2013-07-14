// -*- C++ -*-

/*
 * QuicksortSupport.cpp
 *
 * Protecting 341 students from the ugliness that is files, random
 * number generation, list creation, and print methods.
 *
 */

#include <cstdlib>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

int maxValue = 500;

void checkLen(int len) {
  if (len < 2) {
    cout << "Sequence Length must be > 1";
    exit(0);
  }
}

vector<int> getSequenceFromFile(int* seqLength, char* filename) {

  vector<int> sequence;
  int file_len;
  string line;

  ifstream myfile (filename);
  if (myfile.is_open()) {
      int i = 0;
      bool first = true;
      while (myfile.good() && getline(myfile, line)) {
        int num = atoi(line.c_str());
        if (first) {
          *seqLength = num;
          checkLen(*seqLength);
          sequence.resize(num); // now we know how big it should be
          first = false;
          std::cout << "File's sequence has length: "
            << num << "." << std::endl << std::endl;
        } else {
          sequence[i] = num;
          i++;
	  if (i >= *seqLength)
	    break;
        }
      }
    myfile.close();
  }
  else {
    cout << "Unable to open file " << filename << std::endl; 
    exit(0);
  }

  return sequence;
}

// This code already works and you shouldn't have to understand or
// modify it, so we've stashed it here.
vector<int> randomlyGenerateSeq(int seqLength) {
  
  checkLen(seqLength);

  std::cout << "Randomly generating sequence of length: "
	    << seqLength << "." << std::endl <<
	    "Highest possible value = "
	    << maxValue << "." << std::endl << std::endl;

  vector<int> sequence(seqLength);
  for(int i = 0; i < seqLength; i++) {
    // Populate sequence 
    // Note: might want to change rand seed at some point... or not!
    sequence[i] = rand() % (maxValue + 1);
  }
  return sequence;
}

void printSequence(int seq_len, vector<int> seq) {

  std::cout << "Sequence =  " << std::endl << "   [";

  for (int i = 0; i < seq_len; i++) {
    std::cout << seq[i] << ", ";
    if (((i+1)%20) == 0)
      std::cout << std::endl << "    ";
  }
  std::cout << "]" << std::endl;
}

