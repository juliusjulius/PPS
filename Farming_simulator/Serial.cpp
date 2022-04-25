#include "Serial.h"

struct structureS;
using std::cout;

void master(structureS& data) {
    data.warehouseStatus = 0; // master emptie's warehouse
    cout << std::endl << " *warehouse has been emptied*" << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << std::endl << "Master: Why is warehouse empty ?! *whip* *whip*" << std::endl << std::endl;
}

void slave(structureS& data) {
    data.field--;
    data.warehouseStatus++;
    cout << " *Cotton collected* " << std::endl;
}

void farm(structureS& data) { // farm loop

    bool end = false;

    while (!end) {

        if (data.warehouseStatus == data.warehouseCapacity)  // if warehouse full, call Master methode to empty warehouse  
        {
            cout << std::endl << "Slave: oh no, warehouse full, I rest" << std::endl;
            master(std::ref(data));
        }
        else
        {
            slave(std::ref(data));
        }

        if (data.field == 0)  // checking if there is cotton to collect, if not terminate program
        {
            end = true;
            cout << std::endl << "Master: great job, field is harvested !" << std::endl;
        }
    }

}

void serialMenu() {
    char select;

    cout << "Welcome in the serial Farming simulator !";

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
        int warehouseCapacity;
        int numberOfSlaves;
        int field;

        cout << "\nenter field size: ";
        std::cin >> field;

        cout << "enter warehouse capacity: ";
        std::cin >> warehouseCapacity;

        cout << "\nSimulation has started, year - 1705..." << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        structureS data{ 0, warehouseCapacity, field };

        farm(std::ref(data));
        break;
    }

    case 'I':
    case 'i': {
        cout << "\n INFO \n Uloha ilustruje priklad serioveho riesenia problemu.\n";
        std::this_thread::sleep_for(std::chrono::seconds(4));
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