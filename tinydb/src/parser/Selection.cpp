//
//  Selecttion.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#include "Selection.h"

namespace Parser{

Selection::Selection(Constant constant) {
    this->type = ConstantSelection;
    this->constant = constant;
}

Selection::Selection(std::string binding, std::string name) {
    this->type = AttributeSelection;
    this->binding = binding;
    this->name = name;
}

}
