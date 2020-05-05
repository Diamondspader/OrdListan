#include "Ordlista.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstddef>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <stdlib.h>


//Komplettering: se till att ta bort de warningar ni får vid kompilering.

Ordlista::Ordlista(const std::string & file_n) :
	 file_name{file_n}
{
	Insert_File();
}


bool CleanWord(std::string & wash_word)
{
	std::string alpha_check{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ"};
	std::size_t found_first_alpha = wash_word.find_first_of(alpha_check);

	//checks first part of junks characters
	if (found_first_alpha == std::string::npos)
	{
			return false;
	}

	if (found_first_alpha >= 1)
	{
			std::string tmp = wash_word.substr(0, found_first_alpha);
			std::size_t not_accepted_char = tmp.find_first_not_of("\"(\'");

			if (not_accepted_char != std::string::npos)
			{
					return false;
			}
			wash_word = wash_word.substr(found_first_alpha, wash_word.size());
	}

//checks last part of junks characters
	std::size_t find_first_junk = t.find_first_not_of(alpha_check + "-" + "'");

	if(find_first_junk != std::string::npos)
	{
			std::string tmp_2 = wash_word.substr(find_first_junk, wash_word.size());
			std::size_t not_accepted_char = tmp_2.find_first_not_of(")!;:,.?\'\"");
			if (not_accepted_char != std::string::npos)
			{
				return false;
			}
			std::size_t find_last_alpha = wash_word.find_last_of(alpha_check);

			wash_word = wash_word.substr(0, find_last_alpha+1);

	}

	//check if "'s'"  is at the end
	std::size_t apostrophe = wash_word.find("\'");
	if (apostrophe != std::string::npos)
	{

			if  ( (apostrophe == wash_word.size()-2))
			{
					if (wash_word.back() == 's' || wash_word.back() == 'S')
					{
							wash_word = wash_word.substr(0, apostrophe);
					}
			}
			else
			{
					return false;
			}
	}

	// om binde ligger sist eller direkt efter en binde eller mindre än 3.
	std::size_t double_dash = wash_word.find("--");
	if (double_dash != std::string::npos || wash_word.back() == '-' || wash_word.size() < 3)
	{
			return false;
	}

	return true;
}

void Ordlista::Insert_File()
{

	iss.open(file_name, std::ifstream::in);
	if (iss.is_open())
	{

			std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
					 std::istream_iterator<std::string>{} };


			std::transform(tokens.begin(), tokens.end(), back_inserter(print_order), [&](const std::string & str)
			{
					if(cleanWord(str))
					{
							ordered[str]++;
							return str;
					}
			}
	}
	else
	{
		std::cout << "failed to open file " << file_name << '\n';
	}
}


//Komplettering: kodupprepning i funktionerna här.
void Ordlista::Print_Ordered()
{
	unsigned int longest_word{0};
	std::vector<strInt> output;
	output.reserve(ordered.size());



	std::transform(ordered.begin(), ordered.end(), back_inserter(output), [&](const strInt& pair)
	{
	if(pair.first.length() > longest_word)
	{
		longest_word = pair.first.length();
	}
	return pair; });
//std::string word = std::max_element(ordered.begin(),ordered.end());

		std::transform(ordered.begin(), ordered.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [&](const strInt& a)
		{
			std::stringstream ss;

			std::string width = std::to_string(a.second);
			int fill_width = width.length();
			int width_length =  longest_word - (int)a.first.length()+ fill_width +2;
			ss << a.first << std::setw(width_length) << std::setfill(' ') << a.second;
			return ss.str();
		});
}



void Ordlista::Print_Freq()
{
	unsigned int longest_word{ 0 };
	std::vector<strInt> output;
	output.reserve(ordered.size());

	//Komplettering: detta är en vagt förklädd loop.
	//               använd en bättre algoritm för att hitta max längd.
	//               Tips: max_element.
	std::transform(ordered.begin(), ordered.end(), back_inserter(output), [&](const strInt& pair) {
		if(pair.first.length() > longest_word){
			longest_word = pair.first.length();
		}
		return pair; });

	std::sort(output.begin(), output.end(), [&](const strInt& a, const strInt& b) { return a.second > b.second; });

	std::transform(output.begin(), output.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [&](const strInt& a)
		{
			std::stringstream ss;
			std::string width = std::to_string(a.second);
			int fill_width = width.length() + 2;
			ss <<std::setw(longest_word) << std::setfill(' ')<< a.first << std::setw(fill_width) << std::setfill(' ') << a.second;
			return ss.str();
		});
}

void Ordlista::Print_Vector(int limiter)
{
	int counter{0};
	auto print = [&](const std::string& n)
	{
		counter += n.length();
		if (counter >= limiter){
		std::cout << '\n';
		counter = 0;
		counter += n.length();
		}
		std::cout << n << " ";
		counter++;
	};
	std::for_each(print_order.cbegin(), print_order.cend(), print);

}
