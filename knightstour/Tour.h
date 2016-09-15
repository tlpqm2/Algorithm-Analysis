//Programmer: Tyler Patton
//Instructor: Dr. Das
//Course: Analysis of Algorithms
//Assignment: Given a starting square construct a closed Knight's Tour on an NxN chess Tour
//Description: Header and implementation details for Tour.h, containing structures and functions
//             necessary to solve a closed Knight's Tour.
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

#ifndef TOUR_H
#define TOUR_H

class Tour
{
  private:
    int m_size;
    int** m_data;
    //Tracker should be implemented as a tree in the future
    int** m_tracker;
    int m_moves[8][2];

  public:
    Tour(const int size);
    ~Tour();
    void tour(const std::string start);
    friend std::ostream& operator<<(std::ostream& os, const Tour& rhs);

};

Tour::Tour(const int size)
{
  //Initialize size
  m_size = size;
  if(m_size < 6)
  {
    throw std::domain_error("There are no Knight's Tours for N < 6");
  }
  else if(m_size % 2 == 1)
  {
    throw std::domain_error("N must be even");
  }

  //Initialize data
  m_data = new int*[m_size];
  for(int i = 0; i < m_size; i++)
  {
    m_data[i] = new int[m_size];
  }
  for(int i = 0; i < m_size; i++)
  {
    for(int j = 0; j < m_size; j++)
    {
      m_data[i][j] = -1;
    }
  }

  //Initialize tracker
  m_tracker = new int*[m_size*m_size];
  for(int i = 0; i < m_size*m_size; i++)
  {
    m_tracker[i] = new int[11];
  }
  for(int i = 0; i < m_size*m_size; i++)
  {
    for(int j = 0; j < 11; j++)
    {
      m_tracker[i][j] = -1;
    }
  }

  //Initialize moves
  m_moves[0][0] = 2;
  m_moves[0][1] = 1;

  m_moves[1][0] = 1;
  m_moves[1][1] = 2;

  m_moves[2][0] = 2;
  m_moves[2][1] = -1;

  m_moves[3][0] = 1; 
  m_moves[3][1] = -2;

  m_moves[4][0] = -2;
  m_moves[4][1] = 1;

  m_moves[5][0] = -1;
  m_moves[5][1] = 2;

  m_moves[6][0] = -2;
  m_moves[6][1] = -1;

  m_moves[7][0] = -1;
  m_moves[7][1] = -2;


}

Tour::~Tour()
{
  //Memory management: delete data and tracker
  for(int i = 0; i < m_size; i++)
  {
    delete [] m_data[i];
  }
  for(int i = 0; i < m_size*m_size; i++)
  {
    delete [] m_tracker[i];
  }
  delete [] m_data;
  delete [] m_tracker;
}

void Tour::tour(const std::string start)
{
  int move = 0, search = 0, x, y, dx, dy;
  //Ascii trick to map input rank/file to x/y coords
  //Need error checking that start is on board
  x = start[0] - 'a';
  y = start[1] - '0';
  y = m_size - y;

  //Set first move on board and track the position
  m_data[y][x] = move + 1;
  m_tracker[move][9] = x;
  m_tracker[move][10] = y;

  //This is where the magic happens
  while(move < (m_size*m_size - 1))
  {
    //Tracker[8] signies whether a move has all possible moves recorded
    //Tracker[9] holds the x coord for a given move
    //Tracker[10] holds the y coord for a given move
    //Update tracker
    if(m_tracker[move][8] == -1)
    {
      m_tracker[move][8] = 0;

      //Check moves
      for(int i = 0; i < 8; i++)
      {
        for(int j = 0; j < 2; j++)
        {
          if(j == 0)
          {
            dx = m_moves[i][j];
          }
          else
          {
            dy = m_moves[i][j];
          }
        }
        if(x + dx < 0 || y + dy < 0 || x + dx >= m_size || y + dy >= m_size || m_data[y + dy][x + dx] != -1)
        {
          m_tracker[move][i] = -1;
          //Illegal move, set as -1
        }
        else
        {
          //Apply Hornsdorf's Heuristic
          m_tracker[move][i] = 1;
        }
      }
    }
    search = 0;
    //Try to find a tracked move
    while(search < 8)
    {
      if(m_tracker[move][search] > 0)
      {
        x += m_moves[search][0];
        y += m_moves[search][1];
        m_tracker[move + 1][9] = x;
        m_tracker[move + 1][10] = y;
        m_tracker[move][search] = -1;
        break;
      }
      search++;
    }
    //Backtrack
    if(search == 8)
    {
      //Backtracking if we exhausted the tracker for the given move
      m_data[y][x] = -1;
      x = m_tracker[move - 1][9];
      y = m_tracker[move - 1][10];
      m_tracker[move][8] = -1;
      m_tracker[move][9] = -1;
      m_tracker[move][10] = -1;
      search = 0;

      //Clear the move taken at the previous move
      while(search < 8)
      {
        if(m_tracker[move - 1][search] > 0)
        {
          m_tracker[move - 1][search] = -1;
          break;
        }
        search++;
      }
      move--;
    } 
    //Move
    else
    {
      //Move the knight!
      m_data[y][x] = move + 2;
      move++;
    }
  }
  return;
}

std::ostream& operator<<(std::ostream& os, const Tour& rhs)
{
  for(int i = 0; i < rhs.m_size; i++)
  {
    for(int j = 0; j < rhs.m_size; j++)
    {
      std::cout<<std::setw(5)<<rhs.m_data[i][j]<<" ";
    }
    std::cout<<std::endl;
  }
  
  return os;
}

#endif