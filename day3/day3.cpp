#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

struct GearNumber
{
	GearNumber(std::string digits, int _index, int _row) : value(digits), index(_index), row(_row) {};
	std::string outputValue()
	{
		return ("Value is: " + value 
			+ "\nIndex: " + std::to_string(index)
			+ "\nRow: " + std::to_string(row));
	};
	std::string value = "";
	int row = 0;
	int index = 0;
};

std::vector<std::pair<int, int>> findNeighbors(GearNumber gear)
{
	int min_index = gear.index - 1;
	int max_index = gear.index + gear.value.size();
	int min_row = gear.row - 1;
	int max_row = gear.row + 1;
	std::vector<std::pair<int, int>> neighbors = {};

	//		  -1   0   1   2   3						
	// row -1 [x] [x] [x] [x] [x]
	// row 0  [x] [7] [8] [9] [x] 
	// row +1 [x] [x] [x] [x] [x]

	for (int i = min_row; i <= max_row ; i++)
	{
		for (int j = min_index; j <= max_index; j++)
		{
			// skip if we are on the same position as the gear 
			if (i == gear.row && (j > min_index  && j < max_index))
			{
				continue;
			}
			neighbors.push_back(std::make_pair(i, j));
		}
	}
	return neighbors;
}

void findPotentialGears(std::vector<GearNumber>& list, std::string text, int row)
{
	std::stringstream text_stream(text);
	int index = 0;

	while (text_stream.good())
	{
		// extract the number from the string
		std::string tempset;
		getline(text_stream, tempset, ' ');

		if (!tempset.empty())
		{
			// mark the index where the string was found then increment by the strings size 
			index = text.find(tempset, index);
			GearNumber new_gear = GearNumber(tempset, index, row);
			index += tempset.size();
			list.push_back(new_gear);
		}
	}
}

int main()
{
	std::vector<std::string> grid = {};
	std::vector<GearNumber> potential_gear_list = {};
	std::ifstream infile("test.txt");
	std::string line;
	int current_row = 0;
	int total = 0;

	while (std::getline(infile, line))
	{
		grid.push_back(line);

		std::replace_if(line.begin(), line.end(), [](auto const c) -> bool 
			{ return (!std::isalnum(c) || c == '.'); }, ' ');
		findPotentialGears(potential_gear_list, line, current_row);
		current_row++;
	}
	for (auto& gear : potential_gear_list)
	{
		std::vector<std::pair<int, int>> neighbors = findNeighbors(gear);
		bool found = false;
		for (auto & neighbor : neighbors)
		{
			 // Skip if rows or index are out of bounds.
			if (neighbor.first < 0 || neighbor.first >= grid.size() || neighbor.second < 0 || neighbor.second >= grid[0].size())
			{
				continue;
			}
			if (!std::isalnum(grid[neighbor.first][neighbor.second]) && grid[neighbor.first][neighbor.second] != '.')
			{
				// Match found
				total += std::stoi(gear.value);
				break;
			}
		}
	}
	std::cout << total << std::endl;

	return 0;
}