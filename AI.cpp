#include "AI.h"

AI::AI()
{
	// Seed the random function
	srand(time(NULL));

	// Set the intelligence level to 1 (TODO: implement smarter AI)
	_ai_intelligence_level = 1;
}

AI::~AI()
{
}

void AI::print_map()
{
	// Print the computers map
	_ai_map.print_map();
}

Point & AI::get_last_move()
{
	// Return a reference to the last move made by the computer
	return _ai_last_move;
}

void AI::get_rcoord(int & row, int & col)
{
	// Create temporary flag boolean
	bool good_coord;

	do
	{
		// Initialize boolean to true
		good_coord = true;

		// Intialize parameters to random numbers in the domain and range of the map
		row = (rand() % _ai_map.get_height());
		col = (rand() % _ai_map.get_width());

		// Check to see that random coords are not previous misses
		for (int i = 0; i < _ai_misses.size(); i++)
		{
			if ((row == _ai_misses[i]._row) && (col == _ai_misses[i]._col))
			{
				// If it was a previous miss, set the flag to false and break
				good_coord = false;
				break;
			}
		}

		// Check to see that random coords are not previous hits
		for (int i = 0; i < _ai_hits.size(); i++)
		{
			if ((row == _ai_hits[i]._row) && (col == _ai_hits[i]._col))
			{
				// If it was a previous hit, set the flag to false and break
				good_coord = false;
				break;
			}
		}

	// Continue while flag is false
	} while (!good_coord);

	return;
}

bool AI::accidental_hit(vector<Ship> player_fleet, int & row, int & col)
{
	// Create variable that will be returned, set it to false
	bool create_another_node = false;

	// Loop through all the hits made
	for (int i = 0; i < _ai_hits.size(); i++)
	{
		// Loop through all of the players ships
		for (int j = 0; j < player_fleet.size(); j++)
		{
			// If a hit is part of a ship
			if (player_fleet[j].part_of_ship(_ai_hits[i]._row, _ai_hits[i]._col))
			{
				// If the ship is not destroyed
				if (!player_fleet[j].is_destroyed())
				{
					// Create a new node
					create_another_node = true;
							
					// Intialize reference parameters
					row = _ai_hits[i]._row;
					col = _ai_hits[i]._col;

					break;
				}
				else
				{
					// Do not create another node
					create_another_node = false;
				}
			}
		}
		// If a new node needs to be created, break
		if (create_another_node)
			break;
	}

	// Return variable
	return create_another_node;
}

bool AI::good_dir(int dir, int row, int col, int check_size)
{
	// Intialize variable that will be returned to true
	bool result = true;

	switch (dir)
	{
	case DIRECTION::UP:

		// If direction is up, check to make sure the space above is not out of the map
		if ((row - check_size) < 0)
		{
			result = false;
		}
		else
		{
			// Check to make sure the space above is not a previous miss
			for (int i = 0; i < _ai_misses.size(); i++)
			{
				if ((row - check_size) == _ai_misses[i]._row && col == _ai_misses[i]._col)
				{
					result = false;
					break;
				}
			}

			// Check to make sure the space above is not a previous hit
			for (int i = 0; i < _ai_hits.size(); i++)
			{
				if ((row - check_size) == _ai_hits[i]._row && col == _ai_hits[i]._col)
				{
					result = false;
					break;
				}
			}
		}

		break;
	case DIRECTION::DOWN:

		// If the direction is down, check to make sure the space below is not out of the map
		if ((row + check_size) > (_ai_map.get_height() - 1))
		{
			result = false;
		}
		else
		{
			// Check to make sure the space above is not a previous miss
			for (int i = 0; i < _ai_misses.size(); i++)
			{
				if ((row + check_size) == _ai_misses[i]._row && col == _ai_misses[i]._col)
				{
					result = false;
					break;
				}
			}

			// Check to make sure the space above is not a previous hit
			for (int i = 0; i < _ai_hits.size(); i++)
			{
				if ((row + check_size) == _ai_hits[i]._row && col == _ai_hits[i]._col)
				{
					result = false;
					break;
				}
			}
		}

		break;
	case DIRECTION::LEFT:

		// If the direction is left, check to make sure the space to the left is not out of the map
		if ((col - check_size) < 0)
		{
			result = false;
		}
		else
		{
			// Check to make sure the space above is not a previous miss
			for (int i = 0; i < _ai_misses.size(); i++)
			{
				if (row == _ai_misses[i]._row && (col - check_size) == _ai_misses[i]._col)
				{
					result = false;
					break;
				}
			}

			// Check to make sure the space above is not a previous hit
			for (int i = 0; i < _ai_hits.size(); i++)
			{
				if (row == _ai_hits[i]._row && (col - check_size) == _ai_hits[i]._col)
				{
					result = false;
					break;
				}
			}
		}

		break;
	case DIRECTION::RIGHT:
		
		// If the direction is right, check to make sure that the space to the right is not out of the map
		if ((col + check_size) > (_ai_map.get_width() - 1))
		{
			result = false;
		}
		else
		{
			// Check to make sure the space above is not a previous miss
			for (int i = 0; i < _ai_misses.size(); i++)
			{
				if (row == _ai_misses[i]._row && (col + check_size) == _ai_misses[i]._col)
				{
					result = false;
					break;
				}
			}

			// Check to make sure the space above is not a previous hit
			for (int i = 0; i < _ai_hits.size(); i++)
			{
				if (row == _ai_hits[i]._row && (col + check_size) == _ai_hits[i]._col)
				{
					result = false;
					break;
				}
			}
		}

		break;
	default:
		break;
	}

	// Return the result
	return result;
}

