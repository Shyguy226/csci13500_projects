/*
Author: Andrew Giannico
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 3 Part C

This program is now at a point where the dwarves will build fences that are connected for at least 30 spaces, as well as cutting down trees in any direction along the way.
*/
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;
bool buildTime = false;
bool buildTime2 = false;
bool flag = true;
bool flag2=true;
bool flag3 = true;

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

bool isNextToATree(Dwarf &dwarf, int r, int c){
  if(dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE || dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE ||dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE ||dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE)
    return true;
  return false;
}

bool isNextToAPumpkin(Dwarf &dwarf, int r, int c){
  if(dwarf.look(r, c+1) == PUMPKIN || dwarf.look(r, c-1) == PUMPKIN || dwarf.look(r+1, c) == PUMPKIN || dwarf.look(r-1, c) == PUMPKIN)
    return true;
  return false;
}

void appleTree(Dwarf &dwarf, int r, int c){
  if(dwarf.look(r+1, c) == APPLE_TREE)
    dwarf.start_pick(SOUTH);
  if(dwarf.look(r-1, c) == APPLE_TREE)
    dwarf.start_pick(NORTH);
  if(dwarf.look(r, c+1) == APPLE_TREE)
    dwarf.start_pick(EAST);
  if(dwarf.look(r, c-1) == APPLE_TREE)
    dwarf.start_pick(WEST);
  return;
}

void pumpkinPick(Dwarf &dwarf, int r, int c){
  if(dwarf.look(r+1, c) == PUMPKIN)
    dwarf.start_pick(SOUTH);
  if(dwarf.look(r-1, c) == PUMPKIN)
    dwarf.start_pick(NORTH);
  if(dwarf.look(r, c+1) == PUMPKIN)
    dwarf.start_pick(EAST);
  if(dwarf.look(r, c-1) == PUMPKIN)
    dwarf.start_pick(WEST);
  return;
}

