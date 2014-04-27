//
//  Attribute.h
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#ifndef __Exercise1__Attribute__
#define __Exercise1__Attribute__

#include <string>

class Attribute {
public:
    Attribute();
    Attribute(std::string binding, std::string name);
    
    std::string binding;
    std::string name;
};

#endif /* defined(__Exercise1__Attribute__) */
