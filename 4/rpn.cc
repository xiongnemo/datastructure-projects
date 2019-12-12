#include "rpn.h"
#include "calc.h"
#include "helper.h"

using helper::calc_decimal_digits;
using std::cerr;

bool Rpn::pre_processer(char *infix_orig, char *result, int *result_length)
{
    int length = strlen(infix_orig);
    int temp_result_length = 0;
    char temp_char;
    int open_parentheses_count = 0;
    char mid_result[BUFFER_SIZE];

    // Judge whether the original expression is ended in '='
    if (infix_orig[length - 1] != '=')
    {
        cerr << "Missing '=' in original infix expression." << endl;
        return false;
    }

    // remove extra whitespaces in the expression
    for (int i = 0; i < length; i++)
    {
        temp_char = infix_orig[i];
        if (temp_char == ' ')
            continue;
        else
        {
            mid_result[temp_result_length] = temp_char;
            temp_result_length++;
        }
    }

    // convert unary operator '+' and '-' into binary forms
    // do some syntax checking
    length = temp_result_length;
    temp_result_length = 0;
    for (int i = 0; i < length; i++)
    {
        temp_char = mid_result[i];
        switch (temp_char)
        {
        case '+':
            if (check_legal_operator(&mid_result[i], 3, 0))
            {
                cerr << "Three trailing operators appeared in original infix expression." << endl;
                return false;
            }
            if ((i == 0) || (i > 0 && mid_result[i - 1] == '('))
            {
                continue;
            }
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        case '-':
            if (check_legal_operator(&mid_result[i], 3, 0))
            {
                cerr << "Three trailing operators appeared in original infix expression." << endl;
                return false;
            }
            if ((i == 0) || (i > 0 && check_legal_operator(&mid_result[i - 1], 1, 1)))
            {
                // convert unary operator '-' into binary operator '-'
                double temp = atof(&mid_result[i + 1]);
                sprintf(&result[temp_result_length], "(0-%lf)", temp);
                temp_result_length += (4 + calc_decimal_digits(&result[temp_result_length + 4]) + 1);
                i += calc_decimal_digits(&mid_result[i + 1]);
            }
            else
            {
                result[temp_result_length] = temp_char;
                temp_result_length++;
            }
            break;
        case '*':
        case '/':
        case '%':
        case '^':
            if (check_legal_operator(&mid_result[i], 2, 0))
            {
                cerr << "Two trailing operators appeared in original infix expression." << endl;
                return false;
            }
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        // semicolons should match
        case '(':
            open_parentheses_count++;
            break;
        case ')':
            open_parentheses_count--;
            break;
        // other operators and operands
        // just passing
        case '=':
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        default:
            cerr << "Unsupported or illegal character(s) appeared in original infix expression." << endl;
            return false;
        }
    }
    if (open_parentheses_count)
    {
        if (open_parentheses_count > 0)
        {
            cerr << "Open parentheses found!" << endl;
        }
        else
        {
            cerr << "Extra parentheses found!" << endl;
        }
        return false;
    }
    result[temp_result_length] = '\0';
    *result_length = temp_result_length;
    return true;
}

bool Rpn::infix2rpn(char *infix, char *result)
{
    int infix_length = strlen(infix);
    int temp_result_length = 0;
    double temp = 0;
    operator_stack.make_empty();
    for (int i = 0; i < infix_length; i++)
    {
        char temp_char = infix[i];
        switch (temp_char)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            if (!operator_stack.empty())
            {
                // if current operator's priority is bigger or equal than the one on stack top
                // pop until it's less than current
                while (order_between_operator(temp_char, operator_stack.top()) >= 0)
                {
                    result[temp_result_length] = operator_stack.pop();
                    result[temp_result_length + 1] = ' ';
                    temp_result_length += 2;
                    if (operator_stack.empty())
                    {
                        break;
                    }
                }
            }
            // push current operator onto stack
            operator_stack.push(temp_char);
            break;
        case '=':
            break;
        case '(':
            operator_stack.push(temp_char);
            break;
        case ')':
            // pop operators until '(' appears on the top
            while (operator_stack.top() != '(')
            {
                result[temp_result_length] = operator_stack.pop();
                result[temp_result_length + 1] = ' ';
                temp_result_length += 2;
            }
            operator_stack.pop(); // make sure to pop '('
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // append operand to the back
            temp = atof(&infix[i]);
            sprintf(&result[temp_result_length], "%lf ", temp);
            temp_result_length += (1 + calc_decimal_digits(&result[temp_result_length]));
            i += calc_decimal_digits(&infix[i]) - 1;
            break;
        default:
            cerr << "Unsupported or illegal character(s) appeared in processed infix expression." << endl;
            return false;
        }
    }
    // pop remaining operators
    while (!operator_stack.empty())
    {
        result[temp_result_length] = operator_stack.pop();
        result[temp_result_length + 1] = ' ';
        temp_result_length += 2;
    }
    result[temp_result_length] = '\0';
    return true;
}

bool Rpn::eval_rpn(char *rpn)
{
    int rpn_length = strlen(rpn);
    operand_stack.make_empty();
    for (int i = 0; i < rpn_length;)
    {
        char temp_char = rpn[i];
        switch (temp_char)
        {
        case '=':
        case ' ':
            i++;
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            // when it meets operator character, we pop two elements from the stack, cacluate the result, push back onto stack
            operand_stack.push(eval.binary_operator(operand_stack.pop(), operand_stack.pop(), temp_char));
            i = i + 2;
            break;
        default:
            // push operand onto stack
            operand_stack.push(atof(&rpn[i]));
            i += calc_decimal_digits(&rpn[i]) + 1;
        }
    }
    // after all evaluation process complete, there should be only one element in the stack, which is the result
    if (operand_stack.size() != 1)
    {
        cerr << "Syntax error(s) occured in evaluating rpn." << endl;
        return false;
    }
    result = operand_stack.top();
    return true;
}

int Rpn::order_between_operator(char operator_one, char operator_two)
{
    // priority order between operators
    return (priority[static_cast<int>(operator_two)] - priority[static_cast<int>(operator_one)]);
}

// mode 0 don't include '('
// mode 1 include '('
bool Rpn::check_legal_operator(char *target, int num, int mode)
{
    int count = 0;
    int num_operators = (N_ACTURAL_OPERATOR + mode);
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num_operators; j++)
        {
            if (target[i] == vaild_operators[j])
            {
                count++;
                break;
            }
        }
    }
    return (!(num - count));
}