/*
Author: Andrew Giannico
Course: CSCI-133
Instructor: Mr. Zamanksy
Assignment: Project 1 Task D
This program will take multiple lines of calculator inputs with addition, subtraction, and squaring and display answers per 
line.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main () {
	char place;
	int tot = 0;//this variable will hold the total
	int temp = 0; 
	int sign = 1;//this variable will distinguish between plus and minus
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
		else if (place == ';'){//this will complete the operation and move to the next line
			tot += temp * sign;
			cout << tot << endl;
			tot = 0;
			temp = 0;
			sign = 1;
		}
		else if (place == '^'){//this will square the number being logged
			temp = pow(temp, 2);
		}
		else {
			temp *= 10;
			temp += (int)place-48;
		}
		
		
	}
	return 0;
}
