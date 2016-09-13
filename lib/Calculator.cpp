#include <iostream>
#include "Calculator.H"

Calculator::Calculator(std::vector<int> bases) 
{
    expression = new Expression("",10);
    state = ValidExpression;
    CalcDisplay *newDisplay;
    for (int i =0; i < bases.size(); i++)
    {
        newDisplay = new CalcDisplay;
        newDisplay->base = bases[i];
        displays.push_back(newDisplay);
    }
    updateDisplays("",10);
}

void Calculator::updateDisplays(std::string str, int base)
{
    state = ValidExpression;  

    delete expression;
    expression = new Expression(str, base);
    for (int i =0; i< displays.size(); i++)
    {
        displays[i]->text = expression->toString(displays[i]->base);
    }
}

void Calculator::toggleAnswerDisplay()
{
    if (state == DisplayingAnswer)
    {   
        for (int i = 0; i < displays.size(); i++)
        {
            displays[i]->text = expression->toString(displays[i]->base);         
        }
        state = ValidExpression;
        return;
    }    
    else
    {;
        try 
        {
            Expression answer = expression->solve(); //Check if null first
            for (int i = 0; i < displays.size(); i++)
            {
                displays[i]->text = answer.toString(displays[i]->base);         
            }
        }
        catch (const std::invalid_argument &ex)
        {
            std::cout<<ex.what()<<std::endl;
            state = InvalidExpression;      
            return;
        }
        state = DisplayingAnswer;
        return;

    }
}

std::string Calculator::getDisplayText(int base)
{
    for (int i = 0; i<displays.size(); i++)
    {
        if (displays[i]->base == base)
        {
            return displays[i]->text;
        }
    }
    return "";
}
