//Programmer: Tyler Patton
//Instructor: Dr. Das
//Course: Analysis of Algorithms
//Assignment: Given a starting square construct a closed Knight's Tour on an NxN chess board
//Description: This is the driver for Tour.h. Create a Tour with size N = 2k to solve for a closed Knight's
//             Tour on an NxN chess board.
//Implementation: INCOMPLETE: Warnsdorf's Rule is used to choose the next move with the least next moves.
//                After Warsndorf's the moves are then chosen based on the order in the Tracking array.
//                Backtracking allows for failed paths to be reevaluated
//                INCOMPLETE: Checks for a structured Knight's Tour
//                INCOMPLETE: Uses Divide and Conquer for large N

#include "Tour.h"

int main()
{
  Tour mytour(6);
  mytour.tour("d4");
  std::cout<<mytour<<std::endl;

  return 0;
}
