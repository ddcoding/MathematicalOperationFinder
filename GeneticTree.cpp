//
// Created by Karol on 2017-12-09.
//

#include "GeneticTree.h"
#include <iostream>
#include "CTree.h"
#include <ctime>
#include <queue>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;

/**
 * method is randing 0 or 1
 * 0 mean first type mutation(changing)
 * 1 mean second type mutation(swaping)
 * */
CTree *GeneticTree::mutate(CTree *cTree) {
    CTree *cTreeCopy = new CTree(cTree);
    if (!(rand() % 2)) // mutation method
    {
        CNode *cNode = cTreeCopy->getNodeByNumer(rand() % cTreeCopy->getSize(), 0);
        if (!(rand() % 2)) { // leaf
            cNode->setValue(randValue(cTreeCopy->getTab_var_values()));
            if (cNode->left != nullptr) {
                delete (cNode->left);
                cNode->setLeft(nullptr);
            }
            if (cNode->right != nullptr)
                delete (cNode->right);
            cNode->setRight(nullptr);
        } else { // node
            CTree *ctree_generated = genereteTree(cTreeCopy->getTab_var_values());
            cNode->setValue(ctree_generated->getRoot()->getValue());
            if (cNode->left != nullptr) {
                delete (cNode->left);
                cNode->setLeft(nullptr);
            }
            if (cNode->right != nullptr) {
                delete (cNode->right);
                cNode->setRight(nullptr);
            }
            cNode->setLeft(ctree_generated->getRoot()->left);
            cNode->setRight(ctree_generated->getRoot()->right);
        }
    } else {
        CNode *cNode1 = cTreeCopy->getNodeByNumer(rand() & cTreeCopy->getSize(), 1);
        CNode *cNode2 = cTreeCopy->getNodeByNumer(rand() % cTreeCopy->getSize(), 2);

        CNode *temp = new CNode(cNode1);
        if (cNode1->left != nullptr) {
            delete (cNode1->left);
            cNode1->setLeft(nullptr);
        }
        if (cNode1->right != nullptr) {
            delete (cNode1->right);
            cNode1->setRight(nullptr);
        }
        cNode1->setValue(cNode2->getValue());
        cNode1->setLeft(cNode2->left);
        cNode1->setRight(cNode2->right);
        cNode2->setValue(temp->getValue());
        cNode2->setLeft(temp->left);
        cNode2->setRight(temp->right);


    }
    return cTreeCopy;
}

CTree *GeneticTree::genereteTree(vector<pair<string, float> *> *tab_var_values) {
    CTree *cTree = new CTree();
    cTree->getRoot()->setValue(randOperator());
    cTree->getRoot()->setLeft(new CNode());
    genereteTreeHelper(cTree->getRoot()->left, tab_var_values);
    if (!(cTree->getRoot()->getValue() == "sin" || cTree->getRoot()->getValue() == "cos")) {
        cTree->getRoot()->setRight(new CNode());
        genereteTreeHelper(cTree->getRoot()->right, tab_var_values);

    }
    cTree->setTab_var_values(new vector<pair<string, float> *>(*tab_var_values));
    return cTree;
}

CTree *GeneticTree::genereteTreeHelper(CNode *cNode, vector<pair<string, float> *> *tab_var_values) {
    if (!(rand() % 2)) { // 0 - number/variable
        cNode->setValue(randValue(tab_var_values));
    } else {
        cNode->setValue(randOperator());
        cNode->setLeft(new CNode());
        genereteTreeHelper(cNode->left, tab_var_values);
        if (!(cNode->getValue() == "sin" || cNode->getValue() == "cos")) {
            cNode->setRight(new CNode());
            genereteTreeHelper(cNode->right, tab_var_values);
        }
    }
}

string GeneticTree::randOperator() {
    switch (rand() % 6) {
        case 0:
            return "sin";
        case 1:
            return "cos";
        case 2:
            return "*";
        case 3:
            return "-";
        case 4:
            return "+";
        case 5:
            return "/";
        default:
            return "";
    }
}

string GeneticTree::randValue(vector<pair<string, float> *> *tab_var_values) {
    if (!(rand() % 2) && !tab_var_values->empty()) // variable
        return tab_var_values->at(
                rand() % tab_var_values->size())->first;
    else  // number
        return to_string((rand() % 9) + 1);
}

