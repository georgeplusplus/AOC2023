#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

const static int MAX_RED_CUBES = 12;
const static int MAX_GREEN_CUBES = 13;
const static int MAX_BLUE_CUBES = 14;

void splitText(std::vector<std::string> &list, std::string text, char delimiter)
{
	std::stringstream text_stream(text);

	while (text_stream.good())
	{
		std::string tempset;
		getline(text_stream, tempset, delimiter);
		if (!tempset.empty())
		{
			list.push_back(tempset);
		}
	}
}

bool isElfTricky(int count, std::string color)
{
	int max_count = 0;
	if (color == "red")
	{
		max_count = MAX_RED_CUBES;
	}
	else if (color == "blue")
	{
		max_count = MAX_BLUE_CUBES;
	}
	else if (color == "green")
	{
		max_count = MAX_GREEN_CUBES;
	}
	else
	{
		std::cout << "Invalid Color Parsed" << std::endl;
		return true;
	}

	if (count > max_count)
	{
		std::cout << count << " vs " << max_count << std::endl;
		return true;
	}

	return false;
}

int main()
{
	std::string line;
	std::string colon = ":";
	std::string space = " ";
	int total = 0;


	std::ifstream infile("input.txt");
	while (std::getline(infile, line))
	{
		std::vector<std::string> sets = {};

		std::size_t found_space = line.find(space); 
		std::size_t found_colon = line.find(colon);
		int current_game_value = std::stoi(line.substr(found_space, (found_colon - found_space)));
		std::string line_to_sets = (line.erase(0, found_colon+1));
		splitText(sets, line_to_sets, ';');
		bool tricky_elf = false;

		for (auto& set : sets)
		{
			if (tricky_elf)
			{
				break;
			}
			std::vector<std::string> cube_sets = {};
			splitText(cube_sets, set, ',');
			
			for (auto& cube : cube_sets)
			{
				std::vector<std::string> colored_cube_count = {};
				splitText(colored_cube_count, cube, ' ');
				//std::cout << colored_cube_count[0] << " " << colored_cube_count[1] << std::endl;
				assert(colored_cube_count.size() == 2);
				tricky_elf = isElfTricky(std::stoi(colored_cube_count[0]), colored_cube_count[1]);
				if (tricky_elf)
				{
					break;
				}
			}
		}
		if (!tricky_elf)
		{
			total += current_game_value;
		}
	}
	std::cout << total << std::endl;
}