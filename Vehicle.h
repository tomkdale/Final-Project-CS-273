#ifndef VEHICLE
#define VEHICLE
#include <string>
#include <fstream>
#include "random.h"
#include <set>
#include <iostream>
using namespace std;
class set_of_cars; 

class Car {
private:
	string name;
	string type;
	string turning;
	string roadIN;
	string roadOUT;
	int start;
	int end;

	int seven = 7; //FIXME
public:
	Car(string name, string type) {
		this->name = name;
		this->type = type;
		turning = randomDirection();
	}
	void set_start(int now) {
		start = now;
	}
	void set_road(string road) {
		this->roadIN = road;
		int counter;
		if (roadIN == "north") counter = 0;
		else if (roadIN == "west") counter = 1;
		else if (roadIN == "south") counter = 2;
		else counter = 3;
		if (turning == "left") counter = counter + 3;
		else if (turning == "straight") counter = counter + 2;
		else counter = counter + 1;
		counter = counter % 4;
		if (counter == 0) roadOUT = "north";
		else if (counter == 1) roadOUT = "west";
		else if (counter == 2) roadOUT = "south";
		else roadOUT = "east";

	}

	bool operator<(const Car &other) const {// less than overloaded operator to organize list alphabetically
		if (name < other.name)
			return true;
		return false;
	}
	void set_end(int now) {
		end = now;
	}
	string get_type() const {
		return type;
	}

	int get_seven() {//FIXME
		return seven;
	}
	long unsigned int get_wait() {
		return end - start;
	}
	void print_data() const
	{
		cout << name << " entered from " << roadIN << " street driving a " << type << " " << turning << " through the intersection in " << end - start << " seconds.\n";
	}
	int get_time_through() {// returns time for emergency vehicles to move through intersection
		if (turning == "straight")
			return 4;
		if (turning == "left")
			return 6;
		return 2;
	}
	string get_name() const{
		return name;
	}

	//returns true if upcoming road is desired exit
	bool get_exit(string road) {
		if (road == roadOUT)
			return true;
		else
			return false;
	}
};

class set_of_cars{//class for holding and manipulating an alphabetical set of cars
	set <Car> garage;
public:
	set_of_cars() {
		//read from file 2000 names
		//add each to new spot in list
		//each name also has vehicle type
		ifstream ss("residents_of_273ville.txt");
		if (ss.fail())
			cout << "Error reading file";
		streambuf *orig_cin = cin.rdbuf(ss.rdbuf());
		string name;
		for (int i = 0; i < 2000; i++) {
			cin >> name;
			string type = randomType();
			Car newCar(name, type);
			garage.insert(newCar);

		}
		cin.rdbuf(orig_cin);
		ss.close();
	}

	Car getNewCar() {
		set<Car>::iterator it = garage.begin();
		int whichCar = randomInt(1900); //get a random number representing one of the 0 - 2000 residents
		for (int i = 0; i < whichCar; i++) {
			++it;
		}
		return *it;
	}
};

#endif