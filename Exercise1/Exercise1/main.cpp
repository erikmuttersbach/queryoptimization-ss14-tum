//
//  main.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#include <iostream>
#include <string>

#include "Parser.h"

using namespace std;

int main(int argc, const char * argv[])
{
    string s("SELECT \"Hans\", name, t.salary, t.age, 22 FROM table t WHERE t.id = 1");
    
    Parser parser;
    parser.parse(s);
    
    return 0;
}

