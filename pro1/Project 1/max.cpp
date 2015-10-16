#include "max.hpp"

// You will need to implement a complete visitor that
// finds the maximum element in the tree. You can use
// the print and sum visitors for reference.

// WRITEME

//This compares each node in the tree and update the max.

void MaxVisitor::visitNode(Node* node){
    int curmax= node->value;
    
    node->visit_children(this);
    if (curmax>MaxVisitor::max) {
        MaxVisitor::max = curmax;
    }else{
        node++;
    }
}