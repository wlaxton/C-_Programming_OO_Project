/*	Author: Willard Laxton	*/

#include <iostream>

#include "GameObject.h"
#include "World.h"

using namespace std;

Game_Square::Game_Square()
{
// Creates objects for the 2d array.
	name = "";
	game_Object = BLANK;
	direction = NORTH;
}
