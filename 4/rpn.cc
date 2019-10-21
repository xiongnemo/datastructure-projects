#include "rpn.h"
#include "calc.h"
#include "helper.h"

using std::cerr;
using test::OperatorType;
using helper::calc_decimal_digits;

int Rpn::pre_processer(char *infix_orig, char *result, int *result_length)
{
    int length = strlen(infix_orig);
    int temp_result_length = 0;
    char temp_char;
    char mid_result[BUFFER_SIZE];
    if (infix_orig[length - 1] != '=')
    {
        cerr << "Missing '=' in original infix expression." << endl;
        return -4;
    }
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

    length = temp_result_length;
    temp_result_length = 0;
    for (int i = 0; i < length; i++)
    {
        temp_char = mid_result[i];
        switch (temp_char)
        {
        case '+':
            for (int j = 0; j <= N_ACTURAL_OPERATOR; j++)
            {
                if (mid_result[i + 1] == vaild_operators[j])
                {
                    for (int k = 0; k <= N_ACTURAL_OPERATOR; k++)
                    {
                        if (mid_result[i + 2] == vaild_operators[k])
                        {
                            cerr << "Three trailing operators appeared!" << endl;
                            return -5;
                        }
                    }
                }
            }
            if ((i == 0) || (i > 0 && mid_result[i - 1] == '('))
            {
                continue;
            }
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        case '-':
            for (int j = 0; j <= N_ACTURAL_OPERATOR; j++)
            {
                if (mid_result[i + 1] == vaild_operators[j])
                {
                    for (int k = 0; k <= N_ACTURAL_OPERATOR; k++)
                    {
                        if (mid_result[i + 2] == vaild_operators[k])
                        {
                            cerr << "Three trailing operators appeared!" << endl;
                            return -5;
                        }
                    }
                }
            }
            if ((i == 0) || (i > 0 && ((mid_result[i - 1] == '(') || (mid_result[i - 1] == '+') || (mid_result[i - 1] == '-') || (mid_result[i - 1] == '*') || (mid_result[i - 1] == '/') || (mid_result[i - 1] == '%') || (mid_result[i - 1] == '^'))))
            {
                double temp = atof(&mid_result[i + 1]);
                sprintf(&result[temp_result_length], "(0-%lf)", temp);
                temp_result_length += (4 + calc_decimal_digits(&result[temp_result_length]));
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
        for (int j = 0; j <= N_ACTURAL_OPERATOR; j++)
            {
                if (mid_result[i + 1] == vaild_operators[j])
                {
                    cerr << "Two trailing operators appeared!" << endl;
                    return -6;
                }
            }
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        case '=':
        case '.':
        case '(':
        case ')':
            result[temp_result_length] = temp_char;
            temp_result_length++;
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
            result[temp_result_length] = temp_char;
            temp_result_length++;
            break;
        default:
            cerr << "Unsupported character appeared in infix!" << endl;
            return -3;
        }
    }
    result[temp_result_length] = '\0';
    *result_length = temp_result_length;
    return 0;
}

bool Rpn::infix2rpn(char *infix, char *result)
{
    int infix_length = strlen(infix);
    int temp_result_length = 0;
    double temp = 0;
    operator_stack.make_empty();
    //operand_stack_temp.make_empty();
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
            operator_stack.push(temp_char);
            break;
        case '=':
            break;
        case '(':
            operator_stack.push(temp_char);
            break;
        case ')':
            while (operator_stack.top() != '(')
            {
                result[temp_result_length] = operator_stack.pop();
                result[temp_result_length + 1] = ' ';
                temp_result_length += 2;
            }
            operator_stack.pop(); // pop '('
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
            temp = atof(&infix[i]);
            sprintf(&result[temp_result_length], "%lf ", temp);
            temp_result_length += (1 + calc_decimal_digits(&result[temp_result_length]));
            i += calc_decimal_digits(&infix[i]) - 1;
            break;
        default:
            cerr << "Unsupported character appeared in infix!" << endl;
            return -3;
        }
    }
    while (!operator_stack.empty())
    {
        result[temp_result_length] = operator_stack.pop();
        result[temp_result_length + 1] = ' ';
        temp_result_length += 2;
    }

    result[temp_result_length] = '\0';
    return true;
}

double Rpn::eval_rpn(char *rpn)
{
    int rpn_length = strlen(rpn);
    operator_stack.make_empty();
    operand_stack.make_empty();
    for (int i = 0; i < rpn_length;)
    {
        char temp_char = rpn[i];
        /*
        if (i == 0 || i == 1)
        {
            operand_stack.push(temp_char - 48);
            continue;
        }
        */
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
            operand_stack.push(eval.binary_operator(operand_stack.pop(), operand_stack.pop(), temp_char));
            i = i + 2;
            //operand_stack.print();
            break;
        default:
            operand_stack.push(atof(&rpn[i]));
            i += calc_decimal_digits(&rpn[i]) + 1;
            //operand_stack.print();
        }
    }
    return operand_stack.top();
}

int Rpn::order_between_operator(char operator_one, char operator_two)
{
    return (priority[static_cast<int>(operator_two)] - priority[static_cast<int>(operator_one)]);
}