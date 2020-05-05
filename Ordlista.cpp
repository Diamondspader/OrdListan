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
		std::size_t find_first_junk = wash_word.find_first_not_of(alpha_check + "-" + "'");

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

		std::transform(wash_word.begin(), wash_word.end(), wash_word.begin(), [](unsigned char c) { return std::tolower(c); });
		return true;
}

void Ordlista::Insert_File()
{
		iss.open(file_name, std::ifstream::in);
		if (iss.is_open())
		{
				std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
						 std::istream_iterator<std::string>{} };

				std::transform(tokens.begin(), tokens.end(), back_inserter(print_order), [&](std::string & str)
				{
						if(CleanWord(str))
						{
								ordered[str]++;
								return str;
						}
						std::string str1{" "};
						return str1;
				});

				struct EmptyIndex
				{
						bool operator ()(const std::string & s)
						{
								return s.find(" ", 0) != std::string::npos;
						}
				};
				print_order.erase(std::remove_if( print_order.begin(), print_order.end(), EmptyIndex() )  , print_order.end());

		}
		else
		{
			throw file_name;
		}


}


int Get_Longest_Word(const std::vector<std::string> & vect)
{
		auto it = std::max_element(vect.begin(), vect.end(), [](const std::string a,const std::string b){return a.length() < b.length(); });
		//int longest_word{*word};
		std::string word = *it;

		return word.length();
}

//Komplettering: kodupprepning i funktionerna här.
void Ordlista::Print_Ordered()
{
		int longest_word{Get_Longest_Word(print_order)};

			std::transform(ordered.begin(), ordered.end(), std::ostream_iterator<std::string>(std::cout, "\n"), [&](const strInt& a)
			{
				std::stringstream ss;

				std::string width = std::to_string(a.second);
				int width_length =  longest_word - a.first.length() + width.length() + 2;
				ss << a.first << std::setw(width_length) << std::setfill(' ') << a.second;
				return ss.str();
			});
}



void Ordlista::Print_Freq()
{
		int longest_word{ Get_Longest_Word(print_order) };
		std::vector<strInt> output;
		output.reserve(ordered.size());

		std::transform(ordered.begin(), ordered.end(), back_inserter(output), [](const strInt & pair){ return pair; });

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
