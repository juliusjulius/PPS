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
	int field;
	bool end;
	std::mutex mtx;
	std::condition_variable cond1;
	std::condition_variable cond2;
};

void slaves(structure& data) {   //producer

	while (!data.end) {

		std::unique_lock<std::mutex> lck(data.mtx);

		if (data.warehouseStatus == data.warehouseCapacity) // if warehouse is full, slaves waits
		{
			cout << std::endl << "Slave: oh no, warehouse full, we rest" << std::endl;
			data.cond1.notify_one();
			data.cond2.wait(lck);
		}

		if (data.end || data.field == 0) { // if simulation is shutdown
			data.cond1.notify_one();
			break;
		}

		data.field--;  // harvest cotton from field
		data.warehouseStatus++;  // add cotton to the warehouse

		cout << " *Cotton collected* " << std::endl;
		lck.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));// collecting of cotton

	}

}

void master(structure& data) {  //consumer

	while (!data.end) {

		std::unique_lock<std::mutex> lck(data.mtx);

		if (data.warehouseStatus < data.warehouseCapacity) // if warehouse isn't, master waits
		{
			data.cond1.wait(lck);
		}

		if (data.end || data.field == 0) {
			cout << std::endl << "Master: great job, field is harvested !" << std::endl;
			break;
		}

		data.warehouseStatus = 0; // master emptie's warehouse
		cout << std::endl << "*warehouse has been emptied*" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cout << std::endl << "Master: Why is warehouse empty ?! *whip* *whip*" << std::endl << std::endl;

		lck.unlock();

		data.cond2.notify_all();
	}
}


void menu() {

	char select;

	cout << "Welcome in Farming simulator !";

	cout << "\n\n Menu";
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
		int warehouseCapacity;
		int numberOfSlaves;
		int field;

		cout << "enter field size: ";
		std::cin >> field;

		cout << "enter warehouse capacity: ";
		std::cin >> warehouseCapacity;

		cout << "enter number of slaves: ";
		std::cin >> numberOfSlaves;
		cout << std::endl;

		cout << "Simulation has started, year - 1705" << std::endl << std::endl;

		structure data{ 0, warehouseCapacity, field, false };

		std::thread cons(master, std::ref(data));     //start master thread

		std::vector<std::thread> prod;
		for (size_t i = 0; i < numberOfSlaves; i++) {	//start consumer threads
			prod.push_back(std::thread(slaves, std::ref(data)));
		}


		cons.join();						//to join threads at the end
		for (auto& th : prod) th.join();
		break;
	}

	case 'I':
	case 'i':
	{
		cout << "\n INFO \n Uloha ilustruje priklad pre riesenie problemu producent - konzument. \n Slaves - su v ulohe producentov, zbieraju bavlnu z pola ktore jej ma obmedzene mnozstvo. \n"
			" Master - pokial jeho sklad plny tak ho vyprazdni, inak caka na naplnnie skladu.\n";
		std::this_thread::sleep_for(std::chrono::seconds(4));
		break;
	}

	case 'E':
	case 'e':
	{
		break;
	}

	default: cout << "\n oof";
	}

	cout << "\n";
}

int main(int argc, char* argv[]) {

	srand(time(NULL));

	menu();
	

	return 0;
}