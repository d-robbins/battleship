#include "Map.h"



Map::Map(int width, int height, string blank, string ship)
{
	// Intializes variables
	m_width = width;
	m_height = height;
	m_blank_character = blank;
	m_ship_character = ship;
}

Map::~Map()
{
}

void Map::create_map()
{
	// Loops through the rows
	for (int i = 0; i < m_height; i++)
	{
		// Creates temporary vector of strings
		vector<string> line;
		
		// loops through the width of the map
		for (int j = 0; j < m_width; j++)
		{
			// adds a blank character to the line
			line.push_back(m_blank_character);
		}

		// adds the line to the row
		m_map.push_back(line);
	}

	return;
}

void Map::print_map()
{
	// Formats the numbers across the top
	for (int i = 0; i < m_width; i++)
	{
		if (i == 0)
		{
			cout << "    " << i + 1;
		}
		else if ((i + 1) > 9)
		{
			cout << "  " << i + 1;
		}
		else
		{
			cout << "   " << i + 1;
		}
	}

	cout << endl;


	// Formats the letters down the side and the characters between each coordinate
	for (int i = 0; i < m_map.size(); i++)
	{
		cout << (char)(i + 65) << " | ";
		for (int j = 0; j < m_map[i].size(); j++)
		{
			cout << m_map[i][j] << " | ";
		}
		cout << endl;
		for (int i = -1; i < m_width; i++)
		{
			cout << "----";
		}
		cout << endl;
	}

	return;
}

void Map::convert_coord(int & r, int & c)
{
	// Subtracts 65 from the integer, ASCII table
	r = r - 65;
	// Subtracts 1 from the column. 2d arrays start at 0,0
	c -= 1;
	return;
}

void Map::set_point(int r, int c, string l)
{
	// Sets the point on the map equal to the string
	m_map[r][c] = l;

	return;
}

bool Map::good_coord(int row, int col)
{
	bool result = false;

	// Checks to see if the coordinate is out of bounds
	if ((row >= 0) && (row <= (m_height - 1)))
	{
		result = true;
	}

	if ((col >= 0) && (col <= (m_width - 1)))
	{
		result = true;
	}

	return result;
}

string Map::get_coord(int row, int col)
{
	// Returns the string value at the coordinate
	return m_map[row][col];
}

void Map::print_two_maps(Map first, Map second)
{
	// Formats both maps to print side by side

	for (int i = 0; i < (int)(first.get_width() / 2); i++)
	{
		cout << "   ";
	}

	cout << "HITS\MISSES BOARD";

	for (int i = 0; i < first.get_width(); i++)
	{
		cout << "   ";
	}

	cout << "SHIPS BOARD\n";

	for (int i = 0; i < second.get_width(); i++)
	{
		if (i == 0)
		{
			cout << "    " << i + 1;
		}
		else if ((i + 1) > 9)
		{
			cout << "  " << i + 1;
		}
		else
		{
			cout << "   " << i + 1;
		}
	}

	for (int i = 0; i < first.get_width(); i++)
	{
		if (i == 0)
		{
			cout << "          " << i + 1;
		}
		else if ((i + 1) > 9)
		{
			cout << "  " << i + 1;
		}
		else
		{
			cout << "   " << i + 1;
		}
	}


	cout << endl;

	for (int i = 0; i < first.get_height(); i++)
	{
		cout << (char)(i + 65) << " | ";
		for (int j = 0; j < first.get_width(); j++)
		{
			cout << first.get_coord(i, j) << " | ";
		}

		cout << "   " << (char)(i + 65) << " | ";
		for (int j = 0; j < second.get_width(); j++)
		{
			cout << second.get_coord(i, j) << " | ";
		}

		cout << endl;
		for (int i = -1; i < second.get_width(); i++)
		{
			cout << "----";
		}

		for (int i = -1; i < second.get_width(); i++)
		{
			cout << "----";
		}

		cout << "--";

		cout << endl;
	}

	return;
}
