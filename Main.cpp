// Information om komplettering:
//   Siffrorna hänvisar till rättningsprotokollet som finns på
//   kurshemsidan -> laboration -> "UPP-gruppens gemensamma rättningsprotokoll"
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   eriek993@student.liu.se

//Komplettering: inget korrekt felmedelande om flagga saknas.

#include <iostream>
#include <string>
#include <cctype>
#include <exception>
#include "Ordlista.h"
int main(int argc, char *argv[])
{
  	std::string argoutput{};

  	if (argc < 2)
    {
  	    std::cout << "Error: No arguments given.\n";
  	    std::cout << "Usage: a.out FILE [-a] [-f] [-o N] \n ";
        return 0;
  	}
    else if(argc > 2)
    {
      argoutput = argv[2];
    }

  	if (  (argoutput!="-a" && argoutput!="-f" && argoutput!="-o") || argc == 2)
  	{
  	    std::cout << "Second argument missing or invalid.\n";
  	    std::cout << "Usage: a.out FILE [-a] [-f] [-o N] \n ";
        return 0;
  	}
	  else
	  {
        try
        {
        		std::string filename = argv[1];

        		Ordlista ord{ filename };

        		if (argoutput == "-o")
      		  {
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
                     return 0;
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
        catch (std::string & e)
      	{
      		std::cout << "ERROR: failed to open file " << e << '\n';
      	}
  	}
  	return 0;
}
