//
//  Selecttion.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__Selection__
#define __Exercise1__Selection__

#include <string>

#include "Constant.h"

typedef enum {
    AttributeSelection,
    ConstantSelection
} SelectionType;

class Selection {
public:
    Selection(std::string binding, std::string name);
    Selection(Constant constant);
    
    SelectionType type;
    
    // if the selection is an AttributeSelection
    // TODO Should use an Attribute (Attribute.h) here
    std::string binding;
    std::string name;
    
    // if the selection is a ConstantSelection
    Constant constant;
};

#endif /* defined(__Exercise1__Selecttion__) */
