#ifndef MULTIPLYNODE_HPP
#define MULTIPLYNODE_HPP

#include "binaryopnode.hpp"

class MultiplyNode : public BinaryOpNode {
    public:
     MultiplyNode(Node* left, Node* right);
     double evaluate() const override;
};

#endif