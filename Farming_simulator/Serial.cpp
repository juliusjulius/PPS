#include "Serial.h"

struct structureS;
using std::cout;

void master(structureS& data) {
    data.warehouseStatus = 0; // master emptie's warehouse
    cout << std::endl << " *warehouse has been emptied*" << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(500));
    cout << std::endl << "Master: Why is warehouse empty ?! *whip* *whip*" << std::endl << std::endl;
}

void slave(structureS& data) {
    data.field--;
    data.warehouseStatus++;
    cout << " *Cotton collected* " << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(500)); // collecting of cotton
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
        std::chrono::high_resolution_clock::time_point startTime;   // variables to store time data
        std::chrono::high_resolution_clock::time_point endTime;

        cout << "\nenter field size: ";
        std::cin >> field;

        cout << "enter warehouse capacity: ";
        std::cin >> warehouseCapacity;

        cout << "\nSimulation has started, year - 1705..." << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        structureS data{ 0, warehouseCapacity, field };

        
        startTime = std::chrono::high_resolution_clock::now();  // start measure time 
        farm(std::ref(data));                                   // execute code
        endTime = std::chrono::high_resolution_clock::now();    // stop measurment

        cout << "\n===============================";
        cout << "\nEndtime in miliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();   // endTime - starTime = time elapsed
        cout << "\n=========================";
        cout << "\nEndtime in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
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