#ifndef ORDLISTA_H
#define ORDLISTA_H

#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <iterator> 
#include <sstream>
#include <fstream>
class Ordlista
{
public:

	typedef std::pair<std::string, int> strInt;
	Ordlista(const std::string & file_n);
	~Ordlista() {}
	void Print_Ordered();
	void Print_Freq();
	void Print_Vector(int limiter);
	

private:
	void Insert_File();
	std::map<std::string, int> ordered;
	std::vector <std::string> print_order;
	std::ifstream iss;
	std::string file_name;


};




#endif