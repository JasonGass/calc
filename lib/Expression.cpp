#include <stack>
#include <string>
#include <iostream>
#include <cmath>
#include "Expression.H"

int toNumber(char c) 
{
    if (c >= '0' && c <= '9')
    {
        return (int) c-'0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return (int) c-'A'+10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return (int) c-'a'+10;
    }
}
//Possibly refactor this into its own class for easier testing????
long double strToValue(std::string number, int base)
{
    std::size_t found = number.find('.');        
    if (found == std::string::npos)
    {
       found = number.length(); 
    } 
    long double value=0;
    for (std::size_t x = 0; x<number.length(); x++)
    {
        int power =0;
        if( x < found)
        {
            power = found-x-1; 
        }
        else if (x == found)
        {
            continue;       
        }
        else if (x > found)
        {
            power = found - x;
        }
        value += std::pow(base, power) * toNumber(number[x]);
    } 
    return value;    
}

Expression::Expression(std::string expression, int base)
{
    while (expression.length() > 0) 
    {
        std::string number="";
        int i =0;
        for ( i = 0; i < expression.length(); i++)
        {
            if (expression[i] == Operator::Addition ||
                expression[i] == Operator::Subtraction ||           
                expression[i] == Operator::Multiplication ||           
                expression[i] == Operator::Division ||           
                expression[i] == Operator::LeftParentheses ||           
                expression[i] == Operator::RightParentheses )
            break;    
            
        }
        if (i != 0) 
        {
            tokens.push_back(new Operand(strToValue(expression.substr(0,i), base)));
        }
        if( i < expression.length())
        {
            tokens.push_back(new Operator((Operator::Operators) expression[i]));
            i++;
        }
        expression = expression.substr(i);
    }
    
    if (tokens.size() > 1 && tokens[0]->isOperator() && tokens[1]->isOperand())
    {
        Operator* op = (Operator*) tokens[0];
        Operand* num = (Operand*) tokens[1];

        if (*op == Operator::Addition)
        {       
            tokens.erase(tokens.begin());
        }   
        else if (*op == Operator::Subtraction)
        {       
            num->value *= -1;
            tokens.erase(tokens.begin());
        }   
    }
    for (int i = 0; i < (int)tokens.size()-2; i++) 
    {
        if (tokens[i]->isOperator() && tokens[i+1]->isOperator() && tokens[i+2]->isOperand()
            && (*((Operator*)tokens[i]) != Operator::RightParentheses))
        {
            Operator* op = (Operator*) tokens[i+1];
            Operand* num = (Operand*) tokens[i+2];
            if (*op == Operator::Addition)
            {       
                tokens.erase(tokens.begin()+i+1);
            }   
            else if (*op == Operator::Subtraction)
            {       
                num->value *= -1;
                tokens.erase(tokens.begin()+i+1);
            }   
        } 
    }
}

std::string Expression::toString(int base)
{
    std::string result = "";
    for (int i=0; i<tokens.size(); i++)
    {
        result+=tokens[i]->toString(base) + "";
    }
    return result;
}

void solveOp(Operator* op, std::stack<Operand*> &numStack)
{
    if (numStack.size() < op->numOfOperands)
    {
        throw std::invalid_argument("Not enough operands");
    }
    std::vector<long double> operands;
    for (int i = 0; i < op->numOfOperands; i++) 
    {
        operands.push_back(numStack.top()->value);
        numStack.pop();
    }
    numStack.push(new Operand(op->solve(operands)));
}

void solveLowerPrecedenceOps(std::stack<Operator*> &opStack, std::stack<Operand*> &numStack, Operator::Precedences precedence, Operator::Associativity associativity)
{
    while(!opStack.empty() && 
         (opStack.top()->precedence < precedence || 
         (opStack.top()->precedence == precedence && 
          associativity == Operator::Left)))
    {
        solveOp(opStack.top(), numStack);
        opStack.pop();
    }
}

Expression Expression::solve()
{
    Expression answer("",10);
    std::stack<Operator*> opStack;
    std::stack<Operand*>  numStack;    
    for(int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i]->isOperand())
        {
            numStack.push((Operand*) tokens[i]);
        }   
        if (tokens[i]->isOperator())
        {
            Operator* op = (Operator*) tokens[i];
            if (*op == Operator::LeftParentheses)
            {
                opStack.push(op);
            }
            else if (*op == Operator::RightParentheses)
            {
                solveLowerPrecedenceOps(opStack, numStack, Operator::ParenthesesPrecedence, Operator::Right);
                opStack.pop();
            }
            else
            {
                solveLowerPrecedenceOps(opStack, numStack, op->precedence, op->associativity);
                opStack.push(op);
            }
        }
    }
    solveLowerPrecedenceOps(opStack, numStack, Operator::MaxPrecedence, Operator::Left);
    if(numStack.size() > 1 ) 
    {
        throw std::invalid_argument("Too many answers");
    }
    if(numStack.size() == 1 ) 
    {
        answer.tokens.push_back(new Operand(numStack.top()->value));
    }
    return answer;
}










