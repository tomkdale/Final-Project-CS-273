#ifndef RAND
#define RAND
#include <cstdlib>
#include <string>
#include <ctime>

//special function for car arrival returns true x/3600 of the time
void seedRandom() {
	srand(time(0));
}
//returns true x / 1 hour % of the time, used for entering car
bool random(int x) {
	double num = rand() % 3600;
	if (num < x)
		return true;
	else return false;

}

//returns random direction
std::string randomDirection() {
	int x = rand() % 4;
	if (x <= 1)
		return "left"; // 25% likely
	else if (x <= 2)
		return "right";// 25% likely
	else
		return "straight";// 50% likely
}


//returns types of cars at differing percent chances
std::string randomType() {
	int x = rand() % 400;
	if (x == 0)
		return "ambulance"; //.25% likely
	if (x == 1)
		return "firetruck";//.25% likely
	if (x == 2)
		return "police car";//.25% likely
	if (x < 20)
		return "motorcycle"; //4.5% likely
	if (x < 30)
		return "semi-truck"; //2.5% likely
	if (x < 40)
		return "bus"; // 2.5% likely
	if (x < 220)
		return "truck"; //45% likely
	return "car"; // 45% likely 
}


//returns integer between 0 and total used for getting random item in set
int randomInt(int total) {
	int x = rand() % total;
	return x;
}


#endif