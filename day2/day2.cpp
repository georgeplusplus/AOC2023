#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

const static int MAX_RED_CUBES = 12;
const static int MAX_GREEN_CUBES = 13;
const static int MAX_BLUE_CUBES = 14;

class CubeSet
{
public:
	CubeSet(){};

	void handleNewCount(int count, std::string color)
	{
		if (color == "red")
		{
			if (count > min_red_cubes)
			{
				min_red_cubes = count;
			}
			
		}
		else if (color == "blue")
		{
			if (count > min_blue_cubes)
			{
				min_blue_cubes = count;
			}
		}
		else if (color == "green")
		{
			if (count > min_green_cubes)
			{
				min_green_cubes = count;
			}
		}
		else
		{
			std::cout << "Invalid Color Parsed" << std::endl;
		}
	}

	int calculatePower()
	{
		return min_red_cubes * min_blue_cubes * min_green_cubes;
	}

	std::string getValues()
	{
		std::stringstream output;
		output << "Minimum Cubes Required for this set is \n"
			<< "Red: " << min_red_cubes << "\n"
			<< "Blue: " << min_blue_cubes << "\n"
			<< "Green: " << min_green_cubes;

		return output.str();
	}

private:
	int min_red_cubes = 1;
	int min_blue_cubes = 1;
	int min_green_cubes = 1;
}; // end CubeSet


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

int main()
{
	std::string line;
	std::string colon = ":";
	std::string space = " ";
	int total = 0;


	std::ifstream infile("input.txt");
	while (std::getline(infile, line))
	{
		std::vector<std::string> text2sets = {};

		std::size_t found_space = line.find(space); 
		std::size_t found_colon = line.find(colon);
		int current_game_value = std::stoi(line.substr(found_space, (found_colon - found_space)));
		std::string parsed_line = (line.erase(0, found_colon+1));
		splitText(text2sets, parsed_line, ';');

		CubeSet cubeset = CubeSet();

		for (auto& set : text2sets)
		{
			std::vector<std::string> cube_sets = {};
			splitText(cube_sets, set, ',');
			
			for (auto& cube : cube_sets)
			{
				std::vector<std::string> colored_cube_count = {};
				splitText(colored_cube_count, cube, ' ');
				//std::cout << colored_cube_count[0] << " " << colored_cube_count[1] << std::endl;
				assert(colored_cube_count.size() == 2);
				cubeset.handleNewCount(std::stoi(colored_cube_count[0]), colored_cube_count[1]);
			}
		}
		//std::cout << cubeset.getValues() << std::endl;
		total += cubeset.calculatePower();

	}
	std::cout << total << std::endl;
}