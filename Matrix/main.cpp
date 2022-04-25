#include <iostream>
#include <thread>
using namespace std;


int main(int argc, char* argv[]) {


	cout << "hello world - Matrix\n\n";
	unsigned int numThreads = std::thread::hardware_concurrency();

	cout  << numThreads << endl;
	return 0;
}