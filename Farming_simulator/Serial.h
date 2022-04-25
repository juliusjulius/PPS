#pragma once
#include <iostream>
#include <chrono>   
#include <iostream>
#include <thread>

void serialMenu();

struct structureS {
	int warehouseStatus;
	int warehouseCapacity;
	int field;
};

void slave(structureS& data);
void master(structureS& data);