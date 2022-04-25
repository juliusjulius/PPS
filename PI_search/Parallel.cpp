#pragma once
#include "Parallel.h"
#include "Serial.h"
#include <atomic>
#include <stdlib.h>

using std::cout;
double valuePIp;
std::atomic<int> inCricle = 0;
std::atomic<int> count = 0;  //for debug;



void estimatePIparallel(int numberOfEst)
{ 
    srand(time(NULL));
    int throws = numberOfEst;
    double x, y;

    for (int i = 0; i <= throws -1; i++)
    {
        x = (double)rand() / (RAND_MAX);
        y = (double)rand() / (RAND_MAX);

        if ((x * x) + (y * y) <= 1)
        {
            inCricle++;
        }

        count++;
    }
}



void parallelMenu() {
    char select;

    cout << "Welcome in the parallel Pi value estimator !";

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
        int numberOfEst = 0;
        int numberOfThreads = 0;
        int ittNormal = 0; 
        int ittModulo = 0;

        cout << "\nenter the number of estimations: ";
        std::cin >> numberOfEst;

        cout << "\nenter the number of threads: ";
        std::cin >> numberOfThreads;
        cout << std::endl;

        std::chrono::high_resolution_clock::time_point startTime;   // variables to store time data
        std::chrono::high_resolution_clock::time_point endTime;

        cout << "\nMonte Carlo estimation has started ..." << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));



        //iteracie modulo vlakna
        ittModulo = numberOfEst % numberOfThreads; // extra iterations
        ittNormal = (numberOfEst - ittModulo) / numberOfThreads;  // number of iteration equally divided
        ittModulo += ittNormal;  // one thread will manage its own + that extra itterations



        std::vector < std::thread > estimators;   

        for (size_t i = 0; i < numberOfThreads - 1; i++) { //start normal threads
            estimators.push_back(std::thread(estimatePIparallel, ittNormal));
        }
        estimators.push_back(std::thread(estimatePIparallel, ittModulo)); // start thread with extra itt

        startTime = std::chrono::high_resolution_clock::now();  // start measure time 
        for (auto& th : estimators) th.join();

        endTime = std::chrono::high_resolution_clock::now();    // stop measurment


        cout.precision(7);
        valuePIp = 4.0 * inCricle / numberOfEst;    //calculating the estimated value of pi

       
        cout << "Approx value of PI: " << valuePIp << std::endl;  // results
        cout << "Exact value of PI: " << 22.0 / 7.0 << std::endl;
        cout << "Difference to exact value of PI: " << abs((22.0 / 7.0) - valuePIp) << std::endl;
        cout << "Error: " << (valuePIp - (22.0 / 7.0)) / (22.0 / 7.0) * 100 << " %" << std::endl;
        cout << "Time duration: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns\n";   // endTime - starTime = time elapsed
        cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ns\n";
        //debug cout << count << "itt normal " << ittNormal << " itt modulo " << ittModulo  << " val: " << inCricle;

        break;
    }

    case 'I':
    case 'i': {
        cout << "\n INFO \n Tato uloha je zamerana na odhadovanie cisla PI pomocou metody Monte Carlo s vyuzitim threadov.";
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