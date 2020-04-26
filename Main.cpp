
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator> 
#include <map> 
#include <cctype>
#include "Ordlista.h"
int main(int argc, char *argv[])
{ 

    std::cout << "Begin of file \n";
	std::string argoutput = argv[2];
	if (argc <=1){
	std::cout << "Error: No arguments given.\n";
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N] \n ";
	}
	else if (  argoutput!="-a" && argoutput!="-f" && argoutput!="-o")
	{
		
	std::cout << "Second argument missing or invalid.\n";
	std::cout << "Usage: a.out FILE [-a] [-f] [-o N] \n ";
	}
	else
	{
		std::string filename = argv[1];
		Ordlista ord{ filename };
		if (argoutput == "-o")
		{
			std::cout << "here";
			try
			{
				std::string strr = argv[3];
				int N = std::stoi(strr);
				if (N >= 0)
				{
					ord.Print_Vector(N);
				}
				else 
				{
					throw N;
				}
			}
			catch (...)
			{
				std::cout << "N argument missing or invalid.\n";
				std::cout << "Usage: a.out FILE [-a] [-f] [-o N] \n ";
			}
		}
		else if (argoutput == "-a")
		{
			ord.Print_Ordered();
		}
		else if (argoutput == "-f")
		{
			ord.Print_Freq();
		}
	}
	return 0;
}
