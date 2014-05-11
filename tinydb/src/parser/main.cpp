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
    string s("SELECT \"Hans\", name, t.salary, t.age, 22 FROM table t, schema s WHERE t.id = s.id AND s.tid = 'Toll'");
    
    Parser parser;
    parser.parse(s);
    
    return 0;
}

