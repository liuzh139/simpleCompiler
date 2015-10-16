#include <iostream>
#include "sum.hpp"

void SumVisitor::visitNode(Node* node) {
    // Hint: for this function, you will need to to use the sum
    // member of the object.
    
    // WRITEME
    node->visit_children(this);
    SumVisitor::sum += node->value;
}
