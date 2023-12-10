#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <map>

typedef std::vector<std::vector<int64_t>>  Conversion;

std::vector<std::string> map_order = { "seed-to-soil", "soil-to-fertilizer ", "fertilizer-to-water",
						"water-to-light", "light-to-temperature","temperature-to-humidity", "humidity-to-location" };

std::vector<int64_t> splitText(const std::string& text)
{
	std::vector<int64_t> output = {};
	std::stringstream text_stream(text);

	while (text_stream.good())
	{
		std::string tempset;
		getline(text_stream, tempset, ' ');
		if (!tempset.empty())
		{
			output.push_back(stoull(tempset));
		}
	}
	return output;
}

std::vector<int64_t> getSeeds(std::string line)
{
	return splitText(line.substr(line.find(':') + 1));
}

int main()
{
	std::ifstream input("test.txt");
	std::string line;
	getline(input, line);
	auto seeds = getSeeds(line);
	std::map < std::string, Conversion> seed_map = {};
	auto iter = map_order.begin();
	std::string current_order = "";

	while (getline(input, line))
	{
		if (line.empty())
		{
			continue;
		}
		if (iter != map_order.end())
		{
			if (line.find(*iter) != std::string::npos)
			{
					//std::cout << "Found " << *iter << std::endl;
					current_order = *iter;
					iter++;
					seed_map.insert(std::make_pair(current_order, Conversion()));
					continue;
			}
			
		}
		seed_map.at(current_order).push_back(splitText(line));
		
	}
	// now that we got the Map parsed, we can find the route to the location

	int64_t min_location = 9999999999;
	int64_t transition = 0;
	for (auto& seed : seeds)
	{
		transition = seed;
		for (auto& order : map_order)
		{
			for (auto& row : seed_map[order])
			{
				if (transition >= (row[1]) && transition < (row[1] + row[2]))
				{
					//std::cout << order << " Transition " << transition << " :" << row[0] << " " << row[1] << " "<< row[2] << std::endl;
					
					transition = row[0] + abs(transition - row[1]);
					//std::cout << seed << " Transition became:" << transition << std::endl;
					break;
				}
			}
			//std::cout << " Transition became:" << transition << std::endl;

		}
		//std::cout << std::endl;
		if (transition < min_location)
		{
			min_location = transition;
		}
	}
	std::cout << " Minimum :" << min_location << std::endl;
	return 0;
}