//
//  JoinCondition.h
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#ifndef __Exercise1__JoinCondition__
#define __Exercise1__JoinCondition__

#include "Attribute.h"

class JoinCondition {
public:
    JoinCondition(Attribute left, Attribute right);
    
    Attribute left;
    Attribute right;
};

#endif /* defined(__Exercise1__JoinCondition__) */
