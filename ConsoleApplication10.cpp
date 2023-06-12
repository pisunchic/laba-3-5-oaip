#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

double performOperation(char operation, double operand1, double operand2) {
    if (operation == '+')
        return operand1 + operand2;
    else if (operation == '-')
        return operand1 - operand2;
    else if (operation == '*')
        return operand1 * operand2;
    else if (operation == '/')
        return operand1 / operand2;

    return 0.0;
}

int getOperatorPriority(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

double evaluateRPN(const string& expression) {
    stack<double> operands;

    istringstream iss(expression);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || token[0] == ',') {
            double operand = stod(token);
            operands.push(operand);
        }
        else if (isOperator(token[0])) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();

            double result = performOperation(token[0], operand1, operand2);
            operands.push(result);
        }
    }

    return operands.top();
}

string infixToRPN(const string& infix) {
    string rpn;
    stack<char> operators;

    for (char c : infix) {
        if (isdigit(c) || c == ',') {
            rpn += c;
        }
        else if (isOperator(c)) {
            rpn += ' ';
            while (!operators.empty() && operators.top() != '(' && getOperatorPriority(c) <= getOperatorPriority(operators.top())) {
                rpn += operators.top();
                operators.pop();
                rpn += ' ';
            }
            operators.push(c);
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpn += ' ';
                rpn += operators.top();
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        rpn += ' ';
        rpn += operators.top();
        operators.pop();
    }

    return rpn;
}

int main() {
    setlocale(0, "ru");
    string infixExpression;
    cout << "Введите инфиксное выражение в таком формате 5,6-(3,2/0,9*(1,7+4,8)) : ";
    getline(cin, infixExpression);

    string rpnExpression = infixToRPN(infixExpression);
    cout << "Обратная Польская Запись: " << rpnExpression << endl;

    double result = evaluateRPN(rpnExpression);
    cout << "Результат: " << result << endl;

    return 0;
}
