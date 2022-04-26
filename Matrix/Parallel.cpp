#include "Parallel.h"
using namespace std;

void parallelMenu()
{
    char select;

    cout << "Welcome in the parallel Matrix multiplicator !";

    cout << "\n\n Menu";
    cout << "\n========";
    cout << "\n R - Run";
    cout << "\n I - Info";
    cout << "\n E - Exit";
    cout << "\n\nChoose wisely: ";

    std::cin >> select;

    switch (select) {

    case 'R':
    case 'r': {
        // dopln

        break;
    }

    case 'I':
    case 'i': {
        cout << "\n INFO \n Tato uloha je zamerana na vypocet sucinu dvoch matic s vyuzitim threadov.";
        break;
    }

    case 'E':
    case 'e': {
        break;
    }

    default:
        cout << "\n oof";
    }

    cout << "\n";
}
