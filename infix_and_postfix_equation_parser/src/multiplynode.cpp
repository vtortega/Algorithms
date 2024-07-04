#include "multiplynode.hpp"

MultiplyNode::MultiplyNode(Node* left, Node* right) : BinaryOpNode(left, right) {}

double MultiplyNode::evaluate() const{
    return m_left->evaluate() * m_right->evaluate();
}