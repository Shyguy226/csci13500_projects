/*
Author: Andrew Giannico
Course: CSCI-133
Instructor: Mr. Zamanksy
Assignment: Project 1 Task C
This program will take multiple lines of calculator inputs with addition and subtraction and display answers per line.
*/
#include <iostream>

using namespace std;

int main () {
	char place;//this is what each character in the .txt is initially assigned to
	int tot = 0;
	int temp = 0; 
	int sign = 1; //keeps track of minus or plus
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
		else if (place == ';'){ //this is the line that resets for a new line in the .txt
			tot += temp * sign;
			cout << tot << endl;
			tot = 0;
			temp = 0;
			sign = 1;
		}
		else {
			temp *= 10;
			temp += (int)place-48;
		}
		
		
	}
	return 0;
}
