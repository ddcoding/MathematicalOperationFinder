//
// Created by Karol on 2017-12-09.
//

#ifndef LAB_3_GENETICTREE_H
#define LAB_3_GENETICTREE_H

#include "CTree.h"

class GeneticTree {
private:
    vector<pair<CTree *,float> *> *treeVector;
    vector<vector<float> *> *vectorData;
    pair<CTree*,float> * bestTree;

    CTree *genereteTreeHelper(CNode *cNode, vector<pair<string, float> *> *tab_var_values);

    string randOperator();

    string randValue(vector<pair<string, float> *> *tab_var_values);

// PG methods
    void readData();

    void initTrees(int populationSize);

    bool evaluate();

    void selection(int populationSize);

    void performCrossing(float crossP);

    vector<float> *splitLine(string line);

    void mutatePopulation(float mutateP);

    CTree *mutate(CTree *cTree);

    void getMinValue();

    void setBestTree(pair<CTree *, float> *bestTree);

public:
    GeneticTree();

    virtual ~GeneticTree();

    CTree *PG(int populationSize, int repeats, float crossP, float mutP);

    vector<pair<CTree *,float> *> *getTreeVector() const;


    void cross(int index1, int index2);

    vector<vector<float> *> *getVectorData() const;

// mutate methods
    CTree *genereteTree(vector<pair<string, float> *> *tab_var_values);

    bool saveData(int repeats,int maxValue, CTree * cTree);
};


#endif //LAB_3_GENETICTREE_H
