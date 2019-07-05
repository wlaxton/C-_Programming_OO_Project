/*	Author: Willard Laxton	*/

#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include "GameObject.h"

using namespace std;

class World
{
	private:
		bool dead, won;
		string hero;
		Game_Square game_Board_Array[5][5];
	public:
		World(string);
		void set_Human_Location();
		void display_Board();
		void user_Action(int &, int &);
		void check_Game_Results();
		void place_Pit();
		void place_Whumpus();
		void place_Gold();
		bool get_Dead();
		bool get_Won();
};

#endif /* WORLD_H_ */
