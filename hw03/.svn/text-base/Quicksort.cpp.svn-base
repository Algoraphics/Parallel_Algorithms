// -*- C++ -*-

/*
 * Quicksort.cpp
 *
 * HW 03
 *
 */

#include <cstdlib>
#include <cilk/cilk.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include "QuicksortSupport.cpp"
#include "StudentSolution.cpp"
#include "Timer.cpp"
using namespace std;

// DO NOT MODIFY THIS FILE !!!!
// (the Auto-Grader will use the original version of this file,
// so any modifications you make here will be discarded before
// your assignment is graded)

int defaultSeqLen  = 10;
bool printResult_f = true;
bool printSequence_f = false;

int quicksortMain(int seqLength, char* myFile)
{
    vector<int> sequence;
    
    std::cout << "-----------------------------------------\n"
      "SORTING PROBLEM: Given a sequence of integers,\n"
      "sort the values in ascending order.\n"
      "-----------------------------------------\n";

    // Initialize sequence array
    if (myFile == NULL) {
      // Create random sequence
      sequence = randomlyGenerateSeq(seqLength);
    } else { 
      // get the sequence from the input file
      sequence = getSequenceFromFile(&seqLength, myFile);
    }
    // don't print a really long sequence. that's madness
    printSequence_f = printSequence_f;
    if (printSequence_f)
      printSequence(seqLength, sequence);

    vector<int> secondSequence(sequence.size());
    copy(sequence.begin(), sequence.end(), secondSequence.begin());

    // Compare various quicksort algorithms on this sequence.
    Timer *sequentialTimer = new Timer(new string("Sequential Quicksort"));
    Timer *parallelTimer = new Timer(new string("Parallel Quicksort"));

    // Run the sequential quicksort and time it!
    sequentialTimer->printBegin();
    sequentialTimer->begin();
    quicksortSequential(sequence, 0, seqLength-1);
    sequentialTimer->end();
	
    if (printResult_f)
      printSequence(seqLength, sequence);
      
    sequentialTimer->print(); 


    // Run the parallel quicksort and time it!
    parallelTimer->printBegin();
    parallelTimer->begin();
    vector<int> final(secondSequence.size());
    quicksortParallel(secondSequence, 0, secondSequence.size() - 1, final);
    parallelTimer->end();
      
    if (printResult_f)
	    printSequence(seqLength, secondSequence);
      
    parallelTimer->print();
    
    return 0;
}

int main(int argc, char* argv[])
{
    int seqLength = defaultSeqLen;
    char *myFile = NULL;
    if (argc > 1) {
      // they might just be asking for usage information
      if (std::string(argv[1]) == "-help") {
	std::cout << "--------- Quicksort -help -------------------" << std::endl;
	std::cout << "Usage: ./Quicksort -f filename -pRes 0" << std::endl 
		  << "        --OR--" << std::endl 
		  << "       ./Quicksort -len 30 -max 100 -pRes 0" << std::endl 
		  << "       where: " << std::endl 
		  << " -f filename specifies that the file called filename has the sequence" << std::endl
		  << "             First line of the file contains the sequence length" << std::endl
		  << "             Each line after that gives the value" << std::endl
		  << " -pRes 1|0   whether you want the result to be printed (Default = 1)" << std::endl
		  << " -pSeq 1|0   whether you want the sequence to be printed (Default = 0)" << std::endl
		  << " The following arguments apply ONLY to randomly generated sequences:" << std::endl
		  << "             (which will occur if no input file is specified)" << std::endl
		  << " -len x      limits sequence length to x (Default = " << defaultSeqLen << ")" << std::endl
		  << " -max x      limits maximum value to x (Default = " << maxValue << ")" << std::endl;
	exit(0);
      }

      // or they might actually want to run the code!
      for (int i = 1; i < argc; i=i+2) {
	if (std::string(argv[i]) == "-f") {
	  // We know the next argument *should* be the filename:
	  myFile = argv[i + 1];
	} else if (std::string(argv[i]) == "-len") {
	  // We know the next argument *should* be sequence length:
	  seqLength = atoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "-max") {
	  // We know the next argument *should* be max value:
	  maxValue = atoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "-pRes") {
	  // We know the next argument *should* be 1 or 0
	  printResult_f = (atoi(argv[i + 1]) == 0) ? false : true;
        } else if (std::string(argv[i]) == "-pSeq") {
	  // We know the next argument *should* be 1 or 0
	  printSequence_f = (atoi(argv[i + 1]) == 0) ? false : true;
        } 
      }
    }
    std::cout << "Note: for a complete explanation of command line arguments, type: ./Quicksort -help" << std::endl;
 
    return quicksortMain(seqLength, myFile);
}
