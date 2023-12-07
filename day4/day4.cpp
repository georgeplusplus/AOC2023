#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <numeric>	
#include <algorithm>
using namespace std;


std::vector<int> splitText(const std::string &text)
{
	std::vector<int> output = {};
	std::stringstream text_stream(text);

	while (text_stream.good())
	{
		std::string tempset;
		getline(text_stream, tempset, ' ');
		if (!tempset.empty())
		{
			output.push_back(stoi(tempset));
		}
	}
	return output;
}

class Card
{
public: 
	Card(int num, const string &line){
		card_num = num;
		size_t lhs_pos = line.find(':');
		size_t rhs_pos = line.find('|');
		lhs = splitText(line.substr(lhs_pos + 1, rhs_pos - lhs_pos - 1));;
		rhs = splitText(line.substr(rhs_pos + 1));
		1;
	};

	int card_num = 0;
	std::vector<int> lhs;
	std::vector<int> rhs;
};

int countMatch(const Card &card)
{
	int match = 0;
	for (auto& winning_number : card.lhs)
	{
		(std::find(card.rhs.begin(), card.rhs.end(), winning_number) != card.rhs.end()? match++ : 0 );
	}
	return match;
}

int part1(const vector<Card> &Cards)
{
	int total = 0;
	
	for (auto& card : Cards)
	{
		int multiplier = 0;
		
		total += pow(2,(countMatch(card)-1));
	}
	return total;
}

int part2(const vector<Card>& Cards)
{
	std::vector<int> cardCount(Cards.size());
	std::fill(cardCount.begin(), cardCount.end(), 1);
	
	for (int cardId = 0; cardId < cardCount.size(); cardId++)
	{
		for (int i = 0; i < countMatch(Cards[cardId]); i++)
		{
			cardCount[cardId + i + 1] += cardCount[cardId];
		}
	}

	return std::accumulate(cardCount.begin(), cardCount.end(),0);
}

int main()
{	
    ifstream input("input.txt");
    string line;
	int cardId = 1;
	vector<Card> Cards = {};

    while (getline(input, line))
    {
		Card card = Card(cardId, line);
		Cards.push_back(card);
    }

	std::cout << part1(Cards) << std::endl;
	std::cout << part2(Cards) << std::endl;

	return 0;
}