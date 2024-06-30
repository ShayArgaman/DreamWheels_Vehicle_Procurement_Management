//vehicleManager.h
#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include <stdbool.h>
#include "car.h"
#include "truck.h"
#include "motorcycle.h"
#define VEHICLE_TYPES_NUM 3
#define MAX_ID_LEN 8

// sort flags macros
#define RESET_SORT_FLAGS_ALL_FALSE(manager) \
    do { \
        updateSortKinds(manager, false, false, false, false, false); \
    } while(0)
#define FLAGS_SORT_BY_COLOR(manager) \
    do { \
        updateSortKinds(manager, true, false, false, false, false); \
    } while(0)

#define FLAGS_SORT_BY_ID(manager) \
    do { \
        updateSortKinds(manager, false, true, false, false, false); \
    } while(0)
#define FLAGS_SORT_BY_PRICE(manager) \
    do { \
        updateSortKinds(manager, false, false, true, false, false); \
    } while(0)
#define FLAGS_SORT_BY_ENGINETYPE(manager) \
    do { \
        updateSortKinds(manager, false, false, false, true, false); \
    } while(0)
#define FLAGS_SORT_BY_NUMOFDOORS(manager) \
    do { \
        updateSortKinds(manager, false, false, false, false, true); \
    } while(0)

typedef struct
{
	Truck** truckArr;
	int trucksCount;
	Car** carArr;
	int carCount;
	Motorcycle** motorcycleArr;
	int motorcyclesCount;
	bool sortedByColor;
	bool sortedById;
	bool sortedByPrice;
	bool sortedByEngineType;
	bool sortedByNumOfDoors;
} VehicleManager;

int addVehicle(VehicleManager* pManager, int addManual); //booleanBuy - if 0=ADD | 1=BUY
void initManager(VehicleManager* manager);
eEngineType getEngineType();
Car* addCar(VehicleManager* manager, int boolBuy); // boolean - if 0=ADD | 1=BUY
void printCars(const VehicleManager* pManager);
Truck* addTruck(VehicleManager* pManager, int boolBuy);
void printTrucks(const VehicleManager* pManager);

Motorcycle* addMotorcycle(VehicleManager* pManager, int boolBuy);
void printMotorcycles(const VehicleManager* pManager);
void printVehicle(VehicleManager* manager);
void printALLvehicles(const VehicleManager* manager);
eColor getColor();
int removeCar(VehicleManager* manager, char* carId);
int removeTruck(VehicleManager* manager, char* TruckId);
int removeMotorcycle(VehicleManager* manager, char* vehicleID);
int findCarIndexById(const Car** carsArr, int carsCount, char* id);
int findTruckIndexById(const Truck** trucksArr, int trucksCount, char* id);
int findMotorcycleIndexById(const Motorcycle** motorcyclesArr, int motorcyclesCount, char* id);
int compareById(void* a, void* b);
int compareByColor(void* a, void* b);
int compareByEngineType(const void* a, const void* b);
int compareByPrice(void* a, void* b);
int compareByNumOfDoors(void* a, void* b);

void* binarySearch(void** arr, int size, void* target, int (*cmp)(void*, void*));
void updateSortKinds(VehicleManager* manager, bool sortedByColor, bool sortedById, bool sortedByPrice, bool sortedByEngineType, bool sortedByNumOfDoors);// to know if array is sorted by somethig rightnow
void sortByColor(VehicleManager* manager);
void sortById(VehicleManager* manager);
void sortByPrice(VehicleManager* manager);
void sortByEngineType(VehicleManager* manager);
void sortByNumOfDoors(VehicleManager* manager);
void colorBSearchType(VehicleManager* manager);//just scan from user,doing binary search and prints
void idBSearchType(VehicleManager* manager);//""
void priceBSearchType(VehicleManager* manager);//""

void chooseSearchType(VehicleManager* manager);//menu
void chooseSortType(VehicleManager* manager);

void addTruckFromFile(VehicleManager* manager, Truck truck);
void addCarFromFile(VehicleManager* manager, Car car);
void addMotorcycleFromFile(VehicleManager* manager, Motorcycle motorcycle);

void updateCarsFile(const VehicleManager* pManager, int carsBeforeUpdate);
void updateTrucksFile(const VehicleManager* pManager, int trucksBeforeUpdate);
void updateMotorcyclesFile(const VehicleManager* pManager, int motorcyclesBeforeUpdate);

// Writing to a binary file
void writeCarsToBinary(const VehicleManager* pManager, const char* filename);
void writeTrucksToBinary(const VehicleManager* pManager, const char* filename);
void writeMotorcyclesToBinary(const VehicleManager* pManager, const char* filename);

//free functions
void freeManager(VehicleManager* pManager);
void freeMotorcycleArr(VehicleManager* pManager);
void freeTruckArr(VehicleManager* pManager);
void freeCarArr(VehicleManager* pManager);

#endif