//Programmer: Tyler Patton
//Instructor: Dr. Das
//Course: Analysis of Algorithms
//Assignment: Given a starting square construct a closed Knight's Tour on an NxN chess board
//Description: This program implements Warnsdorf's Rule as a heuristic to choose a next square,
//             then attempts to complete a tour, if it fails the program backtracks to find 
//             a correct sequence.

#include "Tour.h"


int main()
{
  Tour mytour(6);
  mytour.tour("d4");
  std::cout<<mytour<<std::endl;

  return 0;
}
