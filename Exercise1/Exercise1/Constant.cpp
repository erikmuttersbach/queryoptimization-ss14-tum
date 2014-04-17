//
//  Constant.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#include "Constant.h"

Constant::Constant() {
    
}

Constant::Constant(std::string value) {
    this->type = String;
    this->string_value = value;
}

Constant::Constant(double value) {
    this->type = Double;
    this->double_value = value;
}

