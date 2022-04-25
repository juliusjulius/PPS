#include "Serial.h"
#include "Parallel.h"
#include<stdlib.h>


using std::cout;

void menu() {

    char select;

    cout << "Welcome in the Farming simulator !";

    cout << "\n\n Menu";
    cout << "\n========";
    cout << "\n P - Parallel";
    cout << "\n S - Serial";
    cout << "\n E - Exit";
    cout << "\n\nChoose wisely: ";

    std::cin >> select;
    system("cls");

    switch (select) {

    case 'P':
    case 'p': {
        parallelMenu();
        break;
    }

    case 'S':
    case 's': {
        serialMenu();
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

int main(int argc, char* argv[]) {

    srand(time(NULL));
    menu();

    return 0;
}