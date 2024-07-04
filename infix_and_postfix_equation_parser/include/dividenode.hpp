#ifndef DIVIDENODE_HPP
#define DIVIDENODE_HPP

#include "binaryopnode.hpp"

class DivideNode : public BinaryOpNode {
    public:
     DivideNode(Node* left, Node* right);
     double evaluate() const override;
};

#endif