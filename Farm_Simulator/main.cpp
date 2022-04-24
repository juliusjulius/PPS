#include <iostream>
#include <stdlib.h> 
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>   
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <vector>

using std::cout;

struct structure {
	int warehouseStatus;
	int warehouseCapacity;
	bool end;
	std::mutex mtx;
	std::condition_variable cond1;
	std::condition_variable cond2;
};

void slaves(structure& data) {   //producer

	while (!data.end) {

		std::unique_lock<std::mutex> lck(data.mtx);

		if (data.warehouseStatus == data.warehouseCapacity) // if warehouse if full, slaves waits
		{
			cout << std::endl << "Slave: oh no, warehouse full, we rest" << std::endl;
			data.cond1.notify_one();
			data.cond2.wait(lck);
		}

		if (data.end) { // if simulation is shutdown
			data.cond1.notify_one();
			break;
		}

		data.warehouseStatus++;
		lck.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(rand() % 2 + 1));// collecting of cotton
		cout << std::hash<std::thread::id>{}(std::this_thread::get_id()) << " *Cotton collected*" << std::endl;
	}

}

void master(structure& data) {  //consumer

	while (!data.end) {

		std::unique_lock<std::mutex> lck(data.mtx);

		if (data.warehouseStatus < data.warehouseCapacity) // if warehouse isn't, master waits
		{
			data.cond1.wait(lck);
		}

		if (data.end) break;

		data.warehouseStatus = 0; // master emptie's warehouse
		cout << std::endl << "*warehouse has been emptied*" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 1));
		cout << std::endl << "Master: Why is warehouse empty ?! *whip* *whip*" << std::endl << std::endl;

		lck.unlock();

		data.cond2.notify_all();
	}
}


void menu() {

	char select;

	cout << "\n Menu";
	cout << "\n========";
	cout << "\n R - Run";
	cout << "\n I - Info";
	cout << "\n E - Exit";
	cout << "\n Choose wisely: ";

	std::cin >> select;

	switch (select) {

	case 'R':
	case 'r':
	{
		break;
	}

	case 'I':
	case 'i':
	{
		cout << "\n INFO \n Fajna uloha, pri stlaceni x sa skonci program. Program sa spusti ... \n";
		std::this_thread::sleep_for(std::chrono::seconds(4));
		break;
	}

	case 'E':
	case 'e':
	{
		abort();
	}

	default: cout << "\n oof";
	}

	cout << "\n";
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	menu();
	int warehouseCapacity;
	int numberOfSlaves;

	cout << "enter warehouse capacity: ";
	std::cin >> warehouseCapacity;

	cout << "enter number of slaves: ";
	std::cin >> numberOfSlaves;
	cout << std::endl;

	structure data{ 0, warehouseCapacity, false };

	std::thread cons(master, std::ref(data));

	std::vector<std::thread> prod;
	for (size_t i = 0; i < numberOfSlaves; i++) {
		prod.push_back(std::thread(slaves, std::ref(data)));
	}

	/*
	while (true) //kontrola stlacenia x (prerusenia)
	{
		char stlac;
		std::cin >> stlac;
		if (stlac == 'x') {
			std::unique_lock<std::mutex> lck(data.mtx);
			data.end = true;
			data.cond2.notify_all();
			lck.unlock();
			break;
		}
	}

	cout << "Program sa uspesne skoncil." << std::endl;
	cout << "Pre korektne ukoncenie stlacte klavesu";
	char x;
	std::cin >> x;*/

	cons.join();
	for (auto& th : prod) th.join();

	return 0;
}