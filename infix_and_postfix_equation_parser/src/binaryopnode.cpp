#include "binaryopnode.hpp"

BinaryOpNode::BinaryOpNode(Node* left, Node* right) : m_left(left), m_right(right) {}


BinaryOpNode::~BinaryOpNode() {
    delete m_left;
    delete m_right; 
}