void AI::initialize_map(int width, int heigh, string blank, string ship)
{
	// Call the map constructor with parameters passed to the function
	_ai_map = Map(width, heigh, blank, ship);

	// Call create map function
	_ai_map.create_map();

	// Set the string variables
	_ai_blank = blank;
	_ai_ship = ship;

	return;
}

void AI::ai_turn(vector<Ship>& playerFleet)
{
	// Booleans to determine hits, destroys and whether or not a move has been made
	bool hit = false;
	bool destroyed_ship = false;
	bool made_move = false;

	// If there is no current node, make a random move
	if (!_current_node._node_created)
	{
		make_random_move(playerFleet);
	}
	else
	{
		// Intialize two integers, incase there is going to be a next set move
		int next_row;
		int next_col;

		// COMMENTS FOR THE UP DIRECTION CHECK ARE SAME AS DOWN, LEFT, RIGHT

		do 
		{
			// Determine if up direction has been checked
			if (!_current_node._checked_up)
			{
				// Determine if a move in the up direction is valid
				if (good_dir(DIRECTION::UP, _current_node._node_center._row - _current_node._distance_from_node, _current_node._node_center._col, _ai_intelligence_level))
				{
					// Make the move
					make_move(playerFleet, hit, destroyed_ship, DIRECTION::UP, _current_node._node_center._row - _current_node._distance_from_node, _current_node._node_center._col);

					// Increase the distance from the node
					_current_node._distance_from_node += 1;

					// Set the last move
					_ai_last_move._row = _current_node._node_center._row - _current_node._distance_from_node;
					_ai_last_move._col = _current_node._node_center._col;

					// A move has been made
					made_move = true;

					if (hit)
					{
						// If it was a hit, the last move was a hit
						_ai_last_move._destroyed = true;

						// Was a ship destroyed?
						if (destroyed_ship)
						{
							// If a ship was destroyed, reset the node
							reset_node();

							// If there is a hit that is not part of the destroyed ship
							if (accidental_hit(playerFleet, next_row, next_col))
							{
								// Create a new node at the accidental hit
								_current_node._node_created = true;
								_current_node._node_center._row = next_row;
								_current_node._node_center._col = next_col;

								_current_node._distance_from_node = 0;

							}
						}
					}
					else
					{
						// If it was not a hit, the up direction has been checked and the last move was not a hit
						_current_node._checked_up = true;
						_current_node._distance_from_node = 0;
						_ai_last_move._destroyed = false;
					}
				}
				else
				{
					// If a move in the up direction is not valid, the up direction has been checked, reset the distance to 0
					_current_node._checked_up = true;
					_current_node._distance_from_node = 0;
				}
			}
			else if (!_current_node._checked_down)
			{
				if (good_dir(DIRECTION::DOWN, _current_node._node_center._row + _current_node._distance_from_node, _current_node._node_center._col, _ai_intelligence_level))
				{
					make_move(playerFleet, hit, destroyed_ship, DIRECTION::DOWN, _current_node._node_center._row + _current_node._distance_from_node, _current_node._node_center._col);
					
					_current_node._distance_from_node += 1;
				
					_ai_last_move._row = _current_node._node_center._row + _current_node._distance_from_node;
					_ai_last_move._col = _current_node._node_center._col;

					made_move = true;

					if (hit)
					{
						_ai_last_move._destroyed = true;

						if (destroyed_ship)
						{
							reset_node();

							if (accidental_hit(playerFleet, next_row, next_col))
							{
								_current_node._node_created = true;
								_current_node._node_center._row = next_row;
								_current_node._node_center._col = next_col;

								_current_node._distance_from_node = 0;
							}
						}

					}
					else
					{
						_current_node._checked_down = true;
						_current_node._distance_from_node = 0;
						_ai_last_move._destroyed = false;
					}
				}
				else
				{
					_current_node._checked_down = true;
					_current_node._distance_from_node = 0;
				}
			}
			else if (!_current_node._checked_left)
			{
				if (good_dir(DIRECTION::LEFT, _current_node._node_center._row, _current_node._node_center._col - _current_node._distance_from_node, _ai_intelligence_level))
				{
					make_move(playerFleet, hit, destroyed_ship, DIRECTION::LEFT, _current_node._node_center._row, _current_node._node_center._col - _current_node._distance_from_node);

					_current_node._distance_from_node += 1;

					made_move = true;

					_ai_last_move._row = _current_node._node_center._row;
					_ai_last_move._col = _current_node._node_center._col - _current_node._distance_from_node;

					if (hit)
					{
						_ai_last_move._destroyed = true;

						if (destroyed_ship)
						{
							reset_node();

							if (accidental_hit(playerFleet, next_row, next_col))
							{
								_current_node._node_created = true;
								_current_node._node_center._row = next_row;
								_current_node._node_center._col = next_col;

								_current_node._distance_from_node = 1;

							}
						}
					}
					else
					{
						_current_node._checked_left = true;
						_current_node._distance_from_node = 0;
						_ai_last_move._destroyed = false;
					}
				}
				else
				{
					_current_node._checked_left = true;
					_current_node._distance_from_node = 0;
				}
			}
			else if (!_current_node._checked_right)
			{
				if (good_dir(DIRECTION::RIGHT, _current_node._node_center._row, _current_node._node_center._col + _current_node._distance_from_node, _ai_intelligence_level))
				{
					make_move(playerFleet, hit, destroyed_ship, DIRECTION::RIGHT, _current_node._node_center._row, _current_node._node_center._col + _current_node._distance_from_node);

					_current_node._distance_from_node += 1;

					made_move = true;

					_ai_last_move._row = _current_node._node_center._row;
					_ai_last_move._col = _current_node._node_center._col + _current_node._distance_from_node;

					if (hit)
					{
						_ai_last_move._destroyed = true;

						if (destroyed_ship)
						{
							reset_node();

							if (accidental_hit(playerFleet, next_row, next_col))
							{
								_current_node._node_created = true;
								_current_node._node_center._row = next_row;
								_current_node._node_center._col = next_col;

								_current_node._distance_from_node = 1;

							}
						}
					}
					else
					{
						_current_node._checked_right = true;
						_current_node._distance_from_node = 0;
						_ai_last_move._destroyed = false;
					}


				}
				else
				{
					_current_node._checked_right = true;
					_current_node._distance_from_node = 0;
				}
			}
		} while (!made_move);
	} 

	return;
}

