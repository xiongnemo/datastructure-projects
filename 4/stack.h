#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdio>

#define BUFFER_SIZE 1024

using std::cin;
using std::cout;
using std::endl;

class StackForInt
{
public:
    StackForInt()
    {
        stack_pointer = 0;
    }
    bool empty();
    int push(int new_element);
    int pop();
    int top();
    int size();
    void print();
    void make_empty();

private:
    int stack_pointer;
    int stack[BUFFER_SIZE + 2];
};

class StackForChar
{
public:
    StackForChar()
    {
        stack_pointer = 0;
    }
    bool empty();
    char push(char new_element);
    char pop();
    char top();
    int size();
    void print();
    void make_empty();

private:
    int stack_pointer;
    char stack[BUFFER_SIZE + 2];
};

class StackForDouble
{
public:
    StackForDouble()
    {
        stack_pointer = 0;
    }
    bool empty();
    double push(double new_element);
    double pop();
    double top();
    int size();
    void print();
    void make_empty();

private:
    int stack_pointer;
    double stack[BUFFER_SIZE + 2];
};


#endif