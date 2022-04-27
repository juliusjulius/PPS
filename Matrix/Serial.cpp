#include "Serial.h"
#include <vector>
using namespace std;

int DIMENSIONM = 0;

template <class T>

vector <vector<T>> Multiply(vector <vector<T>>& a, vector <vector<T>>& b, vector<vector<T>>& c)
{
    // multiply the matrixes a and b 
    for (auto j = 0; j < DIMENSIONM; ++j)
    {
        for (auto k = 0; k < DIMENSIONM; ++k)
        {
            for (auto i = 0; i < DIMENSIONM; ++i)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

void serialMenu()
{
    char select;

    cout << "Welcome in the Matrix multiplicator !";

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
        int matrixDim = 0;
        cout << "\nenter the matrix dimension: ";
        std::cin >> matrixDim;

        DIMENSIONM = matrixDim;

        char matrixType = 0;
        cout << "\n\nchoose the matrix numbers type: ";
        cout << "\n I - int";
        cout << "\n F - float";
        cout << "\n\nChoose wisely: ";
        std::cin >> matrixType;

        std::chrono::high_resolution_clock::time_point startTime;   // variables to store time data
        std::chrono::high_resolution_clock::time_point endTime;

        if (matrixType == 'I' || matrixType == 'i')
        {
            vector <vector<int>> a(DIMENSIONM, vector<int>(DIMENSIONM));
            vector <vector<int>> b(DIMENSIONM, vector<int>(DIMENSIONM));
            vector <vector<int>> c(DIMENSIONM, vector<int>(DIMENSIONM, 0));   // create the target matrix c

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < DIMENSIONM; i++)
            {
                for (int j = 0; j < DIMENSIONM; j++)
                {
                    a[i][j] = rand() % 10 + 1;
                    b[i][j] = rand() % 10 + 1;
                }
            }

            startTime = std::chrono::high_resolution_clock::now();  // start measure time 
            c = Multiply(a, b, c);
            endTime = std::chrono::high_resolution_clock::now();    // stop measurment


            //print the result matrix
            cout << "\nMatrix C: " << endl;

            /*for (int i = 0; i < DIMENSIONM; i++) {
                for (int j = 0; j < DIMENSIONM; j++) {

                    cout << " " << c[i][j];

                    if (j == DIMENSIONM - 1)
                        cout << endl;
                }
            }
            */

            cout << "\nTime duration: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " s\n";   // endTime - starTime = time elapsed
            cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
        }
        else if (matrixType == 'F' || matrixType == 'f')
        {
            vector <vector<float>> a(DIMENSIONM, vector<float>(DIMENSIONM));
            vector <vector<float>> b(DIMENSIONM, vector<float>(DIMENSIONM));
            vector <vector<float>> c(DIMENSIONM, vector<float>(DIMENSIONM, 0));             // create the target matrix c

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < DIMENSIONM; i++)
            {
                for (int j = 0; j < DIMENSIONM; j++)
                {
                    a[i][j] = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                    b[i][j] = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                }
            }

            startTime = std::chrono::high_resolution_clock::now();  // start measure time 
            c = Multiply(a, b, c);
            endTime = std::chrono::high_resolution_clock::now();    // stop measurment


            //print the result matrix
            cout << "\nMatrix C: " << endl;
            /*
            for (int i = 0; i < DIMENSIONM; i++) {
                for (int j = 0; j < DIMENSIONM; j++) {

                    cout << " " << c[i][j];

                    if (j == DIMENSIONM - 1)
                        cout << endl;
                }
            }
            */

            cout << "\nTime duration: " << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " s\n";   // endTime - starTime = time elapsed
            cout << "Time duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
        }
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

