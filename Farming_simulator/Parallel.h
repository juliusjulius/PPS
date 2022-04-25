#pragma once
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

struct structure {
	int warehouseStatus;
	int warehouseCapacity;
	int field;
	bool end;
	std::mutex mtx;
	std::condition_variable cond1;
	std::condition_variable cond2;
};

void slaves(structure& data);
void master(structure& data);
void parallelMenu();