//
// Created by Karol on 2017-11-11.
//

#include <iostream>
#include <vector>
#include "CNode.h"
#include <utility>

#ifndef LAB_3_CTREE_H
#define LAB_3_CTREE_H
using namespace std;

class CTree {
    CNode *root;

    int size;

    int leaves;

    vector<pair<string, float> *> *tab_var_values;

    void fixTree(CNode *node);

    int contains_var(const string &var);

    float calc(CNode *node);

    void copy_nodes(CNode *cNode);

    void *find_var(CNode *cNode, CNode *&cNode_copy);

    void merge_vectors(vector<pair<string, float> *> *v2);

    CNode *getNodeByNumberHelper(CNode *cNode, int number, int acc);

    void printFunctionHelper(CNode *cNode, string &np);

public:
    explicit CTree(CTree *cTree);

    CTree *operator+(CTree *cTree1);

    float comp(CNode *node);

    CNode *getNodeByNumer(int number, int option);

    void completeVars(vector<string> *vars);

    void print_vars();

    void checkIsCorrect(unsigned int input_size);

    void setTab_var_values(vector<pair<string, float> *> *tab_var_values);

    int getLeaves() const;

    void setLeaves(int leaves);

    static bool isOperation(const string &element);

    void add(string value);

    bool addHelper(CNode *node, string value);

    virtual ~CTree();

    CTree();

    CTree(CNode *root);

    CNode *getRoot() const;

    void setRoot(CNode *root);

    int getSize() const;

    void setSize(int size);

    vector<pair<string, float> *> *getTab_var_values() const;

    void print_pre_order(CNode *node);

    void printFunction();

};


#endif //LAB_3_CTREE_H