void GeneticTree::cross(int index1, int index2) {

    if (CTree::isOperation(treeVector->at(index1)->first->getRoot()->getValue()) &&
        CTree::isOperation(treeVector->at(index2)->first->getRoot()->getValue())) {

        CTree *cTree_copy1 = new CTree(treeVector->at(index1)->first);
        CTree *cTree_copy2 = new CTree(treeVector->at(index2)->first);

        CNode *temp;
        if (!(rand() % 2) || cTree_copy1->getRoot()->getValue() == "sin" ||
            cTree_copy1->getRoot()->getValue() == "cos") { // 0 - left of first tree
            temp = cTree_copy1->getRoot()->left;
            if (!(rand() % 2) || cTree_copy2->getRoot()->getValue() == "sin" ||
                cTree_copy2->getRoot()->getValue() == "cos") // 0 - left of second tree
            {
                cTree_copy1->getRoot()->setLeft(cTree_copy2->getRoot()->left);
                cTree_copy2->getRoot()->setLeft(temp);

            } else // 1 - right of second tree
            {
                cTree_copy1->getRoot()->setLeft(cTree_copy2->getRoot()->right);
                cTree_copy2->getRoot()->setRight(temp);
            }
        } else { // 1 - right of first tree
            temp = cTree_copy1->getRoot()->right;
            if (!(rand() % 2) || cTree_copy2->getRoot()->getValue() == "sin" ||
                cTree_copy2->getRoot()->getValue() == "cos") // 0 - left of second tree
            {
                cTree_copy1->getRoot()->setRight(cTree_copy2->getRoot()->left);
                cTree_copy2->getRoot()->setLeft(temp);
            } else // 1 - right of second tree
            {
                cTree_copy1->getRoot()->setRight(cTree_copy2->getRoot()->right);
                cTree_copy2->getRoot()->setRight(temp);

            }
        }
        delete treeVector->at(index1)->first, treeVector->at(index2)->first;
        treeVector->at(index1)->first = cTree_copy1;
        treeVector->at(index2)->first = cTree_copy2;
    }
}


GeneticTree::GeneticTree() : treeVector(new vector<pair<CTree *, float> *>()),
                             vectorData(new vector<vector<float> *>()),
                             bestTree(new pair<CTree *, float>(new CTree(), numeric_limits<float>::max())) {

}

vector<pair<CTree *, float> *> *GeneticTree::getTreeVector() const {
    return treeVector;
}

GeneticTree::~GeneticTree() {
    delete treeVector, vectorData, bestTree;
}

CTree *GeneticTree::PG(int populationSize, int repeats, float crossP, float mutP) {
    int percent = 100 / (repeats + 1);
    readData();
    initTrees(populationSize);
    evaluate();
    getMinValue();
    system("cls");
    cout << "Szukam dzialania..." << endl;
    cout << (char) 220 << " " << percent << "%" << endl;
    int i = 0;
    while (i < repeats) {
        selection(populationSize);
        performCrossing(crossP);
        mutatePopulation(mutP);
        evaluate();
//            if (evaluate()) i = repeats;
        getMinValue();
        i++;
        percent = (i + 1) * 100 / (repeats + 1);
        system("cls");
        int temp = percent / 2;
        cout << "Szukam dzialania..." << endl;
        for (unsigned int i = 0; i < temp; i++)
            cout << (char) 220;
        cout << " " << percent << "%" << endl;
    }
//    }
    cout << "Znaleziono dzialanie !" << endl;
    cout << "f(x,y)=";
    bestTree->first->printFunction();
    cout << endl;
    cout << "blad=" << bestTree->second << endl;

}

void GeneticTree::initTrees(int populationSize) {
    vector<pair<string, float> *> *tab_var_values = new vector<pair<string, float> *>();
    tab_var_values->push_back(new pair<string, float>("x", 0));
    tab_var_values->push_back(new pair<string, float>("y", 0));
    for (int i = 0; i < populationSize; i++)
        getTreeVector()->push_back(new pair<CTree *, float>(genereteTree(tab_var_values), -1));
    delete (tab_var_values);
}

void GeneticTree::readData() {
    ifstream *input = new ifstream();
    string line;
    input->open(R"(C:\Users\Karol\CLionProjects\Lab4 actual\dane.txt)");
    if (input->good()) {
        while (!input->eof()) {
            getline(*input, line);
            vectorData->push_back(splitLine(line));
        }
    } else
        cout << "Dostep do pliku zabroniony !" << endl;
    input->close();
    delete input;

}

