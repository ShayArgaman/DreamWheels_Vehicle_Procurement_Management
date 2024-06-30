//vehicleBasic.h
#ifndef __MOTORCYCLE_H__
#define __MOTORCYCLE_H__
#include "vehicleBasic.h"

// Enumeration for the number of wheels
typedef enum {
	TWO_WHEELS,
	THREE_WHEELS,
	motorcycleWheelSize
} eNumOfWheels;

static const char* enumOfWheels[motorcycleWheelSize] = { "Two Wheels", "Three Wheels" };

typedef struct {
	VehicleBasic vehicle;
	eNumOfWheels numOfWheels; // Number of wheels of the motorcycle
} Motorcycle;


Motorcycle parseVehicleLineMotorcycle(char* line);
void printMotorcycle(const Motorcycle* pMotorcycle);
void initMotorcycle(Motorcycle* pMotorcycle, int boolBuy);
void initMotorcycleForBuy(Motorcycle* pMotorcycle, int boolBuy);
void freeMotorcycle(Motorcycle* pMotorcycle);


#endif
