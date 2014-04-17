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

class Query {
public:
    Query();
    
    std::vector<Selection> selections;
    std::vector<Relation> relations;
};

#endif /* defined(__Exercise1__Query__) */
