#include "stack.h"

bool StackForInt::empty()
{
    if (stack_pointer == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int StackForInt::push(int new_element)
{
    if (stack_pointer >= BUFFER_SIZE)
    {
        cout << "Limit reached. Won't push." << endl;
    }
    else
    {
        stack[stack_pointer] = new_element;
        stack_pointer++;
    }
    return new_element;
}

int StackForInt::pop()
{
    int temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing to pop." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
        stack_pointer--;
    }
    return temp;
}

int StackForInt::top()
{
    int temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing on the top." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
    }
    return temp;
}

int StackForInt::size()
{
    return stack_pointer;
}

void StackForInt::print()
{
    for (int i = 0; i < stack_pointer; i++)
    {
        cout << stack[i] << " " ;
    }
    cout << endl;
}

void StackForInt::make_empty()
{
    stack_pointer = 0;
}

bool StackForChar::empty()
{
    if (stack_pointer == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char StackForChar::push(char new_element)
{
   if (stack_pointer >= BUFFER_SIZE)
    {
        cout << "Limit reached. Won't push." << endl;
    }
    else
    {
        stack[stack_pointer] = new_element;
        stack_pointer++;
    }
    return new_element;
}

char StackForChar::pop()
{
    char temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing to pop." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
        stack_pointer--;
    }
    return temp;
}

char StackForChar::top()
{
    char temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing on the top." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
    }
    return temp;
}

int StackForChar::size()
{
    return stack_pointer;
}

void StackForChar::print()
{
    for (int i = 0; i < stack_pointer; i++)
    {
        cout << stack[i] << " " ;
    }
    cout << endl;
}

void StackForChar::make_empty()
{
    stack_pointer = 0;
}

bool StackForDouble::empty()
{
    if (stack_pointer == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double StackForDouble::push(double new_element)
{
    if (stack_pointer >= BUFFER_SIZE)
    {
        cout << "Limit reached. Won't push." << endl;
    }
    else
    {
        stack[stack_pointer] = new_element;
        stack_pointer++;
    }
    return new_element;
}

double StackForDouble::pop()
{
    double temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing to pop." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
        stack_pointer--;
    }
    return temp;
}

double StackForDouble::top()
{
    double temp;
    if (stack_pointer == 0)
    {
        cout << "Stack is empty. Nothing on the top." << endl;
    }
    else
    {
        temp = stack[stack_pointer - 1];
    }
    return temp;
}

int StackForDouble::size()
{
    return stack_pointer;
}

void StackForDouble::print()
{
    for (int i = 0; i < stack_pointer; i++)
    {
        cout << stack[i] << " " ;
    }
    cout << endl;
}

void StackForDouble::make_empty()
{
    stack_pointer = 0;
}