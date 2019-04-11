#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Map
{
public:
	// Map constructor, intializes variables
	Map(int width, int height, string blank, string ship);
	Map() {}
	~Map();

	// Precondition: call after declaring map object
	void create_map();
	// Postcondition: will initialize the 2d vector

	// Precondition: call when attempting to view map
	void print_map();
	// Postcondition: will print map to console

	// Precondition: pass two integers by reference
	void convert_coord(int & r, int & c);
	// Postcondition: will convert integers to coordinates the 2d vector can use

	// Precondition: pass valid row and column coordinate, as well as a string character
	void set_point(int r, int c, string l);
	// Postcondition: will set that coordinate on the map equal to the string character

	// Precondition: pass row and column coordinate
	bool good_coord(int row, int col);
	// Postcondition: will return true if the coordinate is valid to use in the array

	// Getters that return the size of the map
	int get_width() { return m_width; }
	int get_height() { return m_height; }

	// Getter that returns the character at a specific location
	string get_coord(int row, int col);

	// Precondition: call once the ships have been intialized. Takes in two declared and intialized maps
	void print_two_maps(Map first, Map second);
	// Postcondition: will print both maps side by side, the first one being on the left

private:
	// 2d vector of strings, the map
	vector<vector<string>> m_map;

	// String to hold the blank character
	string m_blank_character;

	// String to hold the ship character
	string m_ship_character;

	// Integers storing map width and height
	int m_width;
	int m_height;
};

