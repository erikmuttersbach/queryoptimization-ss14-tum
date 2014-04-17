//
//  AttributeSelection.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__AttributeSelection__
#define __Exercise1__AttributeSelection__

#include <string>

#include "Selection.h"

class AttributeSelection : public Selection {
public:
    AttributeSelection(std::string binding, std::string name);
    
    std::string binding;
    std::string name;
};

#endif /* defined(__Exercise1__AttributeSelection__) */