void AI::reset_node()
{
	// Set all node variables back to default values
	_current_node._node_created = false;
	_current_node._checked_up = false;
	_current_node._checked_down = false;
	_current_node._checked_left = false;
	_current_node._checked_up = false;
	_current_node._distance_from_node = 0;
}

void AI::make_random_move(vector<Ship>& playerFleet)
{
	// Create variables to hold row and column variables
	int row, col;

	// Create booleans to pass to move function
	bool hit, destroy;

	// Get a good random coordinate
	get_rcoord(row, col);

	// Set the last move point to the new coordinates
	_ai_last_move._col = col;
	_ai_last_move._row = row;

	// Make the move
	make_move(playerFleet, hit, destroy, DIRECTION::RANDOM, row, col);

	// If the move was a hit
	if (hit)
	{
		// Destroy the point
		_ai_last_move._destroyed = true;
	}
	else
	{
		// Last point was a miss
		_ai_last_move._destroyed = false;
	}
}

void AI::make_move(vector<Ship>& playerFleet, bool & was_hit, bool & ship_destroyed, int direction, int row, int col)
{
	// Set the reference parameter equal to false
	was_hit = false;

	// Boolean to hold whether a ship was destroyed or not, set to false
	bool destroyed_ship = false;

	// Switch based on direction
	switch (direction)
	{
	case DIRECTION::RANDOM:
		
		// Loop through the players fleet
		for (int i = 0; i < playerFleet.size(); i++)
		{

			// If the coordinate is a part of one of the players fleet
			if (playerFleet[i].part_of_ship(row, col))
			{
				// Push back a new hit coordinate to the hit vector
				_ai_hits.push_back(Point(row, col));

				// Set the point in the players fleet to destroyed
				playerFleet[i].point_destroyed(row, col);

				// Create a new node at that point
				_current_node._node_center = Point(row, col);
				_current_node._node_created = true;

				// Hit parameter is equal to true
				was_hit = true;
			}
		}

		if (!was_hit)
		{
			// If it wasnt a hit push back a new miss point to the miss vector
			_ai_misses.push_back(Point(row, col));
		}

		break;
	case DIRECTION::UP:
		
		// Same as random direction
		for (int i = 0; i < playerFleet.size(); i++)
		{
			if (playerFleet[i].part_of_ship(row - 1, col))
			{
				_ai_hits.push_back(Point(row - 1, col));
				playerFleet[i].point_destroyed(row - 1, col);
				was_hit = true;

				// Determine if hit destroyed the players ship
				if (playerFleet[i].is_destroyed())
				{
					// Set the reference parameter that tells the program if a ship was destroyed to true
					ship_destroyed = true;
				}
			}
		}

		if (!was_hit)
		{
			// Same as random direction functionality
			_ai_misses.push_back(Point(row - 1, col));
		}

		break;
	case DIRECTION::DOWN:

//		FOLLOWING CODE IN FUNCTION IS EXACTLY THE SAME AS PREVIOUS SWITCH CASE (UP), JUST DIFFERENT DIRECTION

		for (int i = 0; i < playerFleet.size(); i++)
		{
			if (playerFleet[i].part_of_ship(row + 1, col))
			{
				_ai_hits.push_back(Point(row + 1, col));
				playerFleet[i].point_destroyed(row + 1, col);
				was_hit = true;

				if (playerFleet[i].is_destroyed())
				{
					ship_destroyed = true;
				}
			}
		}

		if (!was_hit)
		{
			_ai_misses.push_back(Point(row + 1, col));
		}

		break;
	case DIRECTION::LEFT:
		for (int i = 0; i < playerFleet.size(); i++)
		{
			if (playerFleet[i].part_of_ship(row, col - 1))
			{
				_ai_hits.push_back(Point(row, col - 1));
				playerFleet[i].point_destroyed(row, col - 1);
				was_hit = true;

				if (playerFleet[i].is_destroyed())
				{
					ship_destroyed = true;
				}
			}
		}

		if (!was_hit)
		{
			_ai_misses.push_back(Point(row, col - 1));
		}

		break;
	case DIRECTION::RIGHT:
		for (int i = 0; i < playerFleet.size(); i++)
		{
			if (playerFleet[i].part_of_ship(row, col + 1))
			{
				_ai_hits.push_back(Point(row, col + 1));
				playerFleet[i].point_destroyed(row, col + 1);
				was_hit = true;

				if (playerFleet[i].is_destroyed())
				{
					ship_destroyed = true;
				}
			}
		}

		if (!was_hit)
		{
			_ai_misses.push_back(Point(row, col + 1));
		}

		break;
	default:
		break;
	}
}

