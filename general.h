// general.h
#ifndef __GEN_H__
#define __GEN_H__
#include <stdbool.h>
#include "VehicleManager.h"

#define DOOR_NUM 5

char* myGets(char* buffer, int size);
int initYear();
int initPrice(int boolBuy);
int numOfDoors();
bool checkNumberValid(int* input);
void capitalizeWords(char* str);
void readVehiclesFromFile(VehicleManager* manager, const char* filename);
//void updateCarsFile(const VehicleManager* pManager, int carsBeforeUpdate);

// Read from binary files
void readCarsFromBinary(VehicleManager* manager, const char* filename);
void readTrucksFromBinary(VehicleManager* manager, const char* filename);
void readMotorcyclesFromBinary(VehicleManager* manager, const char* filename);

int getCapacitySize();
int getNumOfWheels();
void printWithCommas(float num);

#endif