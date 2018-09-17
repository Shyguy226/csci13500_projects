/*
Author: Andrew Giannico
Course: CSCI-133
Instructor: Mike Zamansky
Assignment: Project 1 Task B
This program reads a .txt file and reads plusses and minuses as well as numbers to properly assess the experession.
*/
#include <iostream>

using namespace std;

int main () {
	char n; //need a char for '-' and '+'
	int tot, temp;
	int minus = 1; //keeps track of minus or plus
	while (cin >> temp){
		if (cin.fail() ){
			cin >> n;
			if (n == '-')
				minus = -1;
			else
				minus = 1; 
		}
		tot += temp * minus;
	}
	cout << tot << endl;
	return 0;
}
