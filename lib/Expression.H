#include<string>
#include<vector>
#include<stdexcept>

struct Token 
{
    virtual std::string toString(int base) 
    {
        throw std::invalid_argument("toString should be inherited from Token");
    }
    virtual bool isOperand() { return false; }    
    virtual bool isOperator() { return false; }    
};

static char singleChar[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
struct Operand : Token
{   
    long double value;
    Operand(long double value)
    {
        this->value = value;
    }
    std::string toString(int base)
    {
        int wholeNum = (int) value;
        double fraction = value - wholeNum;
        std::string result = "";

        bool isNegative = value < 0;
        if (isNegative) { wholeNum*=-1; fraction*=-1;}
        
        if ( wholeNum == 0)
        {
            result = "0";
        }
        while(wholeNum > 0)
        {
            result = singleChar[wholeNum % base] + result;
            wholeNum/=base;
        }

        int precision = 0;
        if (fraction > 0) 
        {
            result += ".";
        }
        
        while (fraction > 0 && precision < 9)
        {
            fraction*=base;
            result += singleChar[(int) fraction];
            fraction = (double) fraction - (int) fraction;
            precision++; 
        }

        if (isNegative) {result = "-"+result;}
        return result;
    }
    bool isOperand() { return true; }    
};

struct Operator : Token
{
    enum Operators 
    {
        Addition = '+',
        Subtraction = '-',
        Multiplication = '*',
        Division = '/',
        LeftParentheses = '(',
        RightParentheses = ')',
    };
    enum Precedences
    {
        AdditionSubtractionPrecedence = 2,
        MultiplicationDivisionPrecedence = 1,
        ParenthesesPrecedence = 254,
        MaxPrecedence = 255,
    };
    Precedences precedence;
    Operators op;
    int numOfOperands;
    
    Operator(Operators op) 
    {
        this->op = op;
        switch (this->op)   
        {
            case Addition: 
                precedence = AdditionSubtractionPrecedence;
                numOfOperands=2;
                break;

            case Subtraction: 
                precedence = AdditionSubtractionPrecedence;
                numOfOperands=2;
                break;

            case Multiplication: 
                precedence = MultiplicationDivisionPrecedence;
                numOfOperands=2;
                break;

            case Division: 
                precedence = MultiplicationDivisionPrecedence;
                numOfOperands=2;
                break;

            case LeftParentheses: 
                precedence = ParenthesesPrecedence;
                numOfOperands=0;
                break;

            case RightParentheses: 
                precedence = ParenthesesPrecedence;
                numOfOperands=0;
                break;

            default:
                throw std::invalid_argument("Unrecognized Op");
        }
    }
    long double solve(std::vector<long double> operands)
    {
        if (operands.size() != numOfOperands) 
        {
            throw std::invalid_argument("Wrong number of operands");
        }
        switch (op)   
        {
            case Addition: 
                return operands[1]+operands[0];
                break;

            case Subtraction: 
                return operands[1]-operands[0];
                break;

            case Multiplication: 
                return operands[1]*operands[0];
                break;

            case Division: 
                return operands[1]/operands[0];
                break;

            default:
                throw std::invalid_argument("Can't solve this operator");
        }
        
    }
    std::string toString(int base) 
    {
        return std::string(1,((char) op));    
    }
    bool operator==(const Operators op) {return this->op == op;}
    bool operator!=(const Operators op) {return this->op != op;}
    bool isOperator() { return true; }    
};

class Expression 
{
    public: 
        Expression(std::string expression, int base);
        std::string toString(int base);
        Expression solve();
    private:
        std::vector<Token*> tokens;
};
