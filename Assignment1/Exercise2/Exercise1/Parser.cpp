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
#include <boost/algorithm/string/regex.hpp>

using namespace std;

Query Parser::parse(std::string query_str) {
    regex regex("(SELECT .*)(FROM .*)(WHERE .*)", regex_constants::icase);
    smatch match;
    regex_match(query_str, match, regex);
    
    if(match.size() != 4) {
        throw std::invalid_argument("Query does match SELECT .* FROM .* WHERE .* syntax");
    }
    
    string select_str = match[1];
    string from_str = match[2];
    string where_str = match[3];
    
    Query query;
    
    // evaluate SELECT
    if(std::regex_match(select_str, std::regex("SELECT\\s*\\*\\s*", regex::ECMAScript))) {
        // leave query.selections empty to indicate that all should be
        // selected
    } else {
        // remove SELECT and any whitespaces from the input
        boost::algorithm::erase_all(select_str, "SELECT");
        boost::algorithm::erase_all(select_str, " ");
        
        // split the remainder by "," and check with regex
        // if it confirms to our input format
        std::regex attribute_regex("(?:([\'\"a-zA-Z0-9-_]+)\\.){0,1}([\'\"a-zA-Z0-9-_]+)", regex::ECMAScript);
        
        vector<string> tokens;
        boost::algorithm::split(tokens, select_str, boost::is_any_of(","));
        for(uint i=0; i<tokens.size(); i++) {
            std::smatch match;
            std::regex_search(tokens[i], match, attribute_regex);
            
            if(match.size() != 3) {
                throw std::invalid_argument("Attribute in SELECT is not of the form binding.attribute");
            }
            
            // if the group before the dot was matched, we have a binding
            // like "binding.attribute"
            if(match[1].length() > 0) {
                Selection selection(match[1], match[2]);
                query.selections.push_back(selection);
            } else {
                string attribute = match[2];
                // check if we have a constant string like 'foo' or "bar"
                if(std::regex_match(attribute, std::regex("(\".*\")|(\'.*\')"))) {
                    boost::algorithm::erase_all(attribute, "\"");
                    boost::algorithm::erase_all(attribute, "\'");
                    
                    Constant constant(attribute);
                    Selection selection(constant);
                    
                    query.selections.push_back(selection);
                } else {
                    Selection selection(string(""), attribute);
                    query.selections.push_back(selection);
                }
                
                /* TODO Check for numeric constants here*/
            }
        }
    }
    
    // parse FROM
    boost::algorithm::erase_all(from_str, "FROM");
    
    vector<string> tokens;
    boost::algorithm::split(tokens, from_str, boost::is_any_of(","));
    for(uint i=0; i<tokens.size(); i++) {
        smatch match;
        if(regex_search((string)tokens[i], match, std::regex("\\s*([a-zA-Z-_]+)\\s+([a-zA-Z-_]+)\\s*"))) {
            Relation relation(match[1], match[2]);
            query.relations.push_back(relation);
        } else {
            throw std::invalid_argument("relation in FROM clause does not match format");
        }
    }
    
    // parse WHERE
    boost::erase_all(where_str, "WHERE");
    boost::replace_all(where_str, " and ", ",");
    boost::replace_all(where_str, " AND ", ",");
    boost::erase_all(where_str, " ");
    
    std::regex join_condition_attribute_regex("([a-zA-Z0-9-_]+)\\.([a-zA-Z0-9-_]+)=(?:([a-zA-Z0-9-_]+)\\.([a-zA-Z0-9-_]+))", regex::ECMAScript);
    std::regex join_condition_constant_regex("([a-zA-Z0-9-_]+)\\.([a-zA-Z0-9-_]+)=([\'\"a-zA-Z0-9-_]+)", regex::ECMAScript);

    boost::algorithm::split(tokens, where_str, boost::is_any_of(","));
    for(uint i=0; i<tokens.size(); i++) {
        std::smatch match;
        std::regex_search(tokens[i], match, join_condition_attribute_regex);
        
        if(match.size() > 0) {
            Attribute left(match[1], match[2]);
            Attribute right(match[3], match[4]);
            JoinCondition join_condition(left, right);
        
            query.join_conditions.push_back(join_condition);
        } else {
            // TODO we cannot parse numeric constants
            std::regex_search(tokens[i], match, join_condition_constant_regex);
            
            string constant_str = match[3];
            boost::algorithm::erase_all(constant_str, "\"");
            boost::algorithm::erase_all(constant_str, "\'");
            
            Attribute left(match[1], match[2]);
            Constant right(constant_str);
            JoinCondition join_condition(left, right);
            
            query.join_conditions.push_back(join_condition);
        }
    }
    
    return query;
}