#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <cmath>

using std::cerr;
using std::cout;
using std::endl;

class Calc
{
public:
    double binary_operator(double operand_one, double operand_two, char bin_operator);
    double unary_operator(double operand, char una_operator);
private:

};

#endif