#include "parser.hpp"
#include "stack.hpp"

bool isPostfix(const std::string& expr) {
    int operands = 0;
    int operators = 0;

    for (const char& c : expr) {
        if (isdigit(c)) {
            ++operands;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            ++operators;
        }
    }


    return operands == operators + 1;
}


Parser::Parser(std::string expression)
    : m_expression(expression)
{
    if(isPostfix(m_expression)) {
        return;
    }
    else{

    // Fomatando a expressão
    std::string expression2 = m_expression;
    m_expression.erase(std::remove_if(m_expression.begin(), m_expression.end(), [](char c){ return std::isspace(c); }), m_expression.end());

    char c1 = m_expression.back();
    if(c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/') {
        m_expression = expression2;
        return;
    }

        int parenthese2Number, parenthese1Number;
        parenthese1Number = parenthese2Number = 0;

        // Formatando a expressão para que temos um stream de tokens
        for (char c : m_expression) {
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {           
                m_tokens << ' ' << c << ' ';



                if (c == '(') {
                    parenthese1Number++;
                }
                if (c == ')') {
                    parenthese2Number++;
                }

            } else {
                m_tokens << c;
            }
        }

        if(parenthese1Number != parenthese2Number) {
            throw std::runtime_error(" Numero de parenteses incorreto");
        }
    }
}

double Parser::parseNumber() {
    double value;
    m_tokens >> value;
    if (m_tokens.fail()) {
        throw std::runtime_error(" Numero invalido");
    }
    return value;
}

Node* Parser::parseTerm() {
    Node* node = parseFactor();
    for (;;) {
        skipWhitespace();
        char op = m_tokens.peek();
        if (op == '*' || op == '/') {
            m_tokens.get();
            Node* right = parseFactor();
            if (op == '*') {
                node = new MultiplyNode(node, right);
            } else {
                node = new DivideNode(node, right);
            }
        } else {
            break;
        }
    }
    return node;
}

Node* Parser::parseFactor() {
    Node* node = nullptr;
    skipWhitespace();
    char c = m_tokens.peek();
    if (c == '(') {
        m_tokens.get();
        node = parseExpression();
        skipWhitespace();
        if(m_tokens.peek() == -1){
            std::cout << std::endl;
        }
        else if (m_tokens.get() != ')') {
            throw std::runtime_error(" Faltando: ')'");
        }
    } else if (std::isdigit(c) || c == '-') {
        double value = parseNumber();
        node = new ValueNode(value);
    } else {
        throw std::runtime_error(" Factor Invalido");
    }
    return node;
}

Node* Parser::parseExpression() {
    Node* node = parseTerm();
    for (;;) {
        skipWhitespace();
        char op = m_tokens.peek();
        if (op == '+' || op == '-') {
            m_tokens.get();
            Node* right = parseTerm();
            if (op == '+') {
                node = new AddNode(node, right);
            } else {
                node = new SubtractNode(node, right);
            }
        } else {
            break;
        }
    }
    return node;
}

void Parser::skipWhitespace() {
    while (std::isspace(m_tokens.peek())) {
        m_tokens.get();
    }
}

Node* Parser::parseInfix() {
    Node* node = parseExpression();
    skipWhitespace();
    if (m_tokens.peek() != std::stringstream::traits_type::eof()) {
        throw std::runtime_error(" Input Incorreto");
    }
    return node;
}

std::string Parser::toPostfix() {
    std::stringstream postfix;
    const int MAX_EXPRESSION_LENGTH = 10000;
    char opStack[MAX_EXPRESSION_LENGTH];
    int top = -1;
    bool parsingNumber = false;

    skipWhitespace();

    


    for (char c : m_expression) {
        if (isdigit(c) || c == '.') {
            if (!parsingNumber) {
                if (!postfix.str().empty() && postfix.str().back() != ' ') {
                    postfix << ' ';
                }
                parsingNumber = true;
            }
            postfix << c;
        } else {
            parsingNumber = false;
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                while (top >= 0 && opStack[top] != '(' &&
                    ((opStack[top] == '*' || opStack[top] == '/') ||
                        (c == '+' || c == '-'))) {
                    postfix << ' ' << opStack[top] << ' ';
                    top--;
                }
                top++;
                opStack[top] = c;
            } else if (c == '(') {
                top++;
                opStack[top] = c;
            } else if (c == ')') {
                while (top >= 0 && opStack[top] != '(') {
                    postfix << ' ' << opStack[top] << ' ';
                    top--;
                }
                if (top >= 0 && opStack[top] == '(') {
                    top--;
                }
            }
        }
    }

    while (top >= 0) {
        postfix << ' ' << opStack[top] << ' ';
        top--;
    }

    return postfix.str();


        return postfix.str();
    }

Node* Parser::parsePostfix() {
    Stack<Node*> node_stack;
    std::stringstream ss(m_expression);
    std::string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            double value = stod(token);
            node_stack.push(new ValueNode(value));
        }
        else {
            Node* right = node_stack.peek();
            node_stack.pop();
            Node* left = node_stack.peek();
            node_stack.pop();

            if (token == "+") { // verificamos qual tipo de expressao que é para guardarmos em seu respectivo Node
                node_stack.push(new AddNode(left, right));
            }
            else if (token == "-") {
                node_stack.push(new SubtractNode(left, right));
            }
            else if (token == "*") {
                node_stack.push(new MultiplyNode(left, right));
            }
            else if (token == "/") {
                node_stack.push(new DivideNode(left, right));
            }
        }
    }

    return node_stack.peek();
}

std::string Parser::toInfix() {
    Stack<std::string> s;
    std::stringstream ss(m_expression);
    std::string token;
    while (ss >> token) {
        if (isdigit(token[0])) { // É um número, colocamos no stack
            s.push(token);
        } else { // É um operador
            std::string operand2 = s.peek();
            s.pop();
            std::string operand1 = s.peek();
            s.pop();
            std::string infix = "( " + operand1 + " " + token + " " + operand2 + " )";
            s.push(infix);
        }
    }
    // A expressão completa estará no final do stack;
    return s.peek();
}

