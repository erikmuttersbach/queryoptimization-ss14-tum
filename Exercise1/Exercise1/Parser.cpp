//
//  Parser.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#include "Parser.h"

#include <regex>
#include <exception>
#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;

Query Parser::parse(std::string query_str) {
    regex regex("(SELECT .*)(FROM .*)(WHERE .*)", regex_constants::icase);
    smatch match;
    regex_match(query_str, match, regex);
    
    if(match.size() != 4) {
        throw std::invalid_argument("Query does match SELECT .* FROM .* WHERE .* syntax");
    }
    
    string select_str = match[1];
    
    Query query;
    
    // evaluate SELECT
    if(std::regex_match(select_str, std::regex("SELECT\\s*"))) {
        // leave query.selections empty to indicate that all should be
        // selected
    } else {
        // remove SELECT and any whitespaces from the input
        boost::algorithm::erase_all(select_str, "SELECT");
        boost::algorithm::erase_all(select_str, " ");
        
        // split the remainder by "," and check with regex
        // if it confirms to our input format
        std::regex attribute_regex("(?:([a-zA-Z0-9-_]+)\\.){0,1}([a-zA-Z0-9-_]+)", regex::ECMAScript);
        
        vector<string> tokens;
        boost::algorithm::split(tokens, select_str, boost::is_any_of(","));
        for(uint i=0; i<tokens.size(); i++) {
            cout << "Token: " << tokens[i] << endl;
            std::smatch match;
            std::regex_search(tokens[i], match, attribute_regex);
            
            if(match.size() != 3) {
                throw std::invalid_argument("Attribute in SELECT is not of the form binding.attribute");
            }
            
            // if the group before the dot was matched, we have a binding
            // like "binding.attribute"
            if(match[1].length() > 0) {
                AttributeSelection selection(match[1], match[2]);
                query.selections.push_back(selection);
            } else {
                string attribute = match[2];
                
                // check if we have a constant string like 'foo' or "bar"
                if(std::regex_match((string)match[2], std::regex("\".*\"|\'.*\'"))) {
                    boost::algorithm::erase_all(attribute, "\"");
                    boost::algorithm::erase_all(attribute, "\'");
                    
                    Constant constant(attribute);
                    ConstantSelection selection(constant);
                    
                    query.selections.push_back(selection);
                } else /* TODO Check for numeric constants here*/ {
                    AttributeSelection selection(string(), attribute);
                    query.selections.push_back(selection);
                }
            }
        }
    }
    
    //cout << match.length() << " " << match.size() << endl;
    
    for(uint i=0; i<match.size()-1; i++) {
        cout << match[i+1] << endl;
    }
    
    return query;
}