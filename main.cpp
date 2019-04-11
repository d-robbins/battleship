#include <iostream>
#include <fstream>
#include <conio.h>
#include <cctype>

#include "Map.h"
#include "Ship.h"
#include "AI.h"

using namespace std;

// Constants to hold simple game data
const int HEIGHT = 10;
const int WIDTH = 10;
const string BLANK = " ";
const string SHIP = "+";

// Precondition: call from empty vector of ships
vector<Ship> intialize_fleet();
// Postcondition: will return a vector of 5 ships, of predetermined size

// Precondition: call to load in strings from a file: file_name
vector<string> load_file(string file_name);
// Postcondition: will return a vector of strings of the file contents

// Precondition: pass 2 empty integers by reference, and an intialized map.
void get_coordinate_input(int & row, int & col, Map _map);
// Postcondition: Will prompt and return a coordinate that has been validated

// Precondition: pass a intialized map and an intialized vector of ships
void create_fleet(Map & map, vector<Ship> & fleet);
// Postcondition: will return a vector of ships that hold valid coordinates

// Precondition: pass intialized and set vector of ships as well as a intialized and created map
void player_turn(vector<Ship> & ai_fleet, Map & hits_map);
// Postcondition: will prompt the user for his coordinate choice, determine hit or miss, and manipulate the map

// Precondition: call when attempting to clear console
void clear_screen();
// Postcondition: will print 20 new lines, 'clearing' the screen

// Precondition: pass intialized vector of ships, map holding hits and misses, map which holds ships, and two vectors of strings holding positive and negative statements
void update_map(vector<Ship> playerFleet, Map hits_map, Map & player_map, AI aiPlayer, vector<string> pos_statements, vector<string> neg_statements);
// Postcondition: will update the players hits/misses map aswell as the ship map with the AI's last move. Will also game output

// Precondition: pass two intialized vector of ships, one being the players and the other the computers, as well as two reference booleans
bool winner(vector<Ship> player_ships, vector<Ship> ai_ships, bool & player_victory, bool & ai_victory);
// Postcondition: will determine if either of the opponents ships are destroyed, if so will set the corresponding boolean to true. Will return true if there was a winner

// Precondition: call at beginning of game
bool enable_cheats();
// Postcondition: will prompt the user if they would like to see the opponents map

// Precondition: call when attempting to view current ships
void display_current_ships(vector<Ship> player_ship, vector<Ship> ai_ship);
// Postcondition: will print active and destroyed ships of both players

int main()
{
	// Declare the AI object
	AI computer;

	// Declare 2 vectors of strings which will hold the computers positive and negative statements
	vector<string> positive_statements = load_file("ai_positive.txt");
	vector<string> negative_statements = load_file("ai_negative.txt");
	
	// Declare vector of strings to hold the text art which will be displayed at beginning
	vector<string> splash_screen = load_file("splashscreen.txt");

	// Declare and intialize Map objects, one being the ships board and the other being the hits/misses board
	Map player_map(WIDTH, HEIGHT, BLANK, SHIP);
	Map player_hits_map(WIDTH, HEIGHT, BLANK, SHIP);

	// Display the text art
	for (int i = 0; i < splash_screen.size(); i++)
	{
		cout << "\t\t\t\t" << splash_screen[i] << endl;
	}

	clear_screen();

	// Give credit where due
	cout << "text art courtesy of http://patorjk.com. Press any key to continue....";

	_getch();

	// Clear the screen 
	clear_screen();
	clear_screen();
	clear_screen();

	// Game logic booleans
	bool done = false;
	bool player_won = false;
	bool computer_won = false;

	// Create the players maps
	player_hits_map.create_map();
	player_map.create_map();

	// Declare and intialize the players fleet
	vector<Ship> fleet = intialize_fleet();

	// Intialize the AI's map
	computer.initialize_map(WIDTH, HEIGHT, BLANK, SHIP);

	// Create the computers fleet
	computer.create_fleet();

	// Determine if player wants to use cheats
	if (enable_cheats())
	{
		computer.print_map();
	}

	// Create the players fleet and set it in the map
	create_fleet(player_map, fleet);

	// Print both maps side by side
	player_map.print_two_maps(player_hits_map, player_map);
	
	// Start the main game loop, do while there is no winner
	do
	{
		// Player turn
		player_turn(computer.get_fleet(), player_hits_map);

		// Computer turn
		computer.ai_turn(fleet);

		// Update map
		update_map(fleet, player_hits_map, player_map, computer, positive_statements, negative_statements);

	} while (!winner(fleet, computer.get_fleet(), player_won, computer_won));

	if (player_won)
	{
		cout << "Congrats! You have won!\n";
	}
	else
	{
		cout << "Sorry, but you have lost!\n";
	}

	cout << "Press any key to continue...\n";

	_getch();

	return 0;
}

