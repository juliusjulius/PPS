#include "Parallel.h"

using namespace std;

int DIMENSION = 0;

template <class T>

void Multiply(vector <vector<T>>& a, vector <vector<T>>& b, vector <vector<T>>& c, int startAt, int colls)
{

    int stopAt = startAt + colls;

    // multiply the matrixes a and b 
    for (auto j = 0; j < DIMENSION; ++j)
    {
        for (auto k = 0; k < DIMENSION; ++k)
        {
            for (auto i = startAt; i < stopAt; ++i)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


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
        char matrixType;
        int numberOfThreads = 0;
        int mulNormal = 0;
        int mulModulo = 0;
        int collsToCount = 0;
        int startAt = 0;

        cout << "\nenter the matrix dimension: ";
        std::cin >> DIMENSION;

        cout << "\nenter number of threads: ";
        std::cin >> numberOfThreads;

        cout << "\n\nchoose the matrix numbers type: ";
        cout << "\n I - int";
        cout << "\n F - float";

        cout << "\n\nChoose wisely: ";
        std::cin >> matrixType;
        std::chrono::high_resolution_clock::time_point startTime;   // variables to store time data
        std::chrono::high_resolution_clock::time_point endTime;

        if (matrixType == 'I' || matrixType == 'i')
        {
            cout << "\nMatrix multiplication has started ..." << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            vector <vector<int>> a(DIMENSION, vector<int>(DIMENSION));
            vector <vector<int>> b(DIMENSION, vector<int>(DIMENSION));
            vector <vector<int>> c(DIMENSION, vector<int>(DIMENSION, 0)); // matrix will hold result


            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < DIMENSION; i++) {
                for (int j = 0; j < DIMENSION; j++)
                {
                    a[i][j] = rand() % 10 + 1;
                    b[i][j] = rand() % 10 + 1;
                }
            }


            //splitting main task to smaller taks
            mulModulo = DIMENSION % numberOfThreads; // extra colls
            mulNormal = (DIMENSION - mulModulo) / numberOfThreads;  // number of cols to multiply is equally divided
            mulModulo += mulNormal;  // one thread will manage its own + this extra colls


            //every thread will substract number of his colls to count 
            //this number will be index of coll where it will start the multiplication
            collsToCount = DIMENSION;

            startTime = std::chrono::high_resolution_clock::now();  // start measure time 

            std::vector < std::thread > multipliers;
            for (size_t i = 0; i < numberOfThreads; i++) {
                startAt = collsToCount - mulNormal;
                multipliers.push_back(std::thread(Multiply<int>, std::ref(a), std::ref(b), std::ref(c), startAt, mulNormal));
                collsToCount = collsToCount - mulNormal; // update the intial position for other threads
            }

            // start thread with extra colls to count, ------ startAt here should be zero  
            multipliers.push_back(std::thread(Multiply<int>, std::ref(a), std::ref(b), std::ref(c), startAt, mulModulo));

            for (auto& th : multipliers) th.join();

            endTime = std::chrono::high_resolution_clock::now();    // stop measurment


            //print the result matrix
            /*cout << "\nMatrix C: " << endl;

            for (int i = 0; i < DIMENSION; i++) {
                for (int j = 0; j < DIMENSION; j++) {

                    cout << " " << c[i][j];

                    if (j == DIMENSION - 1)
                        cout << endl;
                }
            }
            */

            cout << "\nTime duration: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " s\n";   // endTime - starTime = time elapsed
            cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";

        }
        else if (matrixType == 'F' || matrixType == 'f')
        {
            cout << "\nMatrix multiplication has started ..." << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));

            vector <vector<float>> a(DIMENSION, vector<float>(DIMENSION));
            vector <vector<float>> b(DIMENSION, vector<float>(DIMENSION));
            vector <vector<float>> c(DIMENSION, vector<float>(DIMENSION, 0));     // create the target matrix c

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < DIMENSION; i++)
            {
                for (int j = 0; j < DIMENSION; j++)
                {
                    a[i][j] = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                    b[i][j] = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                }
            }


            //splitting main task to smaller taks
            mulModulo = DIMENSION % numberOfThreads; // extra colls
            mulNormal = (DIMENSION - mulModulo) / numberOfThreads;  // number of cols to multiply is equally divided
            mulModulo += mulNormal;  // one thread will manage its own + this extra colls


            //every thread will substract number of his colls to count 
            //this number will be index of coll where it will start the multiplication
            collsToCount = DIMENSION;

            startTime = std::chrono::high_resolution_clock::now();  // start measure time 

            std::vector < std::thread > multipliers;
            for (size_t i = 0; i < numberOfThreads; i++) {
                startAt = collsToCount - mulNormal;
                multipliers.push_back(std::thread(Multiply<float>, std::ref(a), std::ref(b), std::ref(c), startAt, mulNormal));
                collsToCount = collsToCount - mulNormal; // update the intial position for other threads
            }

            // start thread with extra colls to count, ------ startAt here should be zero  
            multipliers.push_back(std::thread(Multiply<float>, std::ref(a), std::ref(b), std::ref(c), startAt, mulModulo));

            for (auto& th : multipliers) th.join();

            endTime = std::chrono::high_resolution_clock::now();    // stop measurment

            /*
            //print the result matrix
            cout << "\nMatrix C: " << endl;

            for (int i = 0; i < DIMENSION; i++) {
                for (int j = 0; j < DIMENSION; j++) {

                    cout << " " << c[i][j];

                    if (j == DIMENSION - 1)
                        cout << endl;
                }
            }
            */

            cout << "\nTime duration: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " s\n";   // endTime - starTime = time elapsed
            cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
        }
        break;
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


