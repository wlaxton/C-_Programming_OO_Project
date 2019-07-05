/*	Author: Willard Laxton	*/

#include <iostream>
#include <string>

#include "GameObject.h"
#include "World.h"

using namespace std;

int main()
{
	int i = 0, j = 0;
	string name;
	bool x, y;

	cout << "What is the name of your hero?" << endl;
	getline(cin, name);

// Places all the game objects on the board and displays it.
	World whumpus_World(name);
	whumpus_World.set_Human_Location();
	whumpus_World.place_Pit();
	whumpus_World.place_Whumpus();
	whumpus_World.place_Gold();
	whumpus_World.display_Board();

// Used for condition in the while loop.
	x = whumpus_World.get_Dead();
	y = whumpus_World.get_Won();

// Plays the game until either you win or die.
	while(x == 0 && y == 0)
	{
		whumpus_World.user_Action(i, j);
		whumpus_World.display_Board();
		x = whumpus_World.get_Dead();
		y = whumpus_World.get_Won();
		whumpus_World.check_Game_Results();
	}

return 0;
}

