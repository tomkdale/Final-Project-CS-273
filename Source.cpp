//Traffic Simulation
//CS 273 Final Project
// Created by Tom Dale

#include<iostream>
#include "intersection.h"
#include "roundabout.h"
#include "trafficlight.h"
#include <stdexcept>
using std::cout;
using std::cin;

roundabout test1;
trafficlight test2;


void getuserinfo() {//used to set initial intersection data
	int avgcars;//total cars per hour
	int Ncars, Scars, Ecars, Wcars;// cars from each direction
	double percent1,percent2,percent3,percent4;//direction percentages for user input
	while (true) {//loop ensuring that values are acceptable
		//loop repeats when incorrect input is entered such as # < 0 or > 100 or the sum of all percentages is not equal 100 
		cout << "Enter the average total cars through the intersection per hour:\n";
		cin >> avgcars;
		if (avgcars <= 0) {
			cout << "Enter value greater than 0\n";
			continue;
		}
		cout << "Enter % cars coming from North street:";
		cin >> percent1;
		if (percent1 < 0 || percent1 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Ncars = (percent1 / 100) * avgcars;
		cout << "Enter % cars coming from South street:";
		cin >> percent2;
		if (percent2 < 0 || percent2 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Scars = (percent2 / 100) * avgcars;
		cout << "Enter % cars coming from East street:";
		cin >> percent3;
		if (percent3 < 0 || percent3 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Ecars = (percent3 / 100) * avgcars;
		cout << "Enter % cars coming from West street:";
		cin >> percent4;
		if (percent4 < 0 || percent4 > 100) {
			cout << "Invalid entry. Enter # 0-100\n";
			continue;
		}
		Wcars = (percent4 / 100) * avgcars;
		if (percent1 + percent2 + percent3 + percent4 != 100) {
			cout << "Percentages do not equal 100.\n";
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
	seedRandom();
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

//FIXME handle entry exceptions like 'h' or '.7'

//FIXME get car data from traffic light to show itself