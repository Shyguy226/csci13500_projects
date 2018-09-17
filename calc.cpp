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
	char n;
	int tot, temp;
	int minus = 1;
	int c = 0;
	while (cin >> temp && c < 10){
		if (cin.fail() ){
			cin >> n;
			if (n == '-')
				minus = -1;
			else
				minus = 1;
		}
		tot += temp * minus;
		c++;
	}
	cout << tot << endl;
	return 0;
}
