#include "addnode.hpp"

AddNode::AddNode(Node* left, Node* right) : BinaryOpNode(left, right) {}

double AddNode::evaluate() const {
    return m_left->evaluate() + m_right->evaluate(); 
}