#ifndef VEHICLE
#define VEHICLE
#include <fstream>
#include "random.h"
#include <set>
using namespace std;

class set_of_cars; //set holding all CS273ville people and their cars

//class for cars that drive through simulated intersections
class Car {
private:
	string name;//driver name
	string type;//vehicle type
	string turning;//turning direction
	string roadIN;//road entering from
	string roadOUT;//road leaving to
	int start;//timer start when added to queue
	int end;//timer end when arrived at desired road out
public:
	//constructor takes name and car type
	Car(string name, string type) {
		this->name = name;
		this->type = type;
		turning = randomDirection();
	}
	//set start timer
	void set_start(int now) {
		start = now;
	}
	//set end timer
	void set_end(int now) {
		end = now;
	}

	//set roadIn, and then calculated roadOut based on turning direction
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

	// less than overloaded operator to organize list alphabetically
	bool operator<(const Car &other) const {
		if (name < other.name)
			return true;
		return false;
	}
	
	//returns type of vehicle, useful to tell if vehicle is emergency 
	string get_type() const {
		return type;
	}

	//returns time car started at
	long unsigned int get_start() {
		return start;
	}

	//returns total wait time
	long unsigned int get_wait() {
		return end - start;
	}

	//prints individual car movement data, used when show is chosen true
	void print_data() const
	{
		cout << name << " entered from " << roadIN << " street driving a " << type << " " << turning << " through the intersection in " << end - start << " seconds.\n";
	}

	// returns time for emergency vehicles to move through intersection
	int get_time_through() {
		if (turning == "straight")
			return 4;
		if (turning == "left")
			return 6;
		return 2;
	}

	//returns  desired exit
	string get_exit() const {
		return roadOUT;
	}
};

//class for holding and manipulating an alphabetical set of humans and their cars
class set_of_cars{
	set <Car*> garage;
public:
	//no arg constructor loads in names from residents file
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
			Car* C =  new Car(name, type);
			garage.insert(C);

		}
		cin.rdbuf(orig_cin);
		ss.close();
	}

	//returns pointer to random car obj
	Car* getNewCar() {
		set<Car*>::iterator it = garage.begin();
		int whichCar = randomInt(1900); //get a random number representing one of the 0 - 2000 residents
		for (int i = 0; i < whichCar; i++) {
			++it;
		}
		return *it;
	}
};

#endif