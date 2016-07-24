#include "intersection.h"
#include "Vehicle.h"
#include "random.h"
#include <string>
#include <iostream>
using namespace std;

class roundabout : public intersection {
private:
	Car* NNE = NULL;// 8 positions in the roundabout NULL if empty
	Car* NEE = NULL;
	Car* SEE = NULL;
	Car* SSE = NULL;
	Car* SSW = NULL;
	Car* SWW = NULL;
	Car* NWW = NULL;
	Car* NNW = NULL;
	Car* overlap = NULL;// abstract position to prevent overlap of cars (see move carsOut)


	//move any cars that are ready out of intersection
	void moveCarsOut() {
		if (NNE && NNE->get_exit() == "north") {//is car ready to exit
			NNE->set_end(tick);//set end time to now
			totalWait += NNE->get_wait();//update total wait
			if (show)
				NNE->print_data();
			NNE = NULL;//clear space
		}
		if (NWW && NWW->get_exit() =="west") {//repeat for W, S, E
			NWW->set_end(tick);
			totalWait += NWW->get_wait();
			if (show)
				NWW->print_data();
			NWW = NULL;
		}
		if (SSW && SSW->get_exit() =="south") {
			SSW->set_end(tick);
			totalWait += SSW->get_wait();
			if (show)
				SSW->print_data();
			SSW = NULL;
		}
		if (SEE && SEE->get_exit() == "east") {
			SEE->set_end(tick);
			totalWait += SEE->get_wait();
			if (show)
				SEE->print_data();
			SEE = NULL;
				
		}
		
	}
	

		//rotate all car positions in roundabout
		void moveTraffic() {
			overlap = NNE;
			NNE = NEE;
			NEE = SEE;
			SEE = SSE;
			SSE = SSW;
			SSW = SWW;
			SWW = NWW;
			NWW = NNW;
			NNW = overlap;
		
	}

		//move waiting cars into intersection
	void moveCarsIn() {
		if (tick % 3 != 0) // wait 2 seconds each time this function is called in order to simulate hesitation
			return;
		if (!Nline.empty() && !(NNW)) {//if car is waiting in line and space is free to enter
			NNW = Nline.front();//move car into space
			Nline.pop();
			lineWait += tick - NNW->get_start();
		}
		if (!Wline.empty() && !(SWW)) {//repeate for W,S,E
			SWW = Wline.front();
			Wline.pop();
			lineWait += tick - SWW->get_start();
		}
		if (!Sline.empty() && !(SSE)) {
			SSE = Sline.front();
			Sline.pop();
			lineWait += tick - SSE->get_start();
		}
		if (!Eline.empty() && !(NEE)) {
			NEE = Eline.front();
			Eline.pop();
			lineWait += tick - NEE->get_start();
		}
	}
public:
	//show total wait time
	void outputdata() {

		unsigned long int minutes = lineWait / 60;
		int seconds = lineWait % 60;
		cout << "The time cars spend waiting to enter roundabout was " << minutes << "minutes and " << seconds << "seconds.\n";
		minutes = totalWait / 60;
		seconds = totalWait % 60;
		cout << "Total use time for roundabout was " << minutes << "minutes and " << seconds << "seconds.\n";
	}
	int rate() {
		return totalWait;
	}
};

