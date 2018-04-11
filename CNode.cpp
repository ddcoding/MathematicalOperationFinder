//
// Created by Karol on 2017-11-11.
//

#include "CNode.h"

void CNode::setLeft(CNode *left) {
    CNode::left = left;
}

void CNode::setRight(CNode *right) {
    CNode::right = right;
}

CNode::CNode(string &value) : value(value) {}

CNode::CNode(CNode *left, CNode *right, string &value) : left(left), right(right), value(value) {}

CNode::~CNode() {
    delete left;
    delete right;
}

string CNode::getValue() const {
    return value;
}

void CNode::setValue(string value) {
    CNode::value = value;
}

CNode::CNode() : value(""), left(nullptr), right(nullptr) {}

CNode::CNode(CNode *cNode) {
    copy_nodes(cNode);
}

void CNode::copy_nodes(CNode *cNode) {
    CNode::value = cNode->getValue();
    CNode::left = nullptr;
    CNode::right = nullptr;
    if (cNode->left != nullptr) {
        CNode::left = new CNode();
        CNode::left->copy_nodes(cNode->left);
    }
    if (cNode->right != nullptr) {
        CNode::right = new CNode();
        CNode::right->copy_nodes(cNode->right);
    }

}
