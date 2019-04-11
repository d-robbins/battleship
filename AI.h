#pragma once

#include <random>
#include <ctime>

#include "Map.h"
#include "Ship.h"

/*
	UP:

	row_coordinate - 1

	DOWN: 

	row_coordinate + 1

	LEFT: 

	col_coordinate - 1

	RIGHT

	col_coordinate + 1

*/

// Struct Node, holds all data of node
struct Node
{
	// Node has a point which will be the center of the node
	Point _node_center = Point(NULL, NULL);

	// Node has a integer to keep track of how far the ai is from the node
	int _distance_from_node = 0;

	// Node holds a boolean to determine whether the node exists, only one node
	bool _node_created = false;

	// Node holds a set of booleans which will change based on which directions have been checked
	bool _checked_up = false;
	bool _checked_down = false;
	bool _checked_left = false;
	bool _checked_right = false;
};

class AI
{
public:
	// AI constructors and destructors
	AI();
	~AI();

	// Precondition: pass two integers, height and width, along with two strings, blank character and ship character
	void initialize_map(int width, int heigh, string blank, string ship);
	// Postcondition: will initalize the computers map with the variables passed into the initialize_map function

	// Precondition: pass intialized vector of ships by reference
	void ai_turn(vector<Ship> & playerFleet);
	// Postcondition: will make the best next move for the ai based on previous hits and misses

	// Precondition: call function when ready to intialize the computers ships
	void create_fleet();
	// Postcondition: will create and push back 5 ships of different sizes with random locations and directions

	// Precondition: call to print the computers map
	void print_map();
	// Postcondition: will print the computers map to the consolse

	// Precondition: call when attempting to recieve the computers last move
	Point & get_last_move();
	// Postcondition: will return a reference Point of the computers last move

	// AI getter that returns all the AI's hits
	vector<Point> get_hits() { return _ai_hits; }

	// AI getter that returns all the AI's misses
	vector<Point> get_misses() { return _ai_misses; }

	// AI getter that returns a reference of the AI's fleet
	vector<Ship> & get_fleet() { return _ai_fleet; }

private:
	
	// Precondition: call if node is ready to be reset back to default values
	void reset_node();
	// Postcondition: all direction checks will be reset to false, distance from node will be set to zero, node created value will be set to false

	// Precondition: call when there is no smarter move for the ai to make
	void make_random_move(vector<Ship> & playerFleet);
	// Postcondition: will choose random coordinate and random direction and make its move

	// Precondition: pass two uninitialized variables to be set to random values
	void get_rcoord(int & row, int & col);
	// Postcondition: will recieve two values, that are neither previous hits or misses. Also in domain and range of map

	// Precondition: pass an initalized vector of ships, with two unintialized integers to recieve coordinates
	bool accidental_hit(vector<Ship> player_fleet, int & row, int & col);
	// Postcondition: will return true if there is a hit that is not part of a previously destroyed ship, integers will also be intialized

	// Precondition: pass a direction value (1, 2, 3, 4), with a valid coordinate row and col. check size will be how far you want to check in that direction
	bool good_dir(int dir, int row, int col, int check_size);
	// Postcondition: will return true if there is no previous hits, misses, or out of bounds places for the distance: check_size in the direction: dir

	// Precondition: pass a reference to a initalized playerFleet, two unintalized booleans, and 3 integers of the direction row and column of the move
	void make_move(vector<Ship> & playerFleet, bool & was_hit, bool & ship_destroyed, int direction, int row, int col);
	// Postcondition: makes move in specified direction, determines if it was a hit or if a ship was destroyed (returns those values)
	// if it was a hit set that point in the players fleet to destroyed

	// Object that will store the computers map
	Map _ai_map;

	// Strings to hold blank and ship strings
	string _ai_blank;
	string _ai_ship;

	// Vector to hold computers ships ie. fleet
	vector<Ship> _ai_fleet;

	// Object point to store the computers last move
	Point _ai_last_move = Point(NULL, NULL);

	// Node object that will hold a current nodes (if there is one) location, direction checks, etc.
	Node _current_node;

	// Vectors of points that hold the previous hits and misses of the computer
	vector<Point> _ai_hits;
	vector<Point> _ai_misses;

	// Integer that holds the intelligence level of the AI, unchangeable right now
	int _ai_intelligence_level;
};

