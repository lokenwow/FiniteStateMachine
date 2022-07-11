#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <random>

using namespace std;			// cout, endl
using namespace this_thread;	// sleep_for
using namespace chrono;			// seconds, milliseconds


namespace CHOICE {
	enum STATES { Watching = 0, Cheering, Booing, FoodStore, Eating };
}

//New current state
CHOICE::STATES current_state = CHOICE::Watching;

//Variables
int hunger = 50;

/*
* Function prototypes start
*/

void SwapState(CHOICE::STATES new_state);
bool isHungry();
void Watching();
void Cheering();
void Booing();
void Eating();
void FoodStore();
void SleepAndLoseHunger();

/*
* Function prototypes end
*/

int main()
{
	bool program_running = true;
	cout << "Starting Finite State Machine. Press ESC key to close." << endl;

	do {

		switch (current_state) {
		case CHOICE::Watching :
			Watching();
			break;
		case CHOICE::Cheering :
			Cheering();
			break;
		case CHOICE::Booing :
			Booing();
			break;
		case CHOICE::FoodStore :
			FoodStore();
			break;
		case CHOICE::Eating :
			Eating();
			break;
		}

		SleepAndLoseHunger();

		//Check for exit condition.
		if (_kbhit())
		{
			char input_char = _getch();

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}
		}

	} while (program_running);

	cout << "Ending Finite State Machine" << endl;

	return 0;
}

void SwapState(CHOICE::STATES new_state)
{
	//cout << "Current State is: " << current_state << endl;
	cout << "Switching State " << endl;
	current_state = new_state;
	//cout << "new State is: " << current_state << endl;
}

bool isHungry()
{
	if (hunger < 11) {
		return true;
	}
	return false;
}

void Watching()
{
	cout << "Im watching!" << endl;
	do {
		std::random_device rd;
		int rnum = rd() % 10;
		//cout << rnum << endl;


		if (rnum == 0) {
			cout << "We Scored!" << endl;
			SwapState(CHOICE::Cheering);
			break;
		}
		else if (rnum == 9) {
			cout << "They Scored!" << endl;
			SwapState(CHOICE::Booing);
			break;
		}

		SleepAndLoseHunger();

	} while (!isHungry());
	
	if (isHungry()) {
		SwapState(CHOICE::FoodStore);
	}
}

void Cheering()
{
	int count = 1;
	//Cheer for 15 seconds and then go back to watching
	cout << "I'm Cheering for 15 seconds!" << endl;
	do {
		if (count < 15) {
			count = count + 1;
			SleepAndLoseHunger();
		}
		else if (count >= 15) {
			SwapState(CHOICE::Watching);
			break;
		}

	} while (!isHungry());

	if (isHungry()) {
		SwapState(CHOICE::FoodStore);
	}
}

void Booing()
{
	int count = 1;
	//boo for 15 seconds and then go back to watching
	cout << "I'm booing for 15 seconds!" << endl;
	do {
		if (count < 15) {
			count = count + 1;
			SleepAndLoseHunger();
		}
		else if (count >= 15) {
			SwapState(CHOICE::Watching);
			break;
		}

	} while (!isHungry());

	if (isHungry()) {
	SwapState(CHOICE::FoodStore);
	}
}

void Eating()
{
	//reset hunger to 50 then go back to watching
	hunger = 50;
	cout << "I'm eating for 5 seconds!" << endl;
	sleep_for(milliseconds(5000));
	SwapState(CHOICE::Watching);
}

void FoodStore()
{
	//move to eating
	cout << "Im hungry and going to the store!" << endl;
	SwapState(CHOICE::Eating);
}

//Sleeps for half a second and drops hunger level by 1
void SleepAndLoseHunger()
{
	hunger = hunger-1;
	sleep_for(milliseconds(1000));
	//cout << "Current Hunger Level is: " << hunger << endl;

}

