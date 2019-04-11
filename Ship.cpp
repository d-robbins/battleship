#include "Ship.h"


Ship::Ship(string name, int size)
{
	// Intialize variables
	_name = name;
	_size = size;
}

Ship::~Ship()
{
}

vector<Point> Ship::get_possible_endpoints(Map map, int size, int row, int col, string blank)
{
	// Create a vector of points which will be returned
	vector<Point> result;

	// Check the up direction
	if (good_direction(map, DIRECTION::UP, row, col, size, blank))
	{
		// Push back a point at the end coordinate 
		result.push_back(Point(row - size, col));

		// Set the last unit on the vector to direction UP
		result.back()._direction = DIRECTION::UP;
	}

	// Check down direction
	if (good_direction(map, DIRECTION::DOWN, row, col, size, blank))
	{
		result.push_back(Point(row + size, col));
		result.back()._direction = DIRECTION::DOWN;
	}

	// Check left direction
	if (good_direction(map, DIRECTION::LEFT, row, col, size, blank))
	{
		result.push_back(Point(row, col - size));
		result.back()._direction = DIRECTION::LEFT;
	}

	// Check right direction
	if (good_direction(map, DIRECTION::RIGHT, row, col, size, blank))
	{
		result.push_back(Point(row, col + size));
		result.back()._direction = DIRECTION::RIGHT;
	}

	return result;
}

void Ship::add_coord(int row, int col)
{
	// Adds another point to the vector of points at passed coordinate
	_ship.push_back(Point(row, col));
}

void Ship::print_coords()
{
	// Loops through all the coordinates and prints them
	for (int i = 0; i < _ship.size(); i++)
	{
		cout << "ROW: " << (char)(_ship[i]._row + 65) << " COL: " << _ship[i]._col + 1 << endl;
	}
}

void Ship::set_ship(Map & map, string ship_character)
{
	// Loops through all the coordinates and places them in the map
	for (int i = 0; i < _ship.size(); i++)
	{
		map.set_point(_ship[i]._row, _ship[i]._col, ship_character);
	}

	return;
}

void Ship::point_destroyed(int row, int col)
{
	// Sets the point boolean destroyed to true if its a part of the ship
	for (int i = 0; i < _ship.size(); i++)
	{
		if ((row == _ship[i]._row) && (col == _ship[i]._col))
		{
			_ship[i]._destroyed = true;
			break;
		}
	}

	return;
}

bool Ship::is_destroyed()
{
	bool result;

	// Loops through all coordinates in the ship, if all booleans are true, the ship is destroyed
	for (int i = 0; i < _ship.size(); i++)
	{
		if (_ship[i]._destroyed)
		{
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}

	return result;
}

bool Ship::part_of_ship(int row, int col)
{
	bool result = false;

	// Loops through all coordinates in the ship, if the coordinate passed is one of the ships, return true
	for (int i = 0; i < _ship.size(); i++)
	{
		if ((row == _ship[i]._row) && (col == _ship[i]._col))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool Ship::good_direction(Map map, int direction, int row, int col, int size, string blank)
{
	bool result = false;

	// If the ship can be places in the direction specified, return true

	switch (direction)
	{
	case DIRECTION::UP:
		
		// Determine if out of bounds
		if ((row - size) >= 0)
		{
			for (int i = 0; i <= size; i++)
			{
				if (map.get_coord(row - (i), col) == blank)
				{
					result = true;
				}
				else
				{
					result = false;
					break;
				}
			}
		}
		break;
	case DIRECTION::DOWN:
		if ((row + size) < (map.get_height()))
		{
			for (int i = 0; i <= size; i++)
			{
				if (map.get_coord(row + (i), col) == blank)
				{
					result = true;
				}
				else
				{
					result = false;
					break;
				}
			}
		}
		break;
	case DIRECTION::LEFT:
		if ((col - size) >= 0)
		{
			for (int i = 0; i <= size; i++)
			{
				if (map.get_coord(row, col - i) == blank)
				{
					result = true;
				}
				else
				{
					result = false;
					break;
				}
			}
		}
		break;
	case DIRECTION::RIGHT:
		if ((col + size) < (map.get_width()))
		{
			for (int i = 0; i <= size; i++)
			{
				if (map.get_coord(row, col + i) == blank)
				{
					result = true;
				}
				else
				{
					result = false;
					break;
				}
			}
		}
		break;
	default:
		cout << "ERROR: BAD DIRECTION; good_direction() {}\n";
		_getch();
		break;
	}


	return result;
}

string Point::get_direction_name(int dir)
{
	string result;

	// Returns string name of direction based on passed value

	switch (dir)
	{
	case 1:
		result = "Up";
		break;
	case 2:
		result = "Down";
		break;
	case 3:
		result = "Left";
		break;
	case 4:
		result = "Right";
		break;
	default:
		result = "INVALID DIRECTION\n";
		break;
	}

	return result;
}
