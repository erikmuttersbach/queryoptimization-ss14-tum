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

#include "Constant.h"

namespace Parser{

typedef enum {
    JoinConditionRightAttribute,
    JoinConditionRightConstant
} JoinConditionType;

class JoinCondition {
public:
    JoinCondition(Attribute left, Attribute right);
    JoinCondition(Attribute left, Constant right);
    
    JoinConditionType type;
    
    Attribute left;
    
    Attribute rightAttribute;
    Constant rightConstant;
};

}
#endif /* defined(__Exercise1__JoinCondition__) */
