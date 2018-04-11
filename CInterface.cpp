//
// Created by Karol on 2017-11-11.
//
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "CInterface.h"

bool CInterface::enter(CTree *cTree) {
    string input;
    cin.ignore();
    getline(cin, input);
    vector<string> *parsed = split(input);
    for (auto &j : *parsed) {
        if (!cTree->isOperation(j))
            for (char i : j) {
                if (!((i >= 48 && i <= 57)
                      || (i >= 65 && i <= 90)
                      || (i >= 97 && i <= 122))) {
                    cout << "Wpisano niedozwolony znak: " << i << endl;
                    return false;
                }
            }
    }
    for (const auto &i : *parsed) {
        cTree->add(i);
    }
    cTree->checkIsCorrect(parsed->size());
    return true;
}

CInterface::CInterface() : tree(new CTree()), geneticTree(new GeneticTree()) {}

CInterface::~CInterface() {
    delete CInterface::tree;
    delete CInterface::geneticTree;
}

vector<string> *CInterface::split(string input) {
    vector<string> *parsed = new vector<string>();
    string temp = "";
    for (char i : input) {
        if (i == ' ') {
            parsed->push_back(temp);
            temp = "";
        } else {
            temp += i;
        }
    }
    if (temp != "") parsed->push_back(temp);

    return parsed;

}

CTree *CInterface::getTree() const {
    return tree;
}

void CInterface::print() {
    getTree()->print_pre_order(getTree()->getRoot());
    cout << endl;
}

void CInterface::vars() {
    if (getTree()->getTab_var_values()->size() != 0)
        getTree()->print_vars();
    else cout << "Nie ma w drzewie zadnych argumentow";
    cout << endl;

}

void CInterface::comp() {
    if (getTree()->getTab_var_values()->size() != 0) {
        string input;
        cin.ignore();
        getline(cin, input);
        vector<string> *parsed = split(input);
        if (getTree()->getTab_var_values()->size() == parsed->size())
            getTree()->completeVars(parsed);
        else
            cout << "Wprowadzona zostala bledna ilosc argumentow !" << endl << "Oczekiwana ilosc: "
                 << getTree()->getTab_var_values()->size() << "wprowadzono: " << parsed->size()
                 << " jezeli chcesz wyswietlic ilosc zmiennych komende 'vars'." << endl;
    }
    cout << getTree()->comp(getTree()->getRoot()) << endl;
}

void CInterface::join() {
    CTree *cTree = new CTree();
    enter(cTree);
    CTree *do_usuniecia = CInterface::tree;
    CInterface::tree = *CInterface::tree + cTree;
    if (do_usuniecia != CInterface::tree) delete do_usuniecia;
    cout << "Aktualny stan formuly po sklejeniu wyglada tak: ";
    print();
    cout << endl;
}

void CInterface::pg() {
    geneticTree->PG(200,50,0.5,0.5);
}

void CInterface::generateDataFile() {
    if(geneticTree->saveData(100,1,tree))
        cout << "Plik 'dane.txt' zostal wygenerowany poprawnie :)"<<endl;
    else cout << "Pliku nie udalo sie wygenerowac ! :("<<endl;
}
