#pragma once
#include <iostream>
#include <chrono>   
#include <iostream>
#include <thread>

void serialMenu();
void slave(structureS& data);
void master(structureS& data);

struct structureS{
	int warehouseStatus;
	int warehouseCapacity;
	int field;
};