int closestTreeRow (Dwarf &dwarf, int rr, int cc){
  int ans = -1;
  int dist = 1000000;
  for (int r = 0; r < ROWS; r++){
    for (int c = 0; c < COLS; c++){
      if(dwarf.look(r, c)==APPLE_TREE || dwarf.look(r, c)==PINE_TREE){
	if(dist > sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2))){
	  dist = sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2));
	  ans = r;
	}
      }
    }
  }
  return ans;
}
int closestTreeCol (Dwarf &dwarf, int rr, int cc){
  int ans = -1;
  int dist = 100000000;
  for (int r = 0; r < ROWS; r++){
    for (int c = 0; c < COLS; c++){
      if(dwarf.look(r, c)==APPLE_TREE || dwarf.look(r, c)==PINE_TREE){
	if(dist > sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2))){
	  dist = sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2));
	  ans = c;
	}
      }
    }
  }
  return ans;
}
int closestPumpRow (Dwarf &dwarf, int rr, int cc){
  int ans = -1;
  int dist = 1000000;
  for (int r = 0; r < ROWS; r++){
    for (int c = 0; c < COLS; c++){
      if(dwarf.look(r, c)==PUMPKIN){
	if(dist > sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2))){
	  dist = sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2));
	  ans = r;
	}
      }
    }
  }
  return ans;
}
int closestPumpCol (Dwarf &dwarf, int rr, int cc){
  int ans = -1;
  int dist = 100000000;
  for (int r = 0; r < ROWS; r++){
    for (int c = 0; c < COLS; c++){
      if(dwarf.look(r, c)==PUMPKIN){
	if(dist > sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2))){
	  dist = sqrt(pow(dwarf.row()-r,2)+pow(dwarf.col()-c,2));
	  ans = c;
	}
      }
    }
  }
  return ans;
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

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();
  if(day>1)
    buildTime=false;
  if(day == 1 && dwarf.name()==4 && hours == 10)
    dwarf.start_walk(5,10);
  if(day > 1){
    if(dwarf.name() == 1 && hours == 8)
      dwarf.start_walk(20, 20);
    if(dwarf.name() == 0 && hours == 8)
      dwarf.start_walk(20, 2);
    if(dwarf.name() == 2 && hours == 8)
      dwarf.start_walk(2, 20);
  }
  if(dwarf.name()==3 && hours > 19 && hours < 21)
    dwarf.start_walk(3, 15);
  if(dwarf.name()==3 && (hours > 20 || hours < 2))
    dwarf.start_build(EAST);
  if(dwarf.name()==3 && hours > 1 && hours < 4)
    dwarf.start_walk(4, 9);
  if(dwarf.name()==5 && hours > 3 && hours < 6)
    dwarf.start_walk(3, 15);
  if(dwarf.name()==5 && hours == 6 && minutes > 15)
    dwarf.start_chop(EAST);
  if(dwarf.name()==5 && hours == 6 && minutes > 30)
    dwarf.start_walk(r, c+1);
  if(dwarf.name()==5 && hours == 6 && minutes > 45)
    dwarf.start_pick(EAST);
  if(hours > 17 || hours < 5){
    if(dwarf.name()!=4 && hours == 20 && minutes == 15 && day == 1)
      dwarf.start_chop(NORTH);
    if(dwarf.name()!=4 && hours == 20 && minutes == 30 && day == 1)
      dwarf.start_chop(SOUTH);
    if(dwarf.name()!=4 && hours == 20 && minutes == 45 && day == 1)
      dwarf.start_chop(EAST);
    if(dwarf.name()!=4 && hours == 21 && day == 1)
      dwarf.start_chop(WEST);
    if(dwarf.name()==0)
      dwarf.start_walk(4, 12);
    if(dwarf.name()==1)
      dwarf.start_walk(4, 11);
    if(dwarf.name()==2)
      dwarf.start_walk(4, 10);
    if(dwarf.name()==3)
      dwarf.start_walk(4, 9);
    if(dwarf.name()==5)
      dwarf.start_walk(5, 12);
    if(dwarf.name()==6)
      dwarf.start_walk(5, 11);
    if(dwarf.name()==7)
      dwarf.start_walk(5, 10);
    else if(dwarf.name()==4 && !buildTime2){
      dwarf.start_walk(8, 8);
      buildTime2=true;
    }
    else if(dwarf.name()==4 && day > 1)
      dwarf.start_walk(5, 9);
    else if(dwarf.name()==4 && buildTime2 && (day == 1 || (day == 2 && hours<6))){
      if(dwarf.look(dwarf.row()+1, dwarf.col())==FENCE){
	dwarf.start_walk(dwarf.row(), dwarf.col()+1);
	  }
      else{
	if(dwarf.look(dwarf.row(), dwarf.col()+1)==PINE_TREE || dwarf.look(dwarf.row(), dwarf.col()+1)==APPLE_TREE)
	  dwarf.start_chop(EAST);
	else if(dwarf.look(dwarf.row()+1, dwarf.col())==PINE_TREE || dwarf.look(dwarf.row()+1, dwarf.col())==APPLE_TREE)
	  dwarf.start_chop(SOUTH);
	else
	  dwarf.start_build(SOUTH);
      }
    }
  }
  if(isNextToAPumpkin(dwarf, r, c)){
      if((dwarf.look(r+1, c)==PUMPKIN || dwarf.look(r-1, c)==PUMPKIN || dwarf.look(r, c+1)==PUMPKIN || dwarf.look(r, c-1)==PUMPKIN) && (day > 1))
	pumpkinPick(dwarf, dwarf.row(), dwarf.col());
  }
  else if(isNextToATree(dwarf, r, c)){
    if((dwarf.look(r+1, c)==APPLE_TREE || dwarf.look(r-1, c)==APPLE_TREE || dwarf.look(r, c+1)==APPLE_TREE || dwarf.look(r, c-1)==APPLE_TREE) && (day > 1))
      appleTree(dwarf, dwarf.row(), dwarf.col());
    if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
    // If there is a tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
    }
    else if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
    // If there is a tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
    }
    else if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
    // If there is a tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }
    else if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
    // If there is a tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
    }
  }
  else {
    int rr = closestTreeRow(dwarf, r, c);
    int cc = closestTreeCol(dwarf, r, c);
    if(day == 7){
      rr = closestPumpRow(dwarf, r, c);
      cc = closestPumpCol(dwarf, r, c);
    }
    
    if(dwarf.lumber()>60 && flag && dwarf.name()==0){//this is control of 0
      dwarf.start_walk(4,7);
      flag = false;
      buildTime = true;
    }
    if(buildTime && hours < 12 && dwarf.name()==0 && day == 1){
      if(dwarf.look(4,7)==EMPTY || dwarf.look(4,7)==DWARF)
	dwarf.start_walk(4,7);
      else if (dwarf.look(3,7)==EMPTY || dwarf.look(3,7)==DWARF)
	dwarf.start_walk(3,7);
      else if (dwarf.look(5,7)==EMPTY || dwarf.look(5,7)==DWARF)
	dwarf.start_walk(5,7);
      else if (dwarf.look(4,6)==EMPTY || dwarf.look(4,6)==DWARF)
	dwarf.start_walk(4,6);
      else if (dwarf.look(4,8)==EMPTY || dwarf.look(4,8)==DWARF)
	dwarf.start_walk(4,8);
    }
    if(dwarf.look(dwarf.row()-1, dwarf.col())==FENCE && dwarf.row()<10 && dwarf.name()==0)
      dwarf.start_walk(dwarf.row()+1, dwarf.col());
    if(buildTime && dwarf.name()==0)
      dwarf.start_build(NORTH);
    
    if(buildTime && flag2 && dwarf.name()==1){//this is control of 1
      dwarf.start_walk(1,7);
      flag2=false;
    }
    if(buildTime && hours < 12 && dwarf.name()==1 && day == 1){
      if(dwarf.look(1,7)==EMPTY || dwarf.look(1,7)==DWARF)
	dwarf.start_walk(1,7);
      else if(dwarf.look(0,7)==EMPTY || dwarf.look(0,7)==DWARF)
	dwarf.start_walk(0,7);
      else if(dwarf.look(2,7)==EMPTY || dwarf.look(2,7)==DWARF)
	dwarf.start_walk(2,7);
      else if(dwarf.look(1,6)==EMPTY || dwarf.look(1,6)==DWARF)
	dwarf.start_walk(1,6);
      else
	dwarf.start_walk(1,8);
    }
    if(dwarf.look(dwarf.row()+1, dwarf.col())==FENCE && dwarf.col()<16 && dwarf.name()==1)
      dwarf.start_walk(dwarf.row(), dwarf.col()+1);
    if(buildTime && dwarf.name()==1)
      dwarf.start_build(SOUTH);
    
    if(buildTime && flag3 && dwarf.name()==2){//this is control of 2
      dwarf.start_walk(4,16);
      flag3 = false;
    }
    if(buildTime && hours < 12 && dwarf.name()==2 && day == 1){
      if(dwarf.look(4,16)==EMPTY || dwarf.look(4,16)==DWARF)
	dwarf.start_walk(4,16);
      else if(dwarf.look(3,16)==EMPTY || dwarf.look(3,16)==DWARF)
	dwarf.start_walk(3,16);
      else if(dwarf.look(5,16)==EMPTY || dwarf.look(5,16)==DWARF)
	dwarf.start_walk(5,16);
      else if(dwarf.look(4,15)==EMPTY || dwarf.look(4,15)==DWARF)
	dwarf.start_walk(4,15);
      else if(dwarf.look(4,17)==EMPTY || dwarf.look(4,17)==DWARF)
	dwarf.start_walk(4,17);
    }
    if(dwarf.look(dwarf.row()-1, dwarf.col())==FENCE && dwarf.row()<10 && dwarf.name()==2)
      dwarf.start_walk(dwarf.row()+1, dwarf.col());
    if(buildTime && dwarf.name()==2)
      dwarf.start_build(NORTH);

    /*else if(dwarf.look(3,4)==DWARF && dwarf.look(4, 4)==DWARF && dwarf.look(5, 4)==DWARF && dwarf.look(6, 4)==DWARF && dwarf.look(7, 4)==DWARF && dwarf.look(8, 4)==DWARF){
      log << "TEST" << endl;
      dwarf.start_build(EAST);
      }*/
    else if(dwarf.name()==0 && dwarf.look(dwarf.row()-1, dwarf.col())==FENCE){
      dwarf.start_build(EAST);
    }
    else if(dwarf.look(rr,cc+1)==EMPTY){
      log << "Walk to " << cc+1 << " " << rr << endl;
      dwarf.start_walk(rr,cc+1);
    }
    else if(dwarf.look(rr,cc-1)==EMPTY){
      log << "Walk to " << cc-1 << " " << rr << endl;
      dwarf.start_walk(rr,cc-1);
    }
    else if(dwarf.look(rr+1,cc)==EMPTY){
      log << "Walk to " << cc << " " << rr+1 << endl;
      dwarf.start_walk(rr+1,cc);
    }
    else if(dwarf.look(rr-1,cc)==EMPTY){
      log << "Walk to " << cc << " " << rr-1 << endl;
      dwarf.start_walk(rr-1,cc);
    }
    else{
      dwarf.start_walk(rr-1,cc);
    }
    return;
  }
}
