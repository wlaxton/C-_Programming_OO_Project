/*	Author: Willard Laxton	*/

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

using namespace std;

// Game object variables
enum objects
{
	WHUMPUS = 2, ME, PIT, GOLD, BLANK
};

// Direction variables.
enum facing
{
	NORTH = 7, SOUTH, EAST, WEST, NONE_GOLD, NONE_WHUMPUS
};

class Game_Square
{
	private:
		string name;
		objects game_Object;
		facing direction;
	public:
		Game_Square();
		friend class World;
};

#endif /* GAMEOBJECT_H_ */
