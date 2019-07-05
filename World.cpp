/*	Author: Willard Laxton	*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

#include "GameObject.h"
#include "World.h"

using namespace std;

World::World(string name)
{
	int i, j;

	hero = name;
	dead = 0;
	won = 0;

// Initializes game board;
	for(i=0; i<5; i++)
		{
			for(j=0; j<5; j++)
			{
				game_Board_Array[i][j].name = "";
				game_Board_Array[i][j].game_Object = BLANK;
				game_Board_Array[i][j].direction = NORTH;
			}
		}
}

void World::set_Human_Location()
{
// Set hero's location.
	game_Board_Array[0][0].game_Object = ME;
	game_Board_Array[0][0].name = hero;
	game_Board_Array[0][0].direction = NORTH;
}

void World::display_Board()
{
	int i, j, h=0;

	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{

// Displays the hero and the direction they are facing.
			if(game_Board_Array[i][j].game_Object == ME)
			{
				if(game_Board_Array[i][j].direction == NORTH)
				{
					h++;
					cout << "|" << setw(8) << game_Board_Array[i][j].name << "(N)";
				}
				if(game_Board_Array[i][j].direction == SOUTH)
				{
					h++;
					cout << "|" << setw(8) << game_Board_Array[i][j].name << "(S)";
				}
				if(game_Board_Array[i][j].direction == EAST)
				{
					h++;
					cout << "|" << setw(8) << game_Board_Array[i][j].name << "(E)";
				}
				if(game_Board_Array[i][j].direction == WEST)
				{
					h++;
					cout << "|" << setw(8) << game_Board_Array[i][j].name << "(W)";
				}
			}

// This displays the stench attribute.
			else if(game_Board_Array[i+1][j].game_Object == WHUMPUS)
			{
				h++;
				cout << "|" << setw(7) << game_Board_Array[i][j].name << "{st}";
			}
			else if(game_Board_Array[i-1][j].game_Object == WHUMPUS)
			{
				h++;
				cout << "|" << setw(7) << game_Board_Array[i][j].name << "{st}";
			}
			else if(game_Board_Array[i][j+1].game_Object == WHUMPUS)
			{
				h++;
				cout << "|" << setw(7) << game_Board_Array[i][j].name << "{st}";
			}
			else if(game_Board_Array[i][j-1].game_Object == WHUMPUS)
			{
				h++;
				cout << "|" << setw(7) << game_Board_Array[i][j].name << "{st}";
			}

// This displays the breeze attribute.
			else if(game_Board_Array[i+1][j].game_Object == PIT)
			{
				h++;
				cout << "|" << setw(8) << game_Board_Array[i][j].name << "{b}";
			}
			else if(game_Board_Array[i-1][j].game_Object == PIT)
			{
				h++;
				cout << "|" << setw(8) << game_Board_Array[i][j].name << "{b}";
			}
			else if(game_Board_Array[i][j+1].game_Object == PIT)
			{
				h++;
				cout << "|" << setw(8) << game_Board_Array[i][j].name << "{b}";
			}
			else if(game_Board_Array[i][j-1].game_Object == PIT)
			{
				h++;
				cout << "|" << setw(8) << game_Board_Array[i][j].name << "{b}";
			}
			else
			{
				h++;
				cout << "|" << setw(11) << game_Board_Array[i][j].name;
			}

// Formating that displays the 5 x 5 array format.
			if(h%5 ==0)
			{
				cout << "|" << endl;
				cout << "-------------------------------------------------------------" << endl;
			}
		}
	}
}

void World::place_Pit()
{
	unsigned seed = time(0);
	srand(seed);

//Generates random number of pits.
	int number_Of_Pits, i, j, h;

	number_Of_Pits = rand()% 8 + 3 ;

	for(h=0; h<number_Of_Pits; h++)
	{
		i = rand() % 5;
		j = rand() % 5;

// Makes sure that the pit can't overwrite another object
		if(game_Board_Array[i][j].game_Object == BLANK)
		{
			game_Board_Array[i][j].name = "Pit";
			game_Board_Array[i][j].game_Object = PIT;
		}
	}
}

void World::place_Whumpus()
{
	unsigned seed = time(0);
	srand(seed);

	int i, j;

	i = rand() % 5;
	j = rand() % 5;

// Random generates a location for whumpus and makes sure it doesn't overwrite another object.
	while(game_Board_Array[i][j].game_Object != BLANK)
	{
		i = rand() % 5;
		j = rand() % 5;
	}

	game_Board_Array[i][j].name = "Whumpus";
	game_Board_Array[i][j].game_Object = WHUMPUS;
	game_Board_Array[i][j].direction = NONE_WHUMPUS;
}

void World::place_Gold()
{
	unsigned seed = time(0);
	srand(seed);

	int i, j;

	i = rand() % 5;
	j = rand() % 5;

// Generates a random location for the gold and makes sure it doesn't overwrite another object.
	while(game_Board_Array[i][j].game_Object != BLANK)
	{
		i = rand() % 5;
		j = rand() % 5;
	}

	game_Board_Array[i][j].name = "Gold";
	game_Board_Array[i][j].game_Object = GOLD;
	game_Board_Array[i][j].direction = NONE_GOLD;
}

void World::user_Action(int &i, int &j)
{
	char move, z, x;

// This is for attacking the Whumpus. It makes sure that you are near it and that you are facing it.
	if(game_Board_Array[i+1][j].game_Object == WHUMPUS && game_Board_Array[i][j].game_Object == ME &&
	game_Board_Array[i][j].direction == SOUTH)
	{
		cout << "You are near the Whumpus and you are facing him. Would you like to shoot him?(y/n)" << endl;
		cin.get(z);
		cin.ignore();

		if(z == 'y')
		{
			game_Board_Array[i+1][j].name = "";
			game_Board_Array[i+1][j].game_Object = BLANK;

			display_Board();
		}
	}

	if(game_Board_Array[i-1][j].game_Object == WHUMPUS && game_Board_Array[i][j].game_Object == ME &&
	game_Board_Array[i][j].direction == NORTH)
	{
		cout << "You are near the Whumpus and you are facing him. Would you like to shoot him?(y/n)" << endl;
		cin.get(z);
		cin.ignore();

		if(z == 'y')
		{
			game_Board_Array[i-1][j].name = "";
			game_Board_Array[i-1][j].game_Object = BLANK;

			display_Board();
		}
	}

	if(game_Board_Array[i][j+1].game_Object == WHUMPUS && game_Board_Array[i][j].game_Object == ME &&
	game_Board_Array[i][j].direction == EAST)
	{
		cout << "You are near the Whumpus and you are facing him. Would you like to shoot him?(y/n)" << endl;
		cin.get(z);
		cin.ignore();

		if(z == 'y')
		{
			game_Board_Array[i][j+1].name = "";
			game_Board_Array[i][j+1].game_Object = BLANK;

			display_Board();
		}
	}

	if(game_Board_Array[i][j-1].game_Object == WHUMPUS && game_Board_Array[i][j].game_Object == ME &&
	game_Board_Array[i][j].direction == WEST)
	{
		cout << "You are near the Whumpus and you are facing him. Would you like to shoot him?(y/n)" << endl;
		cin.get(z);
		cin.ignore();

		if(z == 'y')
		{
			game_Board_Array[i][j-1].name = "";
			game_Board_Array[i][j-1].game_Object = BLANK;

			display_Board();
		}
	}

	cout << "How would you like to move? Up, Down, Left or Right(U, D, L, R)" << endl;
	cout <<	"or you can change facing North, South, East, or West(N, S, E, W" << endl;
	cin.get(move);
	cin.ignore();

// Switch statement that moves the hero and erases the hero at the previous location.
	switch (move)
	{
		case 'u':
		case 'U':
			if(game_Board_Array[i][j].direction == NORTH)
			{
				game_Board_Array[i][j].name = "";
				game_Board_Array[i][j].game_Object = BLANK;
				game_Board_Array[i][j].direction = NORTH;

				i--;

// Win condition for finding the gold
				if(game_Board_Array[i][j].game_Object == GOLD)
				{
					cout << "You found the gold. Would you like to pick it up?(y/n)" << endl;
					cin.get(x);

					if(x == 'y')
					{
						won = 1;
					}

				}

// Lose condition if you run into the whumpus.
				if(game_Board_Array[i][j].game_Object == PIT || game_Board_Array[i][j].game_Object == WHUMPUS)
				{
					dead = 1;
				}

				game_Board_Array[i][j].name = hero;
				game_Board_Array[i][j].game_Object = ME;
				game_Board_Array[i][j].direction = NORTH;
			}
			break;

		case 'd':
		case 'D':
			if(game_Board_Array[i][j].direction == SOUTH)
			{
				game_Board_Array[i][j].name = "";
				game_Board_Array[i][j].game_Object = BLANK;
				game_Board_Array[i][j].direction = NORTH;

				i++;

// Win condition for gold.
				if(game_Board_Array[i][j].game_Object == GOLD)
				{
					cout << "You found the gold. Would you like to pick it up?(y/n)" << endl;
					cin.get(x);

					if(x == 'y')
					{
						won = 1;
					}
				}

// Lose condition for whumpus.
				if(game_Board_Array[i][j].game_Object == PIT || game_Board_Array[i][j].game_Object == WHUMPUS)
				{
					dead = 1;
				}

				game_Board_Array[i][j].name = hero;
				game_Board_Array[i][j].game_Object = ME;
				game_Board_Array[i][j].direction = SOUTH;
			}
			break;

		case 'r':
		case 'R':
			if(game_Board_Array[i][j].direction == EAST)
			{
				game_Board_Array[i][j].name = "";
				game_Board_Array[i][j].game_Object = BLANK;
				game_Board_Array[i][j].direction = NORTH;

				j++;

// Win condition for gold.
				if(game_Board_Array[i][j].game_Object == GOLD)
				{
					cout << "You found the gold. Would you like to pick it up?(y/n)" << endl;
					cin.get(x);

					if(x == 'y')
					{
						won = 1;
					}

				}

// Lose condition for whumpus.
				if(game_Board_Array[i][j].game_Object == PIT || game_Board_Array[i][j].game_Object == WHUMPUS)
				{
					dead = 1;
				}

				game_Board_Array[i][j].name = hero;
				game_Board_Array[i][j].game_Object = ME;
				game_Board_Array[i][j].direction = EAST;
			}
			break;

		case 'l':
		case 'L':
			if(game_Board_Array[i][j].direction == WEST)
			{
				game_Board_Array[i][j].name = "";
				game_Board_Array[i][j].game_Object = BLANK;
				game_Board_Array[i][j].direction = NORTH;

				j--;

// Wind condition for gold.
				if(game_Board_Array[i][j].game_Object == GOLD)
				{
					cout << "You found the gold. Would you like to pick it up?(y/n)" << endl;
					cin.get(x);

					if(x == 'y')
					{
						won = 1;
					}

				}

// Lose condition for Whumpus.
				if(game_Board_Array[i][j].game_Object == PIT || game_Board_Array[i][j].game_Object == WHUMPUS)
				{
					dead = 1;
				}

				game_Board_Array[i][j].name = hero;
				game_Board_Array[i][j].game_Object = ME;
				game_Board_Array[i][j].direction = WEST;
			}
			break;

// Code to change the direction.
			case 'n':
			case 'N':
				game_Board_Array[i][j].direction = NORTH;
				break;

			case 's':
			case 'S':
				game_Board_Array[i][j].direction = SOUTH;
				break;

			case 'e':
			case'E':
				game_Board_Array[i][j].direction = EAST;
				break;

			case 'w':
			case 'W':
				game_Board_Array[i][j].direction = WEST;
				break;

// Error message if a valid option isn't choosen.
			default:
				cout << "You have to be facing the direction you want to move. Change direction and then move." << endl;
				break;
		}
	}

void World::check_Game_Results()
{

// Checks to see if the hero has died.
	if(dead == 1)
	{
		cout << "You have died on the field of battle." << endl;
	}

// Checks to see if the hero has won.
	if(won == 1)
	{
		cout << "You have retrieved the gold. All of your friends are jealous." << endl;
	}
}

bool World::get_Dead()
{
// Access private member dead of class World
	return dead;
}

bool World::get_Won()
{
// Access private member won of class World
	return won;
}
