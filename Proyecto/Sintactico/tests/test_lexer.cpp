#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <sstream>
#include "doctest.h"
#include "lexer.h"
#include "Sintactico.h"
using namespace std;

const char *test = "(245)+8";


TEST_CASE("Lexer")
{
    std::istringstream ins;

    ins.str(test);
    Lexer l(ins);
    // Sintactico s();
    try
    {
        // s.parse();
        cout<<"Correcto"<<endl;
    }
    catch (const std::string e)
    {
        std::cout<<"Error:"<<e<<std::endl;
        return;
    }
    
}
