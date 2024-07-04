#ifndef BINARYOPNODE_HPP
#define BINARYOPNODE_HPP
#include "node.hpp"

class BinaryOpNode : public Node {
    public:
     BinaryOpNode(Node* left, Node* right);
     ~BinaryOpNode();

    protected:
     Node* m_left;
     Node* m_right;
};

#endif