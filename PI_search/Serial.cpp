#include "Serial.h"

using std::cout;
double valuePI;

void estimatePI(int numberOfEst)
{
    int throws = numberOfEst;
    double x, y;
    int inCricle = 0;

    for (int i = 0; i <= throws; i++)
    {
        x = (double)rand() / (RAND_MAX);
        y = (double)rand() / (RAND_MAX);

        if ((x * x) + (y * y) <= 1)
        {
            inCricle++;
        }
    }

    cout.precision(7);
    valuePI = 4.0 * inCricle / throws;
}


void serialMenu() {
    char select;

    cout << "Welcome in the Pi value estimator !";

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
        cout << "\nenter the number of estimations: ";
        std::cin >> numberOfEst;
        std::chrono::high_resolution_clock::time_point startTime;   // variables to store time data
        std::chrono::high_resolution_clock::time_point endTime;

        cout << "\nMonte Carlo estimation has started ..." << std::endl << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        startTime = std::chrono::high_resolution_clock::now();  // start measure time 
        estimatePI(numberOfEst);
        endTime = std::chrono::high_resolution_clock::now();    // stop measurment

        cout << "Approx value of PI: " << valuePI << std::endl;
        cout << "Exact value of PI: " << 22.0/7.0 << std::endl;
        cout << "Difference to exact value of PI: " << abs((22.0 / 7.0) - valuePI) << std::endl;
        cout << "Error: " << (valuePI - (22.0 / 7.0)) / (22.0 / 7.0) * 100 << " %" << std::endl;
        cout << "Time duration: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count() << " ns\n";   // endTime - starTime = time elapsed
        cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()<< " ns\n";   

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