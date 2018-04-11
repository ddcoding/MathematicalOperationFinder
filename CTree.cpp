//
// Created by Karol on 2017-11-11.
//

#include "CTree.h"
#include <cmath>
#include <queue>
#include <algorithm>

#define DEFAULT_INIT_VAR_VALUE 0
#define DEFAULT_FILL_VALUE "1"

CNode *CTree::getRoot() const {
    return root;
}

void CTree::setRoot(CNode *root) {
    CTree::root = root;
}

int CTree::getSize() const {
    return size;
}

void CTree::setSize(int size) {
    CTree::size = size;
}

CTree::CTree(CTree *cTree) {
    CTree::tab_var_values = new vector<pair<string, float> *>();
    CTree::root = new CNode();
    for (auto &i : *cTree->getTab_var_values())
        CTree::tab_var_values->push_back(new pair<string, float>(i->first, i->second));

    copy_nodes(cTree->root);

}

CTree::CTree() : size(0), leaves(0), root(new CNode()), tab_var_values(new vector<pair<string, float> *>()) {}

CTree::~CTree() {
    delete tab_var_values;
    delete root;
}

CTree::CTree(CNode *root) : root(root) {}

bool CTree::isOperation(const string &element) {
    return element == "sin"
           || element == "cos"
           || element == "+"
           || element == "-"
           || element == "*"
           || element == "/";
}

void CTree::add(string value) {
    addHelper(CTree::root, value);
}

bool CTree::addHelper(CNode *node, string value) {
    if (node->getValue() == "") {
        if (isOperation(value)) {
            node->setLeft(new CNode());
            if (value != "sin" && value != "cos")
                node->setRight(new CNode());
        } else {
            if (!(value.size() == 1 && value[0] >= 48 && value[0] <= 57)) {
                if (contains_var(value) == -1)
                    getTab_var_values()->push_back(new pair<string, float>(value, DEFAULT_INIT_VAR_VALUE));
            }
            setLeaves(getLeaves() + 1);
        }
        node->setValue(value);
        setSize(getSize() + 1);
        return true;
    } else {
        if (node->left != nullptr) {
            if (!addHelper(node->left, value)) {
                if (node->right != nullptr)
                    if (addHelper(node->right, value)) return true;
            } else return true;
        }
    }
    return false;
}

vector<pair<string, float> *> *CTree::getTab_var_values() const {
    return tab_var_values;
}

void CTree::print_pre_order(CNode *node) {
    cout << node->getValue() << " ";
    if (node->left != nullptr) print_pre_order(node->left);
    if (node->right != nullptr) print_pre_order(node->right);

}

void CTree::fixTree(CNode *node) {
    if (node->getValue() == "") {
        node->setValue(DEFAULT_FILL_VALUE);
        setSize(getSize() + 1);
    }
    if (node->left != nullptr) fixTree(node->left);
    if (node->right != nullptr) fixTree(node->right);

}

int CTree::getLeaves() const {
    return leaves;
}

void CTree::setLeaves(int leaves) {
    CTree::leaves = leaves;
}

void CTree::checkIsCorrect(unsigned int input_size) {
    fixTree(root);
    if (input_size < getSize())
        cout << "Wyrazenie jest nie kompletne ! Uzupelniono wartoscia domyslna !" << endl;
    else if (input_size > getSize())
        cout << "Wyrazenie posiada za duzo stalych badz zmiennych. Usunieto nieprzypisane !" << endl;
    cout << "Aktualny stan formuly wyglada tak: ";
    print_pre_order(root);
    cout << endl;
}

int CTree::contains_var(const string &var) {
    for (int i = 0; i < getTab_var_values()->size(); i++) {
        if (getTab_var_values()->at(i)->first == var) return i;
    }
    return -1;
}

void CTree::print_vars() {
    for (auto &i : *getTab_var_values())
        cout << i->first << "=" << i->second << "  ";
    cout << endl;
}

float CTree::calc(CNode *node) {
    if (node->getValue() == "+") return comp(node->left) + comp(node->right);
    else if (node->getValue() == "-") return comp(node->left) - comp(node->right);
    else if (node->getValue() == "/")
        if (comp(node->right) != 0)
            return comp(node->left) / comp(node->right);
        else {
            delete node->right;
            node->right = new CNode();
            node->right->setValue("1");
            return comp(node->left);
        }
    else if (node->getValue() == "*") return comp(node->left) * comp(node->right);
    else if (node->getValue() == "sin") return sin(comp(node->left));
    else if (node->getValue() == "cos") return cos(comp(node->left));
}

