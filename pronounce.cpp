/*
Author: Andrew Giannico
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Project 2 Phase II

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

string Convert(string& str)
{
	locale settings;
	string converted;

	for(short i = 0; i < str.size(); ++i)
		converted += (toupper(str[i], settings));
	
	return converted;
}

int main(){
	string word = "";
	string ex = "";
	bool found = false;
	string compare= "";
	string insert = "";
	string insert2 = "";
	cin >> word;
	string ans="Pronunciation	: ";
	ifstream fin("Pro_Dictionary");
	while (fin >> compare){
		if (Convert(word) == compare){
			fin >> ex;
			getline(fin, insert);
			found = true;
			ans += ex + insert;
			fin.close();
		}
	}
	ans += "\n\nIdentical	: ";
	while (fin >> compare){
		getline(fin, insert2);
		if (insert == insert2){
			ans += compare;
		}
	}
	if (!found){
		ans = "Not found";
	}
	cout << ans << endl;
	return 0;
		
}
