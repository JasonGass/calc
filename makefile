CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++0x 

default: test

test: ./test/ExpressionTester.cpp ./lib/Expression.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/expressionTester ./lib/Expression.cpp ./test/ExpressionTester.cpp
    
clean:
	$(RM) ./bin/* 

