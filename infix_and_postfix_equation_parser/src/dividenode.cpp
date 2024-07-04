#include "dividenode.hpp"

DivideNode::DivideNode(Node* left, Node* right) : BinaryOpNode(left, right) {}

double DivideNode::evaluate() const {

    if (m_right->evaluate() == 0) { // apenas testa se o valor do elemento da direita será zero (nao pode dividir por 0)
        throw std::runtime_error("EXP errada, divisao por zero");
    }

    return m_left->evaluate() / m_right->evaluate();
}