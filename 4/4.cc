#include "rpn.h"

void stack_test();
void rpn_preprocesser_test();
void infix2rpn_test();
void rpn_eval_test();

int main()
{
    Rpn rpn_processor;
    char raw_data[BUFFER_SIZE];
    char infix_data[BUFFER_SIZE];
    char rpn_data[BUFFER_SIZE];
    int infix_length = 0;
    int* infix_length_pointer = &infix_length;
    cin.getline(raw_data, BUFFER_SIZE);
    rpn_processor.pre_processer(raw_data, infix_data, infix_length_pointer);
    cout << "The preprocessor result is: " << infix_data << endl;
    rpn_processor.infix2rpn(infix_data, rpn_data);
    cout << "The rpn result is: " << rpn_data << endl;
    cout << "The result is: " << rpn_processor.eval_rpn(rpn_data) << endl;
}

void stack_test()
{
    StackForInt test_stack;
    cout << test_stack.empty() << endl;
    test_stack.push(5);
    test_stack.push(3);
    cout << test_stack.pop() << endl;
    test_stack.push(7);
    test_stack.push(3);
    cout << test_stack.top() << endl;
    cout << test_stack.empty() << endl;
    test_stack.push(11);
    cout << test_stack.size() << endl;
    test_stack.push(6);
    cout << test_stack.empty() << endl;
    test_stack.push(7);
    cout << test_stack.pop() << endl;
    cout << test_stack.pop() << endl;
    cout << test_stack.top() << endl;
    cout << test_stack.size() << endl;
}

void rpn_preprocesser_test()
{
    cout << "This is a test for the infix preprocessor." << endl;
    cout << "Please enter the original infix expression." << endl;
    Rpn rpn_processor;
    char raw_data[BUFFER_SIZE];
    char infix_data[BUFFER_SIZE];
    int infix_length = 0;
    int* infix_length_pointer = &infix_length;

    cin.getline(raw_data, BUFFER_SIZE);
    rpn_processor.pre_processer(raw_data, infix_data, infix_length_pointer);
    cout << "The result is: " << infix_data << endl;
}

void infix2rpn_test()
{
    cout << "This is a test for the process of infix to rpn." << endl;
    cout << "Please enter the processed infix expression." << endl;
    Rpn rpn_processor;
    char infix_data[BUFFER_SIZE];
    char rpn_data[BUFFER_SIZE];
    cin.getline(infix_data, BUFFER_SIZE, '\n');
    rpn_processor.infix2rpn(infix_data, rpn_data);
    cout << "The result is: " << rpn_data << endl;
}

void rpn_eval_test()
{
    cout << "This is a test for the eval of rpn." << endl;
    cout << "Please enter the rpn expression." << endl;
    Rpn rpn_processor;
    char rpn_data[BUFFER_SIZE];
    cin.getline(rpn_data, BUFFER_SIZE, '\n');
    cout << "The result is: " << rpn_processor.eval_rpn(rpn_data) << endl;
}


