//
//  Query.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__Query__
#define __Exercise1__Query__

#include <vector>

#include "Selection.h"
#include "Relation.h"
#include "JoinCondition.h"

namespace Parser{

class Query {
public:
    Query();
    
    std::vector<Selection> selections;
    std::vector<Relation> relations;
    std::vector<JoinCondition> join_conditions;
};

}
#endif /* defined(__Exercise1__Query__) */
