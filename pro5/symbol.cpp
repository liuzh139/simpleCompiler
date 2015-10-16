#include "symbol.hpp"

// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.

void Symbol::visitProgramNode(ProgramNode* node) {
    classTable = new ClassTable;
    node->visit_children(this);
}

void Symbol::visitClassNode(ClassNode* node) {
    ClassInfo currentClassInfo;
    
    currentMemberOffset = 0;
    currentMethodTable = &currentClassInfo.methods;
    currentVariableTable = &currentClassInfo.members;
    
    if(node->identifier_2 == NULL){
        currentClassInfo.superClassName = "";
    }else{
        currentClassInfo.superClassName = node->identifier_2->name;
    }
    node->visit_children(this);
    currentClassInfo.membersSize = currentMemberOffset;
    
    classTable->insert(std::pair<std::string, ClassInfo>(node->identifier_1->name, currentClassInfo));
}

void Symbol::visitMethodNode(MethodNode* node) {  
    MethodInfo currentMethodInfo;
    
    currentParameterOffset = 8;
    currentLocalOffset = -4;
    currentVariableTable = &currentMethodInfo.variables;

    currentMethodInfo.returnType.baseType = node->type->basetype;
    
    node->visit_children(this);
    currentMethodInfo.localsSize = -(currentLocalOffset+4);
    currentMethodTable->insert(std::pair<std::string, MethodInfo>(node->identifier->name, currentMethodInfo));
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) {
    node->visit_children(this);
}

void Symbol::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    VariableInfo currentVariableInfo;
    
    currentVariableInfo.size = 4;
    currentVariableInfo.type.baseType = node->type->basetype;
    
    currentVariableTable->insert(std::pair<std::string,VariableInfo>(node->identifier->name,currentVariableInfo));
    currentParameterOffset += 4;
    currentVariableInfo.offset = currentParameterOffset;
}


void Symbol::visitDeclarationNode(DeclarationNode* node) {
    //why is the counpound type has the objectClassName?
    //check the offset to see if we are inside a class
    for (std::list<IdentifierNode*>::iterator iter = node->identifier_list->begin();
         iter != node->identifier_list->end(); iter++){

        VariableInfo currentVariableInfo;
        currentVariableInfo.size = 4;
        currentVariableInfo.type.baseType = node->type->basetype;
        
        if (currentVariableInfo.type.baseType == bt_object){
            currentVariableInfo.type.objectClassName = ((ObjectTypeNode*) node->type)->identifier->name;
        }
        if (currentVariableInfo.offset == 0){
            currentVariableInfo.offset = currentMemberOffset;
            currentMemberOffset += 4;
        }else{ 
            currentVariableInfo.offset = currentLocalOffset;
            currentLocalOffset += -4; 
        }
         currentVariableTable->insert(
                                     std::pair<std::string,VariableInfo>((*iter)->name,currentVariableInfo));    
    }
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_integer; 
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_boolean;
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_object;
}

void Symbol::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_none;
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
