//
//  Attribute.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#include "Attribute.h"
namespace Parser{
Attribute::Attribute() {
    
}

Attribute::Attribute(std::string binding, std::string name) {
    this->binding = binding;
    this->name = name;
}
}
