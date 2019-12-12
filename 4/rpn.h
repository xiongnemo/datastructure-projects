#ifndef RPN_H
#define RPN_H

#include "stack.h"
#include "calc.h"
#include <cstring>

// total amount of current supported operators
// + - * / % ^ ! ( ) '\0'
#define N_OPERATOR 10
#define N_ACTURAL_OPERATOR 6

class Rpn
{
public:
    Rpn()
    {
        priority['+'] = 1;
        priority['-'] = 1;
        priority['*'] = 2;
        priority['/'] = 2;
        priority['%'] = 2;
        priority['^'] = 3;
        result = 0;
    }
    Calc eval;
    StackForDouble operand_stack;
    StackForChar operator_stack;
    bool pre_processer(char *infix_orig, char *result, int *result_length);
    bool infix2rpn(char *infix, char *result);
    bool eval_rpn(char *rpn);
    double result;
private:
    int order_between_operator(char operator_one, char operator_two);
    bool check_legal_operator(char* target, int num, int mode);
    char priority[100] = {0}; 
    const char vaild_operators[10] = {'+', '-', '*', '/', '%', '^', '(', '!', ')', '='};
};// namespace Rpn

#endif