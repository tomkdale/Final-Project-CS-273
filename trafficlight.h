#ifndef TRAFFICLIGHT
#define TRAFFICLIGHT

#include "intersection.h"

class trafficlight : public intersection {
private:
	bool NSlight;//true means north-south light is on, false means east-west light is on
	Car* NE = NULL;//spaces to drive in
	Car* SE = NULL;
	Car* SW = NULL;
	Car* NW = NULL;
	Car* NSoverlap = NULL;//used to avoid north south left hand collisions
	Car* EWoverlap = NULL;//used to avoid east west left hand collisions
	int lightTime = 0; //time light has stayed the same

	// call to change light depending on if cars are waiting and if light has been on for 3 minutes
	void changeLight() {
		if (Nline.empty() && Wline.empty() && Sline.empty() && Eline.empty())//no one is at intersection
			return;
		if (NSlight) {//north south traffic ligh is on
			if (Nline.empty() && Sline.empty()) {//if light is on but no one needs it
				NSlight = false;
				return;
			}
			if (lightTime > 180 && !(Eline.empty() && Wline.empty())){//if it is time for light to change and cars are waiting for it
				NSlight = false;
				return;
			}
		}
		else {//east west traffic line is on
			if (Eline.empty() && Wline.empty()) {//if light is on but no one needs it
				NSlight = true;
				return;
				if (lightTime > 180 && !(Nline.empty() && Sline.empty())) {//if it is time for light to change and cars are waiting for it
					NSlight = true;
					return;
				}
			}
		}
	}

	//moves cars in that have room and are allowed to by the light
	void moveCarsIn() {
		//check if light should be switched
		if (tick % 3 == 0)//wait two seconds to simulate yellow light
			changeLight();
		lightTime++;

		if (!Nline.empty() && !NW) {//if there is at least one car waiting in North street and first space is open
			bool move = false;
			if (Nline.front()->get_exit() == "west") move = true;//if turning right then go ahead
			else if (NSlight) {//if light is on
				if (Nline.front()->get_exit() == "south") move = true;//if going straight go ahead
				else if (Sline.empty() || Sline.front()->get_exit() == "west") move = true;// if other lane has no cars or if car is also turning left then go ahead
			}
			if (move){//if car is ready to enter then do this
				NW = Nline.front();//move car in
				Nline.pop();//take away from queue
				lineWait += tick - NW->get_start();//update total lineWait
			}
		}
		if (!Sline.empty() && !SE) {//if there is at least one car waiting in North street and first space is open
			bool move = false;
			if (Sline.front()->get_exit() == "east") move = true;//if turning right then go ahead
			else if (NSlight) {//if light is on
				if (Sline.front()->get_exit() == "north") move = true;//if going straight go ahead
				else if (Nline.empty() || Nline.front()->get_exit() == "east") move = true;// if other lane has no cars or if car is also turning left then go ahead
			}
			if (move) {//if car is ready to enter then do this
				SE = Sline.front();//move car in
				Sline.pop();//take away from queue
				lineWait += tick - SE->get_start();//update total lineWait
			}
		}
		if (!Wline.empty() && !SW) {//if there is at least one car waiting in North street and first space is open
			bool move = false;
			if (Wline.front()->get_exit() == "south") move = true;//if turning right then go ahead
			else if (!NSlight) {//if light is on
				if (Wline.front()->get_exit() == "east") move = true;//if going straight go ahead
				else if (Eline.empty() || Eline.front()->get_exit() == "south") move = true;// if other lane has no cars or if car is also turning left then go ahead
			}
			if (move) {//if car is ready to enter then do this
				SW = Wline.front();//move car in
				Wline.pop();//take away from queue
				lineWait += tick - SW->get_start();//update total lineWait
			}
		}
		if (!Eline.empty() && !NE) {//if there is at least one car waiting in North street and first space is open
			bool move = false;
			if (Eline.front()->get_exit() == "north") move = true;//if turning right then go ahead
			else if (!NSlight) {//if light is on
				if (Eline.front()->get_exit() == "west") move = true;//if going straight go ahead
				else if (Wline.empty() || Wline.front()->get_exit() == "north") move = true;// if other lane has no cars or if car is also turning left then go ahead
			}
			if (move) {//if car is ready to enter then do this
				NE = Eline.front();//move car in
				Eline.pop();//take away from queue
				lineWait += tick - NE->get_start();//update total lineWait
			}
		}
	}

	//move any cars that are ready out of intersection
	void moveCarsOut() {

		if (tick % 2 == 0)//one move should take two seconds, so only execut every other time
			return;

		if (NE && NE->get_exit() == "north"){//if car in upper right is leaving north
			NE->set_end(tick);//set end time to now
			totalWait += NE->get_wait();//update total wait
			if (show)
				NE->print_data();
			numCars++;
			NE = NULL;//clear space
		}
		if (NW && NW->get_exit() == "west") {//repeat for W,S, E
			NW->set_end(tick);
			totalWait += NW->get_wait();
			if (show)
				NW->print_data();
			numCars++;
			NW = NULL;
		}
		if (SW && SW->get_exit() == "south") {
			SW->set_end(tick);
			totalWait += SW->get_wait();
			if (show)
				SW->print_data();
			numCars++;
			SW = NULL;
		}
		if (SE && SE->get_exit() == "east"){
			SE->set_end(tick);
			totalWait += SE->get_wait();
			if (show)
				SE->print_data();
			numCars++;
			SE = NULL;
		}
	}

	//moves traffic in intersection 
	void moveTraffic() {
		//remember no car will be right next to its exit because it was removed in moveCarsOut()
	
		if (tick % 2 == 0)//one move should take two seconds, so only execut every other time
			return;
		NSoverlap = SE;//move south east car to overlap space (for left turn crash purposes)
		SE = NULL;
		if (NW) {//if car in this space move towards final destination
			if (NW->get_exit() == "south")
				SW= NW;
			else 
				SE = NW;
			NW = NULL;
		}
		if (NSoverlap) {//if overlap was used then move it to real space
			if (NSoverlap->get_exit() == "north") // move NSoverlap placed car towards final destination
				NE = NSoverlap;
			else
				NW = NSoverlap;
			NSoverlap = NULL;
		}

		EWoverlap = SW;
		SW = NULL;
		if (NE) {//if car in this space move towards final destination
			if (NE->get_exit() == "west")
				NW = NE;
			else
				SW = NE;
			NE = NULL;
		}
		if (EWoverlap) {//if overlap was used then move it to real space
			if (EWoverlap->get_exit() == "east") // move NSoverlap placed car towards final destination
				SE = EWoverlap;
			else
				NE = EWoverlap;
			NSoverlap = NULL;
		}

	}

public:
	//show total wait time
	void outputdata() {
		///return data for time waiting for intersection, time in intersection, and average total time
		unsigned long int minutes = lineWait / 60;
		int seconds = lineWait % 60;
		cout << "The time cars spent waiting to enter lighted intersection was " << minutes << "minutes and " << seconds << "seconds.\n";
		unsigned long IN = totalWait - lineWait;//get time just inside the intersection
		minutes = IN / 60;
		seconds = IN % 60;
		cout << "The time cars spent in lighted intersection was " << minutes << "minutes and " << seconds << "seconds.\n";
		minutes = (totalWait / numCars) / 60;
		seconds = (totalWait / numCars) % 60;
		cout << "The average time it takes for a car to move through is " << minutes << "minutes and " << seconds << "seconds.\n\n";
	}

	//returns total wait time
	int rate() {
		return totalWait;
	}
};

#endif