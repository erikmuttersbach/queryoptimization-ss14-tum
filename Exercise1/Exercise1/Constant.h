//
//  Constant.h
//  Exercise1
//
//  Created by Erik Muttersbach on 16/04/14.
//
//

#ifndef __Exercise1__Constant__
#define __Exercise1__Constant__

#include <string>

typedef enum {
    Double,
    String
} Type;

class Constant {
public:
    Constant(std::string value);
    Constant(double value);
    
    Type type;
    std::string string_value;
    double double_value;
};

#endif /* defined(__Exercise1__Constant__) */
