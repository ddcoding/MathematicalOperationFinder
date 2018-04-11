//
// Created by Karol on 2017-11-11.
//

#ifndef LAB_3_CINTERFACE_H
#define LAB_3_CINTERFACE_H


#include "CTree.h"
#include <vector>
#include "../Lab4 actual/GeneticTree.h"
class CInterface {
private:
    CTree *tree;
    GeneticTree * geneticTree;
    vector<string> * split(string input);


public:
    void generateDataFile();

    CTree *getTree() const;

    void join();

    void pg();

    void print();

    virtual ~CInterface();

    CInterface();

    bool enter(CTree * cTree);

    void vars();

    void comp();

};


#endif //LAB_3_CINTERFACE_H
