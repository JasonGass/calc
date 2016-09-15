CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++0x 

all: 
	$(CXX) $(CPPFLAGS) -o ./calculator ./lib/Expression.cpp ./lib/Calculator.cpp ./ui/wxWidgets/gui.cpp `wx-config --libs` `wx-config --cxxflags`

tests: 
	$(CXX) $(CPPFLAGS) -o ./bin/expressionTester ./lib/Expression.cpp ./test/ExpressionTester.cpp
	$(CXX) $(CPPFLAGS) -o ./bin/calculatorTester lib/Expression.H lib/Expression.cpp ./lib/Calculator.cpp ./test/CalculatorTester.cpp
    
clean:
	$(RM) ./bin/* 

