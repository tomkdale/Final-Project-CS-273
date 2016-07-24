//Traffic Simulation
//CS 273 Final Project
// Created by Tom Dale
//last updated 7-24-2016

#include<iostream>
#include <stdexcept>
#include "intersection.h"
#include "roundabout.h"
#include "trafficlight.h"
using std::cout;
using std::cin;

roundabout test1;
trafficlight test2;

//function to handle non-int exception
int read_int()
{
	std::cin.exceptions(std::ios_base::failbit);
	int num = 0;
	while (true) {
		try {
			cin >> num;
			//return number if it was a good input
			return num;
		}
		catch (std::ios_base::failure) {
			cout << "Bad numeric string -- try again\n";
			cin.clear();
			cin.ignore(std::numeric_limits<int>::max(), '\n');
		}
	}
}

//used to set initial intersection data
void getuserinfo() {
	int avgcars;//total cars per hour
	int Ncars, Scars, Ecars, Wcars;// cars from each direction
	double percent1,percent2,percent3,percent4;//direction percentages for user input
	while (true) {//loop ensuring that values are in proper ranges
		//loop repeats when incorrect input is entered such as # < 0 or > 100 or the sum of all percentages is not equal 100 
		cout << "Enter the average total cars through the intersection per hour:\n";
		avgcars = read_int();//call read_int() to handle non-numeral exception
		if (avgcars <= 0) {
			cout << "Enter value greater than 0\n";
			continue;
		}
		cout << "Enter % cars coming from North street:";
		percent1 = read_int();
		if (percent1 < 0 || percent1 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Ncars = (percent1 / 100) * avgcars;
		cout << "Enter % cars coming from South street:";
		percent2 = read_int();
		if (percent2 < 0 || percent2 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Scars = (percent2 / 100) * avgcars;
		cout << "Enter % cars coming from East street:";
		percent3 = read_int();
		if (percent3 < 0 || percent3 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Ecars = (percent3 / 100) * avgcars;
		cout << "Enter % cars coming from West street:";
		percent4 = read_int();
		if (percent4 < 0 || percent4 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Wcars = (percent4 / 100) * avgcars;
		if (percent1 + percent2 + percent3 + percent4 != 100) {
			cout << "Percentages do not equal 100.\n";
			continue;
		}
		if (Wcars + Ecars + Ncars + Scars <= 0) {
			cout << "Choose a larger traffic inflow, # cars is < 1.\n";
			continue;
		}

		bool show = false;
		char response;
		cout << "Would you like too see all traffic data? 'y' or 'n'\n";
		cin >> response;
		if (response =='y' || response == 'Y')//if user chooses to see traffic data set show to true
			show = true;
		//else leave false
		test1.set_cars(Ncars, Scars, Ecars, Wcars, show);
		test2.set_cars(Ncars, Scars, Ecars, Wcars,show);
		break;
	}
}


int main() {
	seedRandom();//initiates new random seed
	cout << "Welcome to the CS-273ville traffic intersection simulation.\n";
	getuserinfo();
	cout << "Running roundabout simulation.\n";
	test1.run();
	cout << "Running traffic light simulation.\n";
	test2.run();
	test1.outputdata();
	test2.outputdata();
	 if (test1.rate() < test2.rate()) 
		cout << "A roundabout is recommended at this intersection.\n";
	else
		cout << "A traffic light is recommended at this intersection.\n";
}