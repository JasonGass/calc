#include <iostream>
#include <string>
#include "../lib/Calculator.H"

using namespace std;

struct Test
{
    std::string expression;
    int base;    
    std::string expressionBase02;  
    std::string expressionBase08;  
    std::string expressionBase10;  
    std::string expressionBase16;  
    std::string answerBase02;  
    std::string answerBase08;  
    std::string answerBase10;  
    std::string answerBase16;  
};

bool compareStrings(std::string str1, std::string str2)
{
    if (str1 != str2)
    {
        cout<<"|"<<str1<<"|"<< " != " <<"|"<<str2<<"|"<<endl;
        return false;
    }
        return true;
}

bool runTest(Test test)
{
    cout<<"Testing: "<<test.expression<< " Base: "<<test.base<<endl;
    std::vector<int> bases;
    bases.push_back(2);
    bases.push_back(8);
    bases.push_back(10);
    bases.push_back(16);
    Calculator calc(bases);
    bool result = true;

    calc.updateDisplays(test.expression, test.base);
    result &= compareStrings(calc.getDisplayText(2), test.expressionBase02);   
    result &= compareStrings(calc.getDisplayText(8), test.expressionBase08) ;  
    result &= compareStrings(calc.getDisplayText(10), test.expressionBase10);   
    result &= compareStrings(calc.getDisplayText(16), test.expressionBase16);   
    calc.toggleAnswerDisplay();
    result &= compareStrings(calc.getDisplayText(2), test.answerBase02);   
    result &= compareStrings(calc.getDisplayText(8), test.answerBase08) ;  
    result &= compareStrings(calc.getDisplayText(10), test.answerBase10) ;  
    result &= compareStrings(calc.getDisplayText(16), test.answerBase16)  ; 
    if (result) {
        cout<<"PASSED!"<<endl;
        return true;
    }
        cout<<"FAILED!"<<endl<<endl;
    return false;
}

int main() 
{
    Test test;
    int failedTests = 0;
    test.expression = "";
    test.base = 2;
    test.expressionBase02 = "";
    test.expressionBase08 = "";
    test.expressionBase10 = "";
    test.expressionBase16 = "";
    test.answerBase02 = "";
    test.answerBase08 = "";
    test.answerBase10 = "";
    test.answerBase16 = "";
    if (!runTest(test)) {failedTests++;}

    test.expression = "32";
    test.base = 10;
    test.expressionBase02 = "100000";
    test.expressionBase08 = "40";
    test.expressionBase10 = "32";
    test.expressionBase16 = "20";
    test.answerBase02 = "100000";
    test.answerBase08 = "40";
    test.answerBase10 = "32";
    test.answerBase16 = "20";
    if (!runTest(test)) {failedTests++;}

    test.expression = "A-A";
    test.base = 16;
    test.expressionBase02 = "1010-1010";
    test.expressionBase08 = "12-12";
    test.expressionBase10 = "10-10";
    test.expressionBase16 = "A-A";
    test.answerBase02 = "0";
    test.answerBase08 = "0";
    test.answerBase10 = "0";
    test.answerBase16 = "0";
    if (!runTest(test)) {failedTests++;}

    test.expression = "-a.a";
    test.base = 16;
    test.expressionBase02 = "-1010.101";
    test.expressionBase08 = "-12.5";
    test.expressionBase10 = "-10.625";
    test.expressionBase16 = "-A.A";
    test.answerBase02 = "-1010.101";
    test.answerBase08 = "-12.5";
    test.answerBase10 = "-10.625";
    test.answerBase16 = "-A.A";
    if (!runTest(test)) {failedTests++;}

    test.expression = "-5+((1+2)*4)-3";
    test.base = 10;
    test.expressionBase02 = "-101+((1+10)*100)-11";
    test.expressionBase08 = "-5+((1+2)*4)-3";
    test.expressionBase10 = "-5+((1+2)*4)-3";
    test.expressionBase16 = "-5+((1+2)*4)-3";
    test.answerBase02 = "100";
    test.answerBase08 = "4";
    test.answerBase10 = "4";
    test.answerBase16 = "4";
    if (!runTest(test)) {failedTests++;}
    
    cout<<failedTests<< " Tests Failed"<<std::endl;
    return 0;
}