void create_fleet(Map & map, vector<Ship>& fleet)
{
	cout << "You will now choose the location of your ships. You will choose the start coordinate,\nthen be given options of where your ship may go.\n"
		<< "*You will not choose each individual coordinate*\n\n";

	map.print_map();
	
	// Create all the ships
	for (int i = 0; i < fleet.size(); i++)
	{
		cout << fleet[i].get_name() << " , Size: " << fleet[i].get_size() << endl;
		// Integers to hold function data
		int r_row;
		int r_col;

		int _end_col;
		int _end_row;

		// Boolean which will be true if the chosen coordinate is part of another ship
		bool part_of_ship = false;

		int choice = NULL;

		do
		{
			// Get users input for start coord
			get_coordinate_input(r_row, r_col, map);

			// Determine if coordinate is part of another ship
			for (int k = 0; k < fleet.size(); k++)
			{
				if (fleet[k].part_of_ship(r_row, r_col))
				{
					part_of_ship = true;
					cout << "[ERROR]: Can not place ships on top of one another!\n\n";
					break;
				}
				else
				{
					part_of_ship = false;
				}
			}

		} while (!map.good_coord(r_row, r_col) || part_of_ship);

		// Get possible endpoints
		vector<Point> possible = fleet[i].get_possible_endpoints(map, (fleet[i].get_size() - 1), r_row, r_col, BLANK);

		// Print the possible end coordinates to the user
		for (int j = 0; j < possible.size(); j++)
		{
			cout << " (" << j + 1 << ") " << "POSSIBLE END CORD: " << possible[j].get_direction_name(possible[j]._direction) << " " << (char)(possible[j]._row + 65) << possible[j]._col + 1 << endl;
		}

		bool good_decision = false;

		// Prompt user for choice
		do
		{
			cout << "Please enter one of the choices above for your endpoint coordinate (ie. 1): ";
			cin >> choice;

			for (int j = 0; j < possible.size(); j++)
			{
				if ((choice - 1) == j)
				{
					good_decision = true;
					break;
				}
			}

		} while (!good_decision);

		// Add coordinates to ship object based on direction
		switch (possible[choice - 1]._direction)
		{
		case 1:
			for (int j = 0; j < fleet[i].get_size(); j++)
			{
				fleet[i].add_coord(r_row - j, r_col);
			}
			break;
		case 2:
			for (int j = 0; j < fleet[i].get_size(); j++)
			{
				fleet[i].add_coord(r_row + j, r_col);
			}
			break;
		case 3:
			for (int j = 0; j < fleet[i].get_size(); j++)
			{
				fleet[i].add_coord(r_row, r_col - j);
			}
			break;
		case 4:
			for (int j = 0; j < fleet[i].get_size(); j++)
			{
				fleet[i].add_coord(r_row, r_col + j);
			}
			break;
		default:
			break;
		}

		// Set the ship
		fleet[i].set_ship(map, SHIP);

		clear_screen();

		map.print_map();
	}

	return;
}

