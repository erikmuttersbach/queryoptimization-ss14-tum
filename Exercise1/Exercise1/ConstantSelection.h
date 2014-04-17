//
//  ConstantSelection.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__ConstantSelection__
#define __Exercise1__ConstantSelection__

#include <string>

#include "Selection.h"
#include "Constant.h"

class ConstantSelection : public Selection {
public:
    ConstantSelection(Constant constant);
    
    Constant constant;
};

#endif /* defined(__Exercise1__ConstantSelection__) */
