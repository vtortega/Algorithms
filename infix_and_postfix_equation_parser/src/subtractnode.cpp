#include "subtractnode.hpp"

SubtractNode::SubtractNode(Node* left, Node* right) : BinaryOpNode(left, right) {}

double SubtractNode::evaluate() const {
    return m_left->evaluate() - m_right->evaluate();
}