vector<float> *GeneticTree::splitLine(string line) {
    vector<float> *result = new vector<float>();
    string buffor;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ';') {
            result->push_back(stof(buffor));
            buffor = "";
            i++;
        } else {
            buffor += line[i];
        }
    }
    return result;
}

vector<vector<float> *> *GeneticTree::getVectorData() const {
    return vectorData;
}

bool GeneticTree::evaluate() {
    float suma;
//    bool isPerfect = false;
    for (int i = 0; i < treeVector->size(); i++) {
        suma = 0;
        for (int j = 0; j < vectorData->size(); j++) {
            treeVector->at(i)->first->getTab_var_values()->at(0)->second = vectorData->at(j)->at(0);
            treeVector->at(i)->first->getTab_var_values()->at(1)->second = vectorData->at(j)->at(1);
            suma += (pow(
                    treeVector->at(i)->first->comp(treeVector->at(i)->first->getRoot()) - vectorData->at(j)->at(2), 2));
        }
        treeVector->at(i)->second = suma;
//        if(suma<0.00001) isPerfect = true;

    }
    return true;
//    return isPerfect;
}

void GeneticTree::selection(int populationSize) {
    vector<pair<CTree *, float> *> *result = new vector<pair<CTree *, float> *>();
    int indeks1, indeks2;
    for (int i = 0; i < populationSize; i++) {
        indeks1 = rand() % (treeVector->size() - 1);
        if (populationSize > 1)
            indeks2 = rand() % (treeVector->size() - 1);
        else indeks2 = indeks1;
        if (treeVector->at(indeks1)->second < treeVector->at(indeks2)->second)
            result->push_back(new pair<CTree *, float>(new CTree(treeVector->at(indeks1)->first),
                                                       treeVector->at(indeks1)->second));
        else
            result->push_back(new pair<CTree *, float>(new CTree(treeVector->at(indeks2)->first),
                                                       treeVector->at(indeks2)->second));
    }
    delete (treeVector);
    treeVector = result;
}

void GeneticTree::performCrossing(float crossP) {
    for (int i = 0; i < treeVector->size() - 1; i += 2)
        if ((rand() % 100) <= (crossP * 100 - 1))
            cross(i, i + 1);
}

void GeneticTree::mutatePopulation(float mutateP) {
    for (int i = 0; i < treeVector->size() - 1; i++)
        if ((rand() % 100) <= (mutateP * 100 - 1)) {
            CTree *to_delete = treeVector->at(i)->first;
            treeVector->at(i)->first = mutate(treeVector->at(i)->first);
            delete (to_delete);
        }
}

void GeneticTree::getMinValue() {
    float min = -1;
    unsigned int indeks = 0;
    for (unsigned int i = 0; i < treeVector->size(); i++) {
        if (i == 0) {
            min = treeVector->at(i)->second;
        } else {
            if (treeVector->at(i)->second < min) {
                min = treeVector->at(i)->second;
                indeks = i;
            }
        }
    }
    if (treeVector->at(indeks)->second < bestTree->second)
        setBestTree(new pair<CTree *, float>(*treeVector->at(indeks)));
//    cout<<"f(x,y)=";
//    treeVector->at(indeks)->first->printFunction();
//    cout<<endl;
//    cout<<" dokladnosc= "<<min<<endl;
}

bool GeneticTree::saveData(int repeats, int maxValue, CTree *cTree) {
    fstream *file = new fstream();
    file->open(R"(C:\Users\Karol\CLionProjects\Lab4 actual\dane.txt)", ios::out | ios::trunc);
    if (file->good()) {
        int i = 0;
        string temp = "";
        while (i < repeats) {
            temp = "";
            for (unsigned int i = 0; i < cTree->getTab_var_values()->size(); i++) {
                cTree->getTab_var_values()->at(i)->second = ((float) rand() / (float) RAND_MAX) * maxValue;
                temp += to_string(cTree->getTab_var_values()->at(i)->second) + "; ";
            }
            temp += to_string(cTree->comp(cTree->getRoot())) + "; ";
            if (i + 1 == repeats)
                *file << temp;
            else
                *file << temp << endl;
            file->flush();
            i++;
        }
    } else {
        cout << "Plik nie zostal prawidlowo otwarty !" << endl;
        file->close();
        delete file;
        return false;
    }
    file->close();
    delete file;
    return true;
}

void GeneticTree::setBestTree(pair<CTree *, float> *bestTree) {
    GeneticTree::bestTree = bestTree;
}





