#include <string>
#include <vector>
#include "Expression.H"

struct CalcDisplay 
{
    int base;
    std::string text;
};

enum States
{
    ValidExpression,
    InvalidExpression,
    DisplayingAnswer
};

class Calculator 
{
    public: 
        Calculator(std::vector<int> bases);
        void updateDisplays(std::string str, int base);
        std::string getDisplayText(int base);
        void toggleAnswerDisplay();
        
    private: 
        Expression* expression;
        States state;
        std::vector<CalcDisplay*> displays;
};
