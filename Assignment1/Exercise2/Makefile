SRC=Exercise1
OBJS = Parser.o Constant.o Attribute.o Query.o Relation.o Selection.o JoinCondition.o
TEST_OBJS = gtest-all.o gtest_main.o Parser_Test.o

CFLAGS = -Wall -c $(DEBUG) -Igtest-1.7.0/include -Igtest-1.7.0
LFLAGS = -Wall $(DEBUG)
CC = g++
DEBUG = -g

all: $(OBJS) main.o
	$(CC) $(LFLAGS) $(OBJS) main.o
    
test: $(OBJS) $(TEST_OBJS)
	$(CC) $(LFLAGS) $(OBJS) $(TEST_OBJS) -o exercise1_test.out
    
clean:
	rm -rf ./*.o
	rm a.out
	rm extercise1_test

main.o:
	$(CC) $(CFLAGS) $(SRC)/main.cpp
    
gtest-all.o:
	$(CC) $(CFLAGS) $(SRC)/gtest-all.cc
    
gtest_main.o:
	$(CC) $(CFLAGS) $(SRC)/gtest_main.cc
    
Parser_Test.o:
	$(CC) $(CFLAGS) $(SRC)/Parser_Test.cpp

Parser.o:
	$(CC) $(CFLAGS) $(SRC)/Parser.cpp
    
Constant.o:
	$(CC) $(CFLAGS) $(SRC)/Constant.cpp
    
Attribute.o:
	$(CC) $(CFLAGS) $(SRC)/Attribute.cpp
    
Query.o:
	$(CC) $(CFLAGS) $(SRC)/Query.cpp
    
Relation.o:
	$(CC) $(CFLAGS) $(SRC)/Relation.cpp
    
Selection.o:
	$(CC) $(CFLAGS) $(SRC)/Selection.cpp
    
JoinCondition.o:
	$(CC) $(CFLAGS) $(SRC)/JoinCondition.cpp