void player_turn(vector<Ship> & ai_fleet, Map & hits_map)
{
	// Function data
	int r_row, r_col;
	bool hit = false;

	bool good_cord = false;
	
	// Get valid coordinate from user
	do
	{
		get_coordinate_input(r_row, r_col, hits_map);
	} while (!hits_map.good_coord(r_row, r_col));

	// Determine if coord is a hit on the AI board
	for (int i = 0; i < ai_fleet.size(); i++)
	{
		if (ai_fleet[i].part_of_ship(r_row, r_col))
		{
			// If its a hit set that point to the destroyed character
			hits_map.set_point(r_row, r_col, "X");
			ai_fleet[i].point_destroyed(r_row, r_col);
			hit = true;

			// If the ship was destroyed, print output
			if (ai_fleet[i].is_destroyed())
			{
				cout << "You have destroyed the computers " << ai_fleet[i].get_name() << "!\nPress any key to continue...\n";
				_getch();
			}
		}
	}

	// If not a hit, set the point as a miss on the hits/misses board
	if (!hit)
	{
		hits_map.set_point(r_row, r_col, "O");
	}

	return;
}

void clear_screen()
{
	// Print out 20 endlines
	for (int i = 0; i < 20; i++)
	{
		cout << endl;
	}

	return;
}

void update_map(vector<Ship> playerFleet, Map hits_map, Map & player_map, AI aiPlayer, vector<string> pos_statements, vector<string> neg_statements)
{
	int statement_choice;

	// Update the players map based on AI's hits and misses

	for (int i = 0; i < aiPlayer.get_hits().size(); i++)
	{
		player_map.set_point(aiPlayer.get_hits()[i]._row, aiPlayer.get_hits()[i]._col, "X");
	}

	for (int i = 0; i < aiPlayer.get_misses().size(); i++)
	{
		player_map.set_point(aiPlayer.get_misses()[i]._row, aiPlayer.get_misses()[i]._col, "O");
	}

	// Print the updated map
	player_map.print_two_maps(hits_map, player_map);

	// Print out AI choice
	cout << "[AI] I choose point " << (char)(aiPlayer.get_last_move()._row + 65) << (aiPlayer.get_last_move()._col + 1) << endl;

	// Print random output based on previous AI move, whether it was a hit or miss
	if (aiPlayer.get_last_move()._destroyed)
	{
		statement_choice = (rand() % pos_statements.size());
		cout << "[AI]: " << pos_statements[statement_choice];
	}
	else
	{
		statement_choice = (rand() % neg_statements.size());
		cout << "[AI]: " << neg_statements[statement_choice];
	}

	cout << endl;


	// Prompt user to see current ships
	char temp;
	cout << "Press * to see status of ships, or any other letter to continue.\n";

	cin >> temp;
	
	if (temp == '*')
	{
		// If the user wants to see ships, clear the screen, print them, then clear the screen again and go back to game
		clear_screen();
		display_current_ships(playerFleet, aiPlayer.get_fleet());

		cout << "Press any key to continue...\n";
		_getch();
		clear_screen();

		// Print both maps
		player_map.print_two_maps(hits_map, player_map);
	}

	cout << endl;

	return;
}

bool winner(vector<Ship> player_ships, vector<Ship> ai_ships, bool & player_victory, bool & ai_victory)
{
	bool winner = false;

	// Determine if all of the players ships are destroyed
	for (int i = 0; i < player_ships.size(); i++)
	{
		if (player_ships[i].is_destroyed())
		{
			winner = true;
		}
		else
		{
			winner = false;
			break;
		}
	}

	if (winner)
	{
		ai_victory = true;
		return winner;
	}

	// Determine if all of the AI's ships are destroyed
	for (int i = 0; i < ai_ships.size(); i++)
	{
		if (ai_ships[i].is_destroyed())
		{
			winner = true;
		}
		else
		{
			winner = false;
			break;
		}
	}

	if (winner)
	{
		player_victory = true;
		return winner;
	}

	// Return false if it reaches this point, no winner
	return winner;
}

