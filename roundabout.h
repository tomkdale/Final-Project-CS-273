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


	//move any cars that can out of intersection
	void moveCarsOut() {
		if (NNE && NNE->get_exit("north")) {//is car ready to exit
			NNE->set_end(tick + 1);//set end time to now
			totalWait += NNE->get_wait();//update total wait
			if (show)
				NNE->print_data();
			NNE = NULL;
		}
		if (NWW && NWW->get_exit("west")) {//repeat for W, S, E
			NWW->set_end(tick + 1);
			totalWait += NWW->get_wait();
			if (show)
				NWW->print_data();
			NWW = NULL;
		}
		if (SSW && SSW->get_exit("south")) {
			SSW->set_end(tick + 1);
			totalWait += SSW->get_wait();
			if (show)
				SSW->print_data();
			SSW = NULL;
		}
		if (SEE && SEE->get_exit("east")) {
			SEE->set_end(tick + 1);
			totalWait += SEE->get_wait();
			if (show)
				SEE->print_data();
			SEE = NULL;
				
		}
		
		rotate();//call rotate function for remaining cars in roundabout
		
	}
	

		//rotate all car positions in roundabout
		void rotate() {
			overlap = NNE;
			NNE = NEE;
			NEE = SEE;
			SEE = SSE;
			SSE = SSW;
			SSW = SWW;
			SWW = NWW;
			NWW = NNW;
			NNW = overlap;
			
			//FIXME deletethis
			if (NNE != NULL)
				cout << "1";
			else cout << "0";
			if (NEE != NULL)
				cout << "1";
			else cout << "0";
			if (SEE != NULL)
				cout << "1";
			else cout << "0";
			if (SSE != NULL)
				cout << "1";
			else cout << "0";
			if (SSW != NULL)
				cout << "1";
			else cout << "0";
			if (SWW != NULL)
				cout << "1";
			else cout << "0";
			if (NWW != NULL)
				cout << "1";
			else cout << "0";
			if (NNW != NULL)
				cout << "1";
			else cout << "0";
			cout << "\n";
		//	*/
	}

		//move waiting cars into intersection
	void moveCarsIn() {
		if (!Nline.empty() && !(NNW)) {//if car is waiting in line and space is free to enter
			NNW = Nline.front();//move car into space
			Nline.pop();
		}
		if (!Wline.empty() && !(SWW)) {//repeate for W,S,E
			SWW = Wline.front();
			Wline.pop();
		}
		if (!Sline.empty() && !(SSE)) {
			SSE = Sline.front();
			Sline.pop();
		}
		if (!Eline.empty() && !(NEE)) {
			NEE = Eline.front();
			Eline.pop();
		}
	}
public:
	void outputdata() {
		cout << "Roundabout has finished\n";
	}
	int rate() {
		return totalWait;
	}
};

