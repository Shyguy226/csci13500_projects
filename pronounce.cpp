/*
Author: Andrew Giannico
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2 Phase V
This program will take in a word and print out the pronunciation and words in the dictionary that have the exact same pronunciation. Then it will give all words than can be obtained by replacing one phoneme. Then, it will have the same list for adding one phoneme. Finally, it will have a list for removing one phoneme.
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

int countSpaces (string input){
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
	string names [100];
	int counter = 0;
	int spaceCount = 0;
	int cooc = 0;
	int name;
	string spaces = "";
	bool found = false;
	bool firsti = true;
	bool flag1 = false;
	string compare= "";
	string insert = "";
	string insert2 = "";
	string insert3 = "";
	string pro="";
	string past="";
	string r1 = ""; //the r strings are holding tools during comparisons
	string r2 = "";
	string r3 = "";
	string r4 = "";
	string r5 = "";
	string r6 = "";
	string a=""; //a will always hold the word to potentially be added
	string b=""; //b will always hold the pronunciation to the new word
	cin >> word;
	string ans="Pronunciation	:";
	ifstream fin("cmudict.0.7a");
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
	fin.open ("cmudict.0.7a");
	while (getline(fin, insert2)){
	  splitOnSpace(insert2, a, b);
		if (b == pro){
		  if(Convert(past) != a){
			ans += a + " ";
			names[cooc]=a; //this is for Replace to not get mimics
			cooc++;
		  }
		  
		}
	}
        
	fin.close();
	spaceCount = countSpaces(pro); //counts spaces in main pronunciation
	counter = 0;
	ans += "\nAdd phoneme\t: ";
	fin.open("cmudict.0.7a");
	while (getline(fin, insert3)){
	  splitOnSpace(insert3, a, b);
	  r2 = pro;
	  r4 = b;
	  if ((spaceCount + 1) == countSpaces(r4)){
	    for (int i = 0; i <= spaceCount+1; i++){
	      r5 = r2;
	      splitOnSpace(r2, r1, r2);
	      splitOnSpace(r4, r3, r4);
	      if (r1 != r3){
		counter++;
		splitOnSpace(r4, r3, r4);
	        if(r1 != r3)
		  counter++;
	      }
	    }
	    if (counter < 2)
	      ans += a + " ";
	    counter = 0;
	  }
	}
	fin.close();
	counter = 0;
	     
	ans +="\nRemove phoneme\t: ";
	fin.open("cmudict.0.7a");
	while (getline(fin, insert3)){
	  splitOnSpace(insert3, a, b);
	  r2 = pro;
	  r4 = b;
	  if (spaceCount == (countSpaces(r4)+1)){
	    for (int i = 0; i <= spaceCount; i++){
	      r5 = r4;
	      splitOnSpace(r2, r1, r2);
	      splitOnSpace(r4, r3, r4);
	      if(r1 != r3){
		counter++;
		splitOnSpace(r2, r1, r2);
	        if(r1 != r3)
		  counter++;
	      }
	    }
	    if (counter < 2) //less than 2 beacause only 1 difference is allowed
	      ans += a + " ";
	    counter = 0;
	  }
	}
	fin.close();
	ans += "\nReplace phoneme\t: ";
	counter = 0;
	fin.open ("cmudict.0.7a");
	while (getline(fin, insert3)){ //this section is parsing the phonemes
	  splitOnSpace(insert3, a, b);
	  r2 = pro;
	  r4 = b;
	  if (spaceCount == countSpaces(r4)){ //this compares length
	  for (int i = 0; i <= spaceCount; i++){
	    splitOnSpace(r2, r1, r2);
	    splitOnSpace(r4, r3, r4);
	    if (r1 != r3){ //counts how many phonemes are different
	      counter++;
	    }
	    
	  }
	  for (int i = 0; i < cooc; i++){ //for each identical, take em out
	    if (a == names[i])
	      flag1=true;
	  }
	  if (counter < 2 && a != past && flag1==false){ //filters out
	    for (int i = 0; i < a.length(); i++){
	      if (a[i] == '(');
	      else
	         ans += a + " ";
	    }
	  }
	  counter = 0;
	  flag1 = false;
	  }
	}
	fin.close();
	if (!found){ //if the word does not exist in the dictionary
	ans = "Not found";
	}
	
	cout << ans << endl;
	return 0;	
	
}
