/*
Author: Andrew
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 3 Part A

This part improves on bot.cpp to make the player's lumber collection more efficient
*/
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

/* onAction: 
A procedure called each time an idle dwarf is choosing 
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

bool isNextToATree(Dwarf & dwarf, int r, int c){
  if(dwarf.look(r, c+1) == APPLE_TREE || dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE || dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE || dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE || dwarf.look(r-1, c) == PINE_TREE)
    return true;
  return false;
}

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  // Look if there is a tree on the right from the dwarf
  if (isNextToATree(dwarf, r, c) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }
  else {
    // Otherwise, move to a random location
    int rr = rand() % ROWS;
    int cc = rand() % COLS;
    log << "Walk to " << rr << " " << cc << endl;
    dwarf.start_walk(rr, cc);
    return;
  }
}
