//
//  Parser_Test.cpp
//  Exercise1
//
//  Created by Erik Muttersbach on 17/04/14.
//
//

#include <string>
#include <gtest/gtest.h>

#include "Parser.h"

using namespace std;


TEST(ParserTest, TestAllSelection) {
    Query query = Parser::parse(string("SELECT * FROM table t WHERE t.id = 1"));
    ASSERT_EQ(query.selections.size(), 0);
}

// --- SELECT: UNBOUND ATTRIBUTES

TEST(ParserTest, TestSelectUnboundAttribute) {
    Query query = Parser::parse(string("SELECT name FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 1);
    
    ASSERT_EQ(query.selections[0].type, AttributeSelection);
    ASSERT_STREQ("name", query.selections[0].name.c_str());
    ASSERT_STREQ("", query.selections[0].binding.c_str());
}

TEST(ParserTest, TestSelectTwoUnboundAttributes) {
    Query query = Parser::parse(string("SELECT name, salary FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 2);
    
    ASSERT_EQ(query.selections[0].type, AttributeSelection);
    ASSERT_STREQ("name", query.selections[0].name.c_str());
    ASSERT_STREQ("", query.selections[0].binding.c_str());
    
    ASSERT_EQ(query.selections[1].type, AttributeSelection);
    ASSERT_STREQ("salary", query.selections[1].name.c_str());
    ASSERT_STREQ("", query.selections[1].binding.c_str());
}

// --- SELECT: BOUND ATTRIBUTES

TEST(ParserTest, TestSelectBoundAttribute) {
    Query query = Parser::parse(string("SELECT t.name FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 1);
    
    ASSERT_EQ(query.selections[0].type, AttributeSelection);
    ASSERT_STREQ("name", query.selections[0].name.c_str());
    ASSERT_STREQ("t", query.selections[0].binding.c_str());
}

TEST(ParserTest, TestSelectTwoBoundAttributes) {
    Query query = Parser::parse(string("SELECT a.name, b.salary FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 2);
    
    ASSERT_EQ(query.selections[0].type, AttributeSelection);
    ASSERT_STREQ("name", query.selections[0].name.c_str());
    ASSERT_STREQ("a", query.selections[0].binding.c_str());
    
    ASSERT_EQ(query.selections[1].type, AttributeSelection);
    ASSERT_STREQ("salary", query.selections[1].name.c_str());
    ASSERT_STREQ("b", query.selections[1].binding.c_str());
}

// --- SELECT: CONSTANT ATTRIBUTES

TEST(ParserTest, TestSelectStringConstant) {
    Query query = Parser::parse(string("SELECT \"foo\" FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 1);
    
    ASSERT_EQ(query.selections[0].type, ConstantSelection);
    ASSERT_STREQ("foo", query.selections[0].constant.string_value.c_str());
}

TEST(ParserTest, TestSelectStringConstantAlternative) {
    Query query = Parser::parse(string("SELECT \'foo\' FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.selections.size(), 1);
    
    ASSERT_EQ(query.selections[0].type, ConstantSelection);
    ASSERT_STREQ("foo", query.selections[0].constant.string_value.c_str());
}

// --- FROM: RELATIONS

TEST(ParserTest, TestFromRelation) {
    Query query = Parser::parse(string("SELECT \'foo\' FROM table t WHERE t.id = 1"));
    
    ASSERT_EQ(query.relations.size(), 1);
    
    ASSERT_STREQ("table", query.relations[0].name.c_str());
    ASSERT_STREQ("t", query.relations[0].binding.c_str());
}

TEST(ParserTest, TestFromRelations) {
    Query query = Parser::parse(string("SELECT \'foo\' FROM professors profs, schema s WHERE t.id = 1"));
    
    ASSERT_EQ(query.relations.size(), 2);
    
    ASSERT_STREQ("professors", query.relations[0].name.c_str());
    ASSERT_STREQ("profs", query.relations[0].binding.c_str());
    
    ASSERT_STREQ("schema", query.relations[1].name.c_str());
    ASSERT_STREQ("s", query.relations[1].binding.c_str());
}

// --- WHERE

TEST(ParserTest, TestWhereCondition) {
    Query query = Parser::parse(string("SELECT \'foo\' FROM table t WHERE t.id = s.idx"));
    
    ASSERT_EQ(query.join_conditions.size(), 1);
    
    ASSERT_STREQ("t", query.join_conditions[0].left.binding.c_str());
    ASSERT_STREQ("id", query.join_conditions[0].left.name.c_str());
    ASSERT_STREQ("s", query.join_conditions[0].rightAttribute.binding.c_str());
    ASSERT_STREQ("idx", query.join_conditions[0].rightAttribute.name.c_str());
}

TEST(ParserTest, TestWhereConditionConstant) {
    Query query = Parser::parse(string("SELECT \'foo\' FROM table t WHERE t.id = 'foo'"));
    
    ASSERT_EQ(query.join_conditions.size(), 1);
    
    ASSERT_STREQ("t", query.join_conditions[0].left.binding.c_str());
    ASSERT_STREQ("id", query.join_conditions[0].left.name.c_str());
    ASSERT_STREQ("foo", query.join_conditions[0].rightConstant.string_value.c_str());
}
