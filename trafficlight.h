#include "intersection.h"

class trafficlight : public intersection {
private:
public:
	void moveCarsIn() {

	}
	void moveCarsOut() {

	}
	void outputdata() {
		cout << "traffic light has finished\n";
	}
	int rate()
	{
		return totalWait;
	}
};