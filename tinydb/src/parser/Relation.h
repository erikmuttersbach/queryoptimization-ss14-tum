//
//  Relation.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__Relation__
#define __Exercise1__Relation__

#include <string>

namespace Parser{

class Relation {
public:
    Relation(std::string name, std::string binding);
    
    std::string name;
    std::string binding;
};

}
#endif /* defined(__Exercise1__Relation__) */
