#ifndef SUBTRACTNODE_HPP
#define SUBTRACTNODE_HPP

#include "binaryopnode.hpp"

class SubtractNode : public BinaryOpNode {
    public:
     SubtractNode(Node* left, Node* right);
     double evaluate() const override;

};

#endif