#include <iostream>
#include <ctime>
#include "CInterface.h"
#include "../Lab4 actual/GeneticTree.h"

using namespace std;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(false);

    CInterface *cInterface;
    bool is_created = false,
            exit = false;
    string s;
    cout
            << "Witaj w programie !\n"
                    "1. enter <formula> - wpisz formule by wyliczyc jej wartosc \n"
                    "2. print - wyswietl drzewo metoda pre order \n"
                    "3. vars - wyswietl wszystkie zmienne w drzewie\n"
                    "4. comp - Wylicz waartosc\n"
                    "5. join <formula> - dokleja formule do drzewa (w miejsce pierwszej najpotkanej niewiadomej)\n"
                    "6. generate - Generuje plik dane.txt z wartosciami x i y oraz wynikiem\n"
                    "7. pg - Wywolanie algorytmu genetycznego\n"
                    "8. exit - wyjscie z programu"
                    "\n";
    while (!exit) {
        cin >> s;
        if (s == "enter") {
            if (is_created) {
                cout << "Poprzednia formula zostanie zastapiona przez nowa !" << endl;
                delete cInterface;
            }
            cInterface = new CInterface();
            is_created = cInterface->enter(cInterface->getTree());
        }
        if (is_created || s == "pg") {
            if (s == "print") {
                cInterface->print();
            } else if (s == "vars")
                cInterface->vars();
            else if (s == "comp")
                cInterface->comp();
            else if (s == "join")
                cInterface->join();
            else if (s == "generate")
                cInterface->generateDataFile();
            else if (s == "pg") {
                cout << "Zaczynam szukac dzialania..." << endl;
                CInterface *cInterface2 = new CInterface();
                cInterface2->pg();
                delete cInterface2;
            } else if (s != "enter" && s != "exit") cout << "Podane zostalo nieprawidlowe polecenie!" << endl;
        } else cout << "Drzewo nie zostalo jeszcze stworzone!" << endl;
        if (s == "exit") exit = true;

    }


    return 0;
}