void AI::create_fleet()
{
	cout << "[AI]: CREATING AND PLACING SHIPS\n\n";

	// Intialize ships
	Ship _one = Ship("Destroyer 1", 2);
	Ship _two = Ship("Destroyer 2", 2);
	Ship _three = Ship("Cruiser", 3);
	Ship _four = Ship("Battleship", 4);
	Ship _five = Ship("Aircraft Carrier", 5);

	// Push ships back onto vector
	_ai_fleet.push_back(_one);
	_ai_fleet.push_back(_two);
	_ai_fleet.push_back(_three);
	_ai_fleet.push_back(_four);
	_ai_fleet.push_back(_five);

	// Create integers to hold where the ships beginning will be
	int start_row, start_col;

	// Boolean to determine if choice is a good direction
	bool good_location;

	// Integer to hold a random direction
	int rand_direction;

	// Create all ships
	for (int i = 0; i < _ai_fleet.size(); i++)
	{
		// Intialize good_location to false
		good_location = false;

		do
		{
			// Get a random coordinate
			get_rcoord(start_row, start_col);

			// Get a random direction
			rand_direction = (rand() % 4) + 1;

			// Determine if that direction at that coordinate is a valid move
			if (_ai_fleet[i].good_direction(_ai_map, rand_direction, start_row, start_col, _ai_fleet[i].get_size(), _ai_blank))
			{
				// If so, add (ship size)x coordinates in that direction
				switch (rand_direction)
				{
				case 1:
					for (int j = 0; j < _ai_fleet[i].get_size(); j++)
					{
						_ai_fleet[i].add_coord(start_row - j, start_col);
					}
					break;
				case 2:
					for (int j = 0; j < _ai_fleet[i].get_size(); j++)
					{
						_ai_fleet[i].add_coord(start_row + j, start_col);
					}
					break;
				case 3:
					for (int j = 0; j < _ai_fleet[i].get_size(); j++)
					{
						_ai_fleet[i].add_coord(start_row, start_col - j);
					}
					break;
				case 4:
					for (int j = 0; j < _ai_fleet[i].get_size(); j++)
					{
						_ai_fleet[i].add_coord(start_row, start_col + j);
					}
					break;
				default:
					break;
				}

				// Set good location to true
				good_location = true;

				// Set the ship in the map
				_ai_fleet[i].set_ship(_ai_map, _ai_ship);
			}

		// Continue while location is invalid
		} while (!good_location);
	}
}
