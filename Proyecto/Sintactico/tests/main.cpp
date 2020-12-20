#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Sintactico.h"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Cannot open '" << argv[1] << "'\n";
        return 1;
    }

    Lexer lexer(input);

     Sintactico s(lexer);
   try
    {
        s.parse();
        cout<<"Correcto"<<endl;
    }
    catch (const std::string e)
    {
        std::cout<<"Error:"<<e<<std::endl;
    }
}