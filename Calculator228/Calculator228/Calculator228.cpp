#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

bool Is_Digit(char symbol) {
    if (symbol >= '0' && symbol <= '9' || symbol == '.') {
        return true;
    }
    else {
        return false;
    }
}

bool Is_Operator(char symbol) {
    if (symbol == '-' || symbol == '+' || symbol == '*' || symbol == '/') {
        return true;
    }
    else {
        return false;
    }
}

bool Is_Digit(const std::string& symbol) {
    if (symbol[0] >= '0' && symbol[0] <= '9' || symbol[0] == '-' && symbol.size() > 1) {
        return true;
    }
    else {
        return false;
    }
}



std::vector<std::string> To_Infix(const std::vector<std::string>& expression) {
    std::map<std::string, int> priority;
    priority["("] = 1;
    priority[")"] = 1;
    priority["+"] = 2;
    priority["-"] = 2;
    priority["*"] = 3;
    priority["/"] = 3;
    std::stack<std::string> st;
    std::vector<std::string> answer;
    for (const auto& symbol : expression) {
        if (symbol == "(") {
            st.push(symbol);
        }
        else if (symbol == ")") {
            while (st.top() != "(") {
                answer.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else if (Is_Digit(symbol)) {
            answer.push_back(symbol);
        }
        else {
            while (!st.empty() && priority[st.top()] >= priority[symbol]) {
                answer.push_back(st.top());
                st.pop();
            }
            st.push(symbol);
        }
    }
    while (!st.empty()) {
        answer.push_back(st.top());
        st.pop();
    }
    return answer;
}

double Calc(double a, double b, std::string operator_) {
    if (operator_ == "+") {
        return a + b;
    }
    if (operator_ == "-") {
        return b - a;
    }
    if (operator_ == "*") {
        return a * b;
    }
    if (operator_ == "/" && a != 0) {
        return b / a;
    }
}

double Calculate(std::vector<std::string> expression) {
    std::stack<double> st;
    for (const auto& symbol : expression) {
        if (Is_Digit(symbol)) {
            st.push(std::stod(symbol));
        }
        else {
            double a = st.top();
            st.pop();
            double b = st.top();
            st.pop();
            st.push(Calc(a, b, symbol));
        }
    }
    return st.top();
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::vector<std::string> expression(1);
    //size_t
    for (int i = 0; i < str.size() - 1; ++i) {
        if (str[i] == ' ') {
            continue;
        }
        if (str[i] == '-' && (i == 0 || str[i - 1] == '(' || Is_Operator(str[i - 1]))) {
            expression[expression.size() - 1] += str[i];
            continue;
        }
        expression[expression.size() - 1] += str[i];
        if (!(Is_Digit(str[i + 1]) && Is_Digit(str[i]))) {
            expression.push_back("");
        }
    }
    expression[expression.size() - 1] += str[str.size() - 1];

    expression = To_Infix(expression);
    std::cout << Calculate(expression);
}