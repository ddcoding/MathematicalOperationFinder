//
// Created by Karol on 2017-11-11.
//

#include <iostream>

#ifndef LAB_3_CNODE_H
#define LAB_3_CNODE_H

using namespace std;

class CNode {
private:
    string value;

    void copy_nodes(CNode *cNode);

public:
    CNode *left;
    CNode *right;

    virtual ~CNode();

    CNode(CNode *left, CNode *right, string &value);

    explicit CNode(CNode *cNode);

    explicit CNode(string &value);

    void setLeft(CNode *left);


    void setRight(CNode *right);

    string getValue() const;

    CNode();

    void setValue(string value);
};


#endif //LAB_3_CNODE_H
