#include "stdafx.h"
#include "CppUnitTest.h"
#include "random.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <set>
#include <queue>
#include <fstream>
#include "intersection.h"
#include "roundabout.h"
#include "trafficlight.h"
#include "Vehicle.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FinalUnitTester
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		//tests randombool function in random
		TEST_METHOD(randombool)
		{
			seedRandom();
			Assert::AreEqual(random(3600), true);
		}

		//tests randomdirection function in random
		TEST_METHOD(randomstring)
		{
			seedRandom();
			string direction = randomDirection();
			string left = "left";
			string right = "right";
			string straight = "straight";
			if (direction != left && direction != right && direction != straight)
				Assert::Fail();
		}

		//tests randomint function in random
		TEST_METHOD(randomint)
		{
			seedRandom();
			Assert::AreEqual(randomInt(1) , 0);
		}

		//tests roundabout with few cars
		TEST_METHOD(roundaboutRate)
		{
			roundabout tester;
			tester.set_cars(10, 20, 30, 40, false);
			tester.run();
			if (tester.rate() < 1)
				Assert::Fail();
		}

		//tests lighted intersection with few cars
		TEST_METHOD(lightedintersectionRate)
		{
			roundabout tester;
			tester.set_cars(10, 20, 30, 40, false);
			tester.run();
			if (tester.rate() < 1)
				Assert::Fail();
			
		}

		//tests car constructor and get name
		TEST_METHOD(correctName)
		{
			string name = "joe";
			string type = "truck";
			Car truck(name,type);
			Assert::AreEqual(truck.get_type(), type);
		}


		//tests set start and get start function for car
		TEST_METHOD(correctTime)
		{
			string name = "joe";
			string type = "truck";
			Car truck(name, type);
			unsigned long int start = 7;
			truck.set_start(start);
			Assert::AreEqual(truck.get_start(), start);
		}

		//tests set road and get exit functions in car
		TEST_METHOD(roadOut)
		{
			string name = "joe";
			string type = "truck";
			string direction = "north";
			Car truck(name, type);
			truck.set_road(direction);
			Assert::AreNotEqual(truck.get_exit(), direction);
		}

		//tests overloaded operator in car
		TEST_METHOD(greaterCar)
		{
			Car firstCar("Aaron", "truck");
			Car secondCar("Bernie", "bus");
			if (!(firstCar < secondCar))
				Assert::Fail();
		}


		//tests get wait function in car
		TEST_METHOD(changeInTime)
		{
			string name = "joe";
			string type = "truck";
			Car truck(name, type);
			truck.set_start(5);
			truck.set_end(10);
			long unsigned int num = 5;
			Assert::AreEqual(truck.get_wait(), num);
		}

		//tests the getter function and no arg constructor of set_of_cars
		TEST_METHOD(setofcars)
		{
			set_of_cars garage;
			Car* truck = garage.getNewCar();
			Assert::IsNotNull(truck);
		}

		//tests roundabout with lots of cars
		TEST_METHOD(roundaboutLOTSOFCARS)
		{
			roundabout tester;
			tester.set_cars(1000, 2000, 3000, 4000, false);
			tester.run();
			if (tester.rate() < 10000)
				Assert::Fail();
		}

		//tests traffic light with lots of cars
		TEST_METHOD(trafficlightLOTSOFCARS)
		{
			trafficlight tester;
			tester.set_cars(1000, 2000, 3000, 4000, false);
			tester.run();
			if (tester.rate() < 10000)
				Assert::Fail();
		}
	};
}