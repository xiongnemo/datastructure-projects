#include "calc.h"

double Calc::binary_operator(double operand_one, double operand_two, char bin_operator)
{
    switch (bin_operator)
    {
    case '+':
        return operand_one + operand_two;
    case '-':
        return operand_one - operand_two;
    case '*':
        return operand_one * operand_two;
    case '/':
        if (operand_two == 0)
        {
            cerr << "Error in processing /: operand two is 0" << endl;
            return -1;
        }
        return operand_one / operand_two;
    case '%':
        if (operand_two == 0)
        {
            cerr << "Error in processing %: operand two is 0" << endl;
            return -1;
        }
        if (fabs(operand_one - floor(operand_one)) > 0.000000001 || fabs(operand_two - floor(operand_two)) > 0.000000001)
        {
            cerr << "Error in processing %: one of the two operands is not a int" << endl;
            cerr << operand_one << " % " << operand_two << endl;
            return -2;
        }
        unsigned long long int temp_operator_one, temp_operator_two;
        temp_operator_one = operand_one;
        temp_operator_two = operand_two;
        return temp_operator_one % temp_operator_two;
    case '^':
        return pow(operand_one, operand_two);
    default:
        cerr << "Unsupported binary operator!" << endl;
        return 114514;
    }
}

double Calc::unary_operator(double operand, char una_operator)
{
    switch (una_operator)
    {
    case '+':
        return operand;
    case '-':
        return -operand;
    default:
        cerr << "Unsupported unary operator!" << endl;
        return 114514;
    }
}