//
//  Parser.h
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#ifndef __Exercise1__Parser__
#define __Exercise1__Parser__

#include <string>

#include "Query.h"
namespace Parser{

class Parser {
public:
    static Query parse(std::string query_str);
};

}
#endif /* defined(__Exercise1__Parser__) */
