/*
Author: Andrew Giannico
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2 Phase III
This program will take in a word and print out the pronunciation and words in the dictionary that have the exact same pronunciation.
*/
#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include <string>
#include <locale>

using namespace std;

void splitOnSpace(string s, string & before, string & after) {
  // reset strings
  before = ""; 
  after = "";
  // accumulate before space
  int i = 0;
  while (i < s.size() && not isspace(s[i])) { before += s[i]; i++; }
  // skip the space
  i++;
  // accumulate after space
  while (i < s.size()) { after += s[i]; i++; }
}

int countSpaces (string input){ //this counts spaces in a string
  int num = 0;
  string space = " ";
  for ( int i = 0; i < input.length(); i++){
    if (input.substr(i,1) == space)
      num++;
  }
  return num;
}

string Convert(string& str) //this will convert to capital letters
{
	locale settings;
	string converted;

	for(short i = 0; i < str.size(); ++i)
		converted += (toupper(str[i], settings));
	
	return converted;
}

int main(){
	string word = "";
	int counter = 0;
	int spaceCount = 0;
	string spaces = "";
	bool found = false;
	bool firsti = true;
	string compare= "";
	string insert = "";
	string insert2 = "";
	string insert3 = "";
	string pro=""; //this holds the original pronunciation from the first part
	string past=""; //this holds the original word from the first part
	string r1 = "";
	string r2 = "";
	string r3 = "";
	string r4 = ""; //these r strings are used in the replacement section
	string r5 = "";
	string r6 = "";
	string a="";
	string b="";
	cin >> word;
	string ans="Pronunciation	:";
	ifstream fin("Pro_Dictionary");
	while (getline(fin,insert)){
	  splitOnSpace(insert, a, b);
	  if (a == Convert(word)){
	    ans+=b;
	    past = a;
	    pro = b;
	    found = true;
	    fin.close();
	  }
	}
	ans += "\n\nIdentical	: ";
	fin.open ("Pro_Dictionary");
	while (getline(fin, insert2)){
	  splitOnSpace(insert2, a, b);
		if (b == pro){
		  if(Convert(past) != a)
			ans += a + " ";
		}
	}
	fin.close();
	spaceCount = countSpaces(pro);
	ans += "\nReplace phoneme\t: ";
	fin.open ("Pro_Dictionary");
	while (getline(fin, insert3)){
	  splitOnSpace(insert3, a, b);
	  r2 = pro;
	  r4 = b;
	  if (spaceCount == countSpaces(r4)){
	  for (int i = 0; i < spaceCount+1; i++){
	    splitOnSpace(r2, r1, r2);
	    splitOnSpace(r4, r3, r4);
	    if (r1 != r3){
	      counter++;
	    }
	    
	  }
	  if (counter < 2 && a != past){
	    ans += a + " ";
	  }
	  counter = 0;
	  }
	}
	    
	if (!found){ //this is the error message if the word is not in the dictionary
	ans = "Not found";
	}
	
	cout << ans << endl;
	return 0;	
	
}
