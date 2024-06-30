// truck.h
#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "vehicleBasic.h"

typedef struct {
    VehicleBasic vehicle;
    int capacitySize;
} Truck;

void initTruck(Truck* pTruck, int boolBuy);   // Print truck details
void printTruck(const Truck* pTruck);
void freeTruck(Truck* pTruck);

Truck parseVehicleLineTruck(char* line);
void initTruckForBuy(Truck* pTruck, int boolBuy);

#endif /* TRUCK_H */