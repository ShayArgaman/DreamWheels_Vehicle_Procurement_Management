//car.h
#ifndef __CAR_H__
#define __CAR_H__
#include "vehicleBasic.h"

//typedef enum eVehicleType eEngineType;
//typedef enum VehicleManager VehicleBasic;

typedef struct {
	VehicleBasic vehicle;
	int numOfDoors;
} Car;


void initCar(Car* pCar, int boolBuy);
void printCar(const Car* car);
void initCarForBuy(Car* pCar, int boolBuy);
void generateID(char id[ID_CAR_LENGTH + 1]);
int isCarCode(const Car* car, const int* id);
int checkIdValid(const char* str);
void getIdFromUser(char id[ID_CAR_LENGTH + 1]);

Car parseVehicleLineCar(char* line);
void freeCar(Car* pCar);

#endif