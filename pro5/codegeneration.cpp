#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
#if __APPLE__
    // Generate label with leading underscore
    std::cout<< " .globl _Main_main" << std::endl;
#else
    // Generate without leading underscore
    std::cout << " .globl Main_main" << std::endl;
#endif
    //std::cout << " .globl Main_main" << std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    
    currentClassName = node->identifier_1->name;
    currentClassInfo = (*classTable)[currentClassName];
    node->visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    
    currentMethodName = node->identifier->name;
    currentMethodInfo = currentClassInfo.methods[currentMethodName];
    std::cout << " # Method " << std::endl;
    
#if __APPLE__
    // Generate label with leading underscore
    std::cout << " _"<<currentClassName<<"_"<<currentMethodName<<": "<<std::endl;
#else
    // Generate without leading underscore
    std::cout << " "<<currentClassName<<"_"<<currentMethodName<<": "<<std::endl;
#endif
    
    // std::cout << " "<<currentClassName<<"_"<<currentMethodName<<": "<<std::endl;
    std::cout << " push %ebp" << std::endl; //save the old base_ptr
    std::cout << " mov %esp, %ebp" <<std::endl; //set the base_ptr = stack_ptr(ebp gets the value from esp)
    std::cout << " sub $" << currentMethodInfo.localsSize << ", %esp" <<std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    node->visit_children(this);
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    node->visit_children(this);
    std::cout << " # Return Statement" << std::endl;
    std::cout << " pop %eax" << std::endl; //save the return value
    std::cout << " mov %ebp, %esp" << std::endl; //deallocate the local variable space
    std::cout << " pop %ebp" << std::endl; //restoring the old base_ptr
    std::cout << " ret" << std::endl; //jumping back to the return address
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    node->visit_children(this);
    std::cout << " # Assignment" <<std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " mov %eax, " <<
    (currentMethodInfo.variables[node->identifier->name]).offset << "(%ebp)" <<std::endl;
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    node->visit_children(this);
    std::cout << " # Plus" << std::endl;
    std::cout << " pop %edx" << std::endl; //pop the 2nd operand into %edx
    std::cout << " pop %eax" << std::endl; //pop the 1st operand into %eax
    std::cout << " add %edx, %eax" << std::endl; //add the second operand to the first (meaning that the sum is in the eax register
    std::cout << " push %eax" << std::endl; //push that result back to the stack
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    node->visit_children(this);
    std::cout << " # Minus" << std::endl;
    std::cout << " pop %edx" <<std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " sub %edx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
    
}
void CodeGenerator::visitTimesNode(TimesNode* node) {
    node->visit_children(this);
    std::cout << " # Times" << std::endl;
    std::cout << " pop %edx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " imul %edx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    node->visit_children(this);
    std::cout << " # Divide" << std::endl;
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cdq" << std::endl;
    std::cout << " idiv %ebx" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    node->visit_children(this);
    std::cout << " # Negation" << std::endl;
    std::cout << " pop %edx" << std::endl;
    std::cout << " neg %edx" << std::endl;
    std::cout << " push %edx" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    node->visit_children(this);
    std::cout << " # Variable Node" <<std::endl;
    std::cout << " push "<<
    currentMethodInfo.variables[node->identifier->name].offset <<
    " (%ebp)" << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    
    int number = node->integer->value;
    node->visit_children(this);
    std::cout << " # Integer Literal " << std::endl;
    std::cout << " push $" << number << std::endl;
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // Depends on.
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
