#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "Map.h"

using namespace std;

/*
1: UP
2: DOWN
3: LEFT
4: RIGHT
*/

// Enum to hold direction values
enum DIRECTION { RANDOM, UP, DOWN, LEFT, RIGHT, NONE };

// Struct point which will serve as a coordinate
struct Point
{
	// Constructor to intialize the row and column values
	Point(int r, int c) { _row = r; _col = c; }

	// Returns direction name based on what direction the user passes
	string get_direction_name(int dir);

	// Struct data, including a coordinate, direction, and boolean to determine whether the point is destroyed or not
	int _row, _col;
	DIRECTION _direction;
	bool _destroyed = false;
};

class Ship
{
public:
	// Constructor to intialize name and size
	Ship(string name, int size);
	~Ship();

	// Setter that allows the user to change name of ship
	void set_name(string name) { _name = name; }

	// Precondition: pass intialized map, a size to check, a coordinate and a blank character for computation
	vector<Point> get_possible_endpoints(Map map, int size, int row, int col, string blank);
	// Postcondition: will return VALID endpoints of the coordinate pass of the size passed

	// Getter to recieve the ships name
	string get_name() { return _name; }

	// Precondition: pass valid row and column coordinate
	void add_coord(int row, int col);
	// Postcondition: will add that coordinate to the ships array of coordinates

	// Print the coordiantes of the ship, for debugging
	void print_coords();

	// Precondition: requires ship to be intialized and containing a set of coordinates
	void set_ship(Map & map, string ship_character);
	// Postcondition: will place the ship in the map which is passed. Once map is printed, ship will be visible

	// Will set the coordinate specified to destroyed
	void point_destroyed(int row, int col);

	// Getter to recieve the size of the ship
	int get_size() { return _size; }

	// Will return true if all points in the ships array are destroyed
	bool is_destroyed();

	// Precondition: pass valid row and column coordinate
	bool part_of_ship(int row, int col);
	// Postcondition: will return true if the coordinate passed is part of the ship

	// Precondition: pass intialized map, a direction, a coordinate, size to check, and the blank character
	bool good_direction(Map map, int direction, int row, int col, int size, string blank);
	// Postcondition: will return true if the ship can be placed in such direction

private:

	// Vector of points, the ships coordinates
	vector<Point> _ship;

	// String to hold the name of the ship
	string _name;

	// Integer to hold the size of the ship
	int _size;
};

