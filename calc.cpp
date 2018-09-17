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
	char place;
	int tot = 0;
	int temp = 0; 
	int sign = 1;
	while (cin >> place){
		if (place == '-'){
			tot += temp * sign;
			sign = -1;
			temp=0;
		}
		else if (place == '+'){
			tot += temp * sign;
			sign = 1;
			temp=0;
		}
		else {
			temp *= 10;
			temp += (int)place-48;
		}
		
	}
	tot += temp * sign;
	cout << tot << endl;
	return 0;
}
