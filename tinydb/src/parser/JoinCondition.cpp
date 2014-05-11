//
//  JoinCondition.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#include "JoinCondition.h"
namespace Parser{

JoinCondition::JoinCondition(Attribute left, Attribute right) : left(left), rightAttribute(right) {
    this->type = JoinConditionRightAttribute;
}

JoinCondition::JoinCondition(Attribute left, Constant right) : left(left), rightConstant(right) {
    this->type = JoinConditionRightConstant;
}

}