bool enable_cheats()
{
	bool result = false;

	// Prompt user if they would like cheats

	char answer;
	do
	{
		cout << "Would you like to enable cheats (y)es or (n)o: ";
		cin >> answer;
		answer = tolower(answer);
	} while ((answer != 'n') && (answer != 'y'));

	if (answer == 'y')
	{
		result = true;
	}
	else
	{
		result = false;
	}

	return result;
}

void display_current_ships(vector<Ship> player_ship, vector<Ship> ai_ship)
{
	// Print ship data for the player
	for (int i = 0; i < player_ship.size(); i++)
	{
		if (player_ship[i].is_destroyed())
		{
			cout << player_ship[i].get_name() << ": Destroyed.\n";
		}
		else
		{
			cout << player_ship[i].get_name() << ": Active.\n";
		}
	}

	cout << endl;

	// Print ship data for the AI
	for (int i = 0; i < ai_ship.size(); i++)
	{
		if (ai_ship[i].is_destroyed())
		{
			cout << "AI: " << ai_ship[i].get_name() << ": Destroyed.\n";
		}
		else
		{
			cout << "AI: " << ai_ship[i].get_name() << ": Active.\n";
		}
	}

	return;
}

void convert_cord(int & row, int & col)
{
	// Convert the coord to usable coordinate in the 2D vector array
	row -= 65;
	col -= 1;
	return;
}

void get_coordinate_input(int & row, int & col, Map _map)
{
	// Function variables

	int row_temp, col_temp;

	char c_row;

	bool good_input = false;

	// Get a valid row coordinate
	do
	{
		cout << "Please enter a \'valid\' row value (ie. g or G): ";
		cin >> c_row;
		
		row_temp = static_cast<int> (toupper(c_row));

		// If row is not valid on the specific board
		if (((row_temp - 65) < 0) || ((row_temp - 65) > (_map.get_height() - 1)))
		{
			good_input = false;
		}
		else
		{
			good_input = true;
		}

	// Do while a character was not given or if the input is not good
	} while (!isalpha(c_row) || !good_input);

	good_input = false;

	cout << "Please enter a \'valid\' col value (ie. 4): ";
	cin >> col_temp;

	// Prompt user for valid column coordinate * credits: https://www.hackerearth.com/practice/notes/validating-user-input-in-c/
	while (cin.fail() && !good_input)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Please enter a \'valid\' col value (ie. 4): ";
		cin >> col_temp;

		if ((col_temp < 1) || (col_temp > _map.get_width()))
		{
			good_input = false;
		}
		else
		{
			good_input = true;
		}
	}

	// Convert the coord to valid map coordinates
	_map.convert_coord(row_temp, col_temp);

	// Set the reference parameters
	row = row_temp;
	col = col_temp;

	return;
}

vector<Ship> intialize_fleet()
{
	vector<Ship> fleet;

	// Declare ship objects
	Ship destroyer_one("Destroyer 1", 2);
	Ship destroyer_two("Destroyer 2", 2);
	Ship cruiser("Cruiser", 3);
	Ship battleship("Battleship", 4);
	Ship aircraft_carrier("Aircraft Carrier", 5);

	// Add ships onto the fleet vector
	fleet.push_back(destroyer_one);
	fleet.push_back(destroyer_two);
	fleet.push_back(cruiser);
	fleet.push_back(battleship);
	fleet.push_back(aircraft_carrier);

	return fleet;
}

vector<string> load_file(string file_name)
{
	// Vector of strings that will be returned
	vector<string> statements;

	// Temporary string to hold each line of the file
	string temp;

	// Declare the input stream
	ifstream input_stream;

	// Open the file
	input_stream.open(file_name);

	// If the file fails, print error and exit
	if (input_stream.fail())
	{
		cout << "ERROR LOADING FILE: " << file_name << endl;
		exit(-1);
	}

	// While the input stream has not reached the end of the file
	while (!input_stream.eof())
	{
		// Get the current line
		getline(input_stream, temp);

		// Push back the current line onto the vector of strings
		statements.push_back(temp);
	}

	// Close the file to prevent corruption
	input_stream.close();

	// Return the file contents
	return statements;
}
