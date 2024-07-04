#ifndef ADDNODE_HPP
#define ADDNODE_HPP
#include "binaryopnode.hpp"

class AddNode : public BinaryOpNode {

    public:
     AddNode(Node* left, Node* right);
     double evaluate() const override;

};


#endif