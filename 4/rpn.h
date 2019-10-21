#ifndef RPN_H
#define RPN_H

#include "stack.h"
#include "calc.h"
#include <cstring>

// total amount of current supported operators
// + - * / % ^ ! ( ) '\0'
#define N_OPERATOR 10

#define N_ACTURAL_OPERATOR 6

namespace test
{
enum OperatorType
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    POW,
    FAC,
    L_P,
    R_P,
    EQU
};
}


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
    }
    Calc eval;
    StackForInt operand_stack_temp;
    StackForDouble operand_stack;
    StackForChar operator_stack;
    int pre_processer(char *infix_orig, char *result, int *result_length);
    bool infix2rpn(char *infix, char *result);
    double eval_rpn(char *rpn);
    int order_between_operator(char operator_one, char operator_two);

private:
    char priority[100] = {0};
    const char vaild_operators[10] = {'+', '-', '*', '/', '%', '^', '!', '(', ')', '='};
};

#endif