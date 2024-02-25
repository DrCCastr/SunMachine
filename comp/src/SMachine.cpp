#include "index.h"

/*
p1 == print / printar

t1 types/tipos = { -- todos objetos da lista estarao acrensetados a t1 (ex: t1s1)
    s1 = string / texto
    e1 = expr / expresao numerica
}


*/
double applyOperator(double operand1, double operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            return 0.0;  // Tratamento padrão para operador desconhecido
    }
}

double evaluateExpression(const std::string& expression) {
    std::istringstream input(expression);

    std::stack<double> operands;
    std::stack<char> operators;

    char ch;
    while (input >> ch) {
        if (std::isdigit(ch)) {
            input.putback(ch);
            double value;
            input >> value;
            operands.push(value);
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            operators.push(ch);
        } else if (ch == '\'') {
            if (!operands.empty()) {
                operands.top() = -operands.top();
            }
        } else if (ch == ';') {
            // Encontrou ponto e vírgula, avalia a expressão até o momento
            while (!operators.empty()) {
                if (operands.size() >= 2) {
                    double operand2 = operands.top();
                    operands.pop();
                    double operand1 = operands.top();
                    operands.pop();
                    char op = operators.top();
                    operators.pop();
                    operands.push(applyOperator(operand1, operand2, op));
                }
            }
        }
    }

    // Avalia a expressão restante
    while (!operators.empty()) {
        if (operands.size() >= 2) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            char op = operators.top();
            operators.pop();
            operands.push(applyOperator(operand1, operand2, op));
        }
    }

    if (!operands.empty()) {
        return operands.top();
    }

    return 0.0;  // Default value if a valid result is not obtained
}

std::ofstream CreateFile(std::string path) {
    path += "/app.s";
    std::ofstream file(path);
    
    file << ".global _start \n";
    file << ".intel_syntax noprefix";
    file << "\n";
    file << "_start:\n";
    
    return file;
}

void Sun::Index::Machine(std::vector<std::string> Tokens, std::string path) {
    Sun::Str::compiling Compiling;
    std::ofstream file = CreateFile(path);
    std::vector<std::string> strings_prints;
    int i = 0;
    while (i < Tokens.size()) {
        std::cout << Tokens[i] << " -- ";
        i++;
    }
    std::cout << "\n";
    i = 0;
    while (i < Tokens.size())
    {
        if (Tokens[i] == "p1" && i + 2 < Tokens.size()) {
            if (Tokens[i + 1] == "t1s1") {
                
                Compiling.Line += 1;
                strings_prints.push_back(Tokens[i+2]);
            } else if (Tokens[i+1] == "t1e1") {
                //std::cout << evaluateExpression(Tokens[i+2]) << std::endl;
            }
        }
    i++;
    }
    
    file.close();
}