float CTree::comp(CNode *node) {
    if (isOperation(node->getValue())) {
        return calc(node);
    }
    if (contains_var(node->getValue()) == -1)
        return stof(node->getValue());
    else
        for (auto &i : *getTab_var_values())
            if (i->first == node->getValue())
                return i->second;
}

void CTree::completeVars(vector<string> *vars) {
    if (vars->size() == getTab_var_values()->size())
        for (int i = 0; i < getTab_var_values()->size(); i++)
            getTab_var_values()->at(i)->second = stof(vars->at(i));
    else cout << "Podana ilosc zmiennych jest nie poprawna !" << endl;

}

CTree *CTree::operator+(CTree *cTree) {
    auto *cTree_org = new CTree(this);
    cTree_org->setSize(cTree_org->getSize() + cTree_org->getSize() - 1);
    CNode *cNode_copy = new CNode();
    cTree_org->find_var(cTree_org->getRoot(), cNode_copy);
    if (cNode_copy->getValue() != "") {
        cTree_org->getTab_var_values()->erase(
                cTree_org->getTab_var_values()->begin() + cTree_org->contains_var(cNode_copy->getValue()));
        cTree_org->merge_vectors(cTree->getTab_var_values());
        cNode_copy->setValue(cTree->getRoot()->getValue());
        cNode_copy->left = cTree->getRoot()->left;
        cNode_copy->right = cTree->getRoot()->right;
        return cTree_org;
    }
    cout << "Nie znaleziono argumentu, pod ktory mozna podstawic drugie drzewo !" << endl;
    return this;
}

void CTree::copy_nodes(CNode *cNode) {
    add(cNode->getValue());
    if (cNode->left != nullptr) copy_nodes(cNode->left);
    if (cNode->right != nullptr) copy_nodes(cNode->right);
}

void *CTree::find_var(CNode *cNode, CNode *&cNode_copy) {
    if (!isOperation(cNode->getValue()) && !(cNode->getValue().size() == 1 && cNode->getValue()[0] <= 57)) {
        cNode_copy = cNode;
    }
    if (cNode->left != nullptr) find_var(cNode->left, cNode_copy);
    if (cNode->right != nullptr) find_var(cNode->right, cNode_copy);
}

void CTree::merge_vectors(vector<pair<string, float> *> *v2) {
    for (auto &i : *v2)
        if (contains_var(i->first) == -1)
            getTab_var_values()->push_back(new pair<string, float>(i->first, i->second));
}

CNode *CTree::getNodeByNumer(int number, int option) {
    switch (option) {
        case 0 :
            return getNodeByNumberHelper(getRoot(), number, 0);
        case 1:
            return getNodeByNumberHelper(getRoot()->left, number / 2, 0);
        case 2:
            return getNodeByNumberHelper(getRoot()->right, number / 2, 0);

        default:
            break;
    }
}

CNode *CTree::getNodeByNumberHelper(CNode *cNode, int number, int acc) {
    if (cNode != nullptr) {
        queue<CNode *> *queue1 = new queue<CNode *>();
        queue1->push(cNode);
        CNode *temp = nullptr;
        while (!queue1->empty()) {
            temp = queue1->front();
            if (acc == number) {
                delete queue1;
                return temp;
            }
            queue1->pop();
            if (temp->left != nullptr) queue1->push(temp->left);
            if (temp->right != nullptr) queue1->push(temp->right);
            acc++;
        }
        delete queue1;
        return temp;
    }
    return root;
}

void CTree::setTab_var_values(vector<pair<string, float> *> *tab_var_values) {
    CTree::tab_var_values = tab_var_values;
}

void CTree::printFunction() {
    string np;
    printFunctionHelper(root, np);
    reverse(np.begin(), np.end());
    np.erase(np.begin(),np.begin()+2);
    np.erase(np.end()-2,np.end());
    cout << np << endl;
}

void CTree::printFunctionHelper(CNode *cNode, string &np) {
    np += " )";
    if (cNode->left != nullptr) printFunctionHelper(cNode->left, np);
    if (cNode->getValue() == "sin" || cNode->getValue() == "cos") {
        string copy = cNode->getValue();
        reverse(copy.begin(), copy.end());
        np += copy;
    } else
        np += cNode->getValue();
    if (cNode->right != nullptr) printFunctionHelper(cNode->right, np);
    np += "( ";
}



