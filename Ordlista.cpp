#include "Ordlista.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstddef>
#include <unordered_map>
#include <map>



Ordlista::Ordlista(const std::string & file_n) :
	 file_name{file_n}
{
	Insert_File();
}


void Ordlista::Insert_File()
{
	std::string alpha_check = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ";
	
	iss.open(file_name, std::ifstream::in);
	if (iss.is_open())
	{

		//std::istringstream iss(tmp);
		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
				 std::istream_iterator<std::string>{} };

		for (auto& t : tokens)
		{
			std::size_t found_first_alpha = t.find_first_of(alpha_check);

			//checks first part of junks characters
			if (found_first_alpha == std::string::npos)
			{
				//std::cout << "\n NOT AN ACCEPTED WORD \n";
				continue;
			}
			if (found_first_alpha >= 1)
			{
				std::string tmp = t.substr(0, found_first_alpha);
				std::size_t not_accepted_char = tmp.find_first_not_of("\"(\'");

				if (not_accepted_char != std::string::npos)
				{
					//std::cout << "\n NOT AN ACCEPTED WORD \n";
					continue;
				}
				t = t.substr(found_first_alpha, t.size());
			}

			//checks last part of junk characters
			std::size_t find_first_junk = t.find_first_not_of(alpha_check + "-" + "'");
			if (find_first_junk != std::string::npos)
				{
					std::string tmp_2 = t.substr(find_first_junk, t.size());
					std::size_t not_accepted_char = tmp_2.find_first_not_of(")!;:,.?\'\"");
					if (not_accepted_char != std::string::npos)
					{
					//std::cout << "\n NOT AN ACCEPTED WORD \n";
					continue;
					}
					//hej's''''''
					std::size_t find_last_alpha = t.find_last_of(alpha_check);
						
					t = t.substr(0, find_last_alpha+1);
					
				}
			//check if potential word    minst 3 tecken
			std::size_t apostrophe = t.find("\'");
			if (apostrophe != std::string::npos)
			{
				
				if  ( (apostrophe == t.size()-2))
				{
					if (t.back() == 's' || t.back() == 'S')
					{
						t = t.substr(0, apostrophe);
					}
				}
				else
				{
					continue;
				}
			}
		
			std::size_t double_dash = t.find("--");
			if (double_dash != std::string::npos)
			{
				continue;
			}
			if(t.back() == '-')
			{
				continue;
			}
			// om binde ligger sist eller direkt efter en binde.

			if (t.size() < 3) 
			{
				continue;
			}

			
			std::transform(t.begin(), t.end(), t.begin(), [](unsigned char c) { return std::tolower(c); });
			
			

			print_order.push_back(t);
			ordered[t]++;
		}
	}
	else 
	{
		std::cout << "failed to open file " << file_name << '\n';
	}
}


void Ordlista::Print_Ordered() 
{
	for (auto t : ordered) 
	{
		std::cout << t.first << " : " << t.second  << '\n';
	}
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
