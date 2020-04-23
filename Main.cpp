
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
	//std::cout << argv[1];
	Ordlista ord{ filename };
	ord.Print_Vector(9);
	}
	
	return 0;
}
