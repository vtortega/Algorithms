#ifndef PARSER_HPP
#define PARSER_HPP

#include "addnode.hpp"
#include "subtractnode.hpp"
#include "valuenode.hpp"
#include "dividenode.hpp"
#include "multiplynode.hpp"

class Parser {
public:
    Parser(std::string expression);
    Node* parseInfix();
    Node* parsePostfix();
    std::string toPostfix();
    std::string toInfix();

private:
    std::string m_expression;
    std::stringstream m_tokens;

    double parseNumber();
    Node* parseTerm();
    Node* parseFactor();
    Node* parseExpression();
    void skipWhitespace();
};

#endif