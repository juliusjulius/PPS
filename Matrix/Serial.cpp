#include "Serial.h"
#include <vector>
using namespace std;

template <class T>

vector <vector<T>> Multiply(vector <vector<T>>& a, vector <vector<T>>& b)
{
    const int a_rows = a.size();     // a rows
    const int a_cols = a[0].size();  // a cols
    const int b_rows = b.size();     // b rows
    const int b_cols = b[0].size();  // b cols

    // multiply the matrixes a and b 
    vector <vector<T>> c(a_rows, vector<T>(b_cols, 0));
    for (auto j = 0; j < b_cols; ++j)
    {
        for (auto k = 0; k < a_cols; ++k)
        {
            for (auto i = 0; i < a_rows; ++i)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    const int c_rows = c.size(); //c rows
    const int c_cols = c[0].size(); //c cols

    //print the output matrix c
    cout << "\nOutput matrix" << endl;

    for (int i = 0; i < c_cols; i++)
    {
        for (int j = 0; j < c_rows; j++)
        {
            cout.precision(6);
            cout << " " << c[i][j];

            if (j == c_rows - 1)
            {
                cout << endl;
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


        char matrixType = 0;
        cout << "\n\nchoose the matrix numbers type: ";
        cout << "\n I - int";
        cout << "\n F - float";
        cout << "\n\nChoose wisely: ";
        std::cin >> matrixType;

        if (matrixType == 'I')
        {
            vector <vector<int>> a(matrixDim, vector<int>(matrixDim));
            vector <vector<int>> b(matrixDim, vector<int>(matrixDim));

            const int a_rows = a.size();     // a rows
            const int a_cols = a[0].size();  // a cols


            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < a_rows; i++)
            {
                for (int j = 0; j < a_cols; j++)
                {
                    int random = rand() % 10 + 1;
                    a[i][j] = random;
                }
            }


            //print the input matrix a
            cout << "\nMatrix A: " << endl;

            for (int i = 0; i < a_rows; i++)
            {
                for (int j = 0; j < a_cols; j++)
                {

                    cout << " " << a[i][j];

                    if (j == a_rows - 1)
                    {
                        cout << endl;
                    }
                }
            }

            const int b_rows = b.size();     // b rows
            const int b_cols = b[0].size();  // b cols

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < b_cols; i++)
            {
                for (int j = 0; j < b_rows; j++)
                {
                    int random = rand() % 10 + 1;
                    b[i][j] = random;
                }
            }

            cout << "---------------------------------------------" << endl;

            //print the input matrix b
            cout << "\nMatrix B" << endl;

            for (int i = 0; i < b_cols; i++)
            {
                for (int j = 0; j < b_rows; j++)
                {

                    cout << " " << b[i][j];

                    if (j == b_rows - 1)
                    {
                        cout << endl;
                    }
                }
            }

            cout << "---------------------------------------------" << endl;
            cout << "---------------------------------------------" << endl;
            auto c = Multiply(a, b);
        }
        else if (matrixType == 'F')
        {
            vector <vector<float>> a(matrixDim, vector<float>(matrixDim));
            vector <vector<float>> b(matrixDim, vector<float>(matrixDim));

            const int a_rows = a.size();     // a rows
            const int a_cols = a[0].size();  // a cols

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < a_rows; i++)
            {
                for (int j = 0; j < a_cols; j++)
                {
                    float random = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                    a[i][j] = random;
                }
            }


            //print the input matrix a
            cout << "\nMatrix A" << endl;

            for (int i = 0; i < a_rows; i++)
            {
                for (int j = 0; j < a_cols; j++)
                {
                    cout.precision(4);
                    cout << " " << a[i][j];

                    if (j == a_rows - 1)
                    {
                        cout << endl;
                    }
                }
            }

            cout << "---------------------------------------------" << endl;

            const int b_rows = b.size();     // b rows
            const int b_cols = b[0].size();  // b cols

            // fill the matrixes a with random numbers between 1 to 10
            for (int i = 0; i < b_cols; i++)
            {
                for (int j = 0; j < b_rows; j++)
                {
                    float random = 1 + (float)(rand()) / ((float)(RAND_MAX / (10 - 1)));
                    b[i][j] = random;
                }
            }


            //print the input matrix b
            cout << "\nMatrix B" << endl;

            for (int i = 0; i < b_cols; i++)
            {
                for (int j = 0; j < b_rows; j++)
                {
                    cout.precision(4);
                    cout << " " << b[i][j];

                    if (j == b_rows - 1)
                    {
                        cout << endl;
                    }
                }
            }

            cout << "---------------------------------------------" << endl;
            cout << "---------------------------------------------" << endl;
            auto c = Multiply(a, b);
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

