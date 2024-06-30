//vehicleManager.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicleManager.h"
#include "orderManager.h"

void initManager(VehicleManager* manager)
{
	manager->carArr = NULL;
	manager->carCount = 0;
	manager->truckArr = NULL;
	manager->trucksCount = 0;
	manager->motorcycleArr = NULL;
	manager->motorcyclesCount = 0;
	manager->sortedByColor = false;
	manager->sortedById = false;
	manager->sortedByPrice = false;
	manager->sortedByEngineType = false;
	manager->sortedByNumOfDoors = false;
}


int addVehicle(VehicleManager* pManager, int addManual)//booleanBuy - if 0=ADD | 1=BUY
{
	int option;
	do {
		printf("Which vehicle type do you want to add?\n");
		printf("1. car\n");
		printf("2. Truck\n");
		printf("3. Motorcycle\n\n");
		scanf("%d", &option);
	} while (option < 0 || option > VEHICLE_TYPES_NUM);
	getchar();

	switch (option) {
	case 1:
		if (!addCar(pManager, addManual))
			return 0;
		break;
	case 2:
		if (!addTruck(pManager, addManual))
			return 0;
		break;
	case 3:
		if (!addMotorcycle(pManager, addManual))
			return 0;
		break;
	}

	return 1;
}

void printVehicle(VehicleManager* manager)
{
	int option;
	do {
		printf("Which vehicle type do you want to print? \n");
		printf("1. print all the available Cars\n");
		printf("2. print all the available Truck\n");
		printf("3. print all the available Motorcycle\n\n");
		scanf("%d", &option);
	} while (option < 0 || option > VEHICLE_TYPES_NUM);
	getchar();

	switch (option) {
	case 1:
		printCars(manager);
		break;
	case 2:
		printTrucks(manager);
		break;
	case 3:
		printMotorcycles(manager);
		break;
	}
}

void freeManager(VehicleManager* pManager) {
	freeTruckArr(pManager);
	freeCarArr(pManager);
	freeMotorcycleArr(pManager);
}

void printALLvehicles(const VehicleManager* manager)
{
	int vehiclesCount = manager->carCount + manager->trucksCount + manager->motorcyclesCount;
	int i;
	printf("There are %d vehicles available:\n", vehiclesCount); // Print the total number of vehicles

	if (manager->carCount > 0)
	{
		printf("\nCars:\n");
		// Iterate over the carArr array and print each car
		for (i = 0; i < manager->carCount; i++)
		{
			printf("%d) - ", i + 1); // Print index of the car
			printCar(manager->carArr[i]); // Print car details
		}
	}

	if (manager->trucksCount > 0)
	{
		printf("\nTrucks:\n");
		// Iterate over the truckArr array and print each truck
		for (i = 0; i < manager->trucksCount; i++)
		{
			printf("%d) - ", manager->carCount + i + 1); // Print index of the truck
			printTruck(manager->truckArr[i]); // Print truck details
		}
	}

	if (manager->motorcyclesCount > 0)
	{
		printf("\nMotorcycles:\n");
		// Iterate over the motorcycleArr array and print each motorcycle
		for (i = 0; i < manager->motorcyclesCount; i++)
		{
			printf("%d) - ", manager->carCount + manager->trucksCount + i + 1); // Print index of the motorcycle
			printMotorcycle(manager->motorcycleArr[i]); // Print motorcycle details
		}
	}
}

void addTruckFromFile(VehicleManager* manager, Truck truck) {
	// Reallocate memory for the truck array in the manager
	Truck** temp = (Truck**)realloc(manager->truckArr, (manager->trucksCount + 1) * sizeof(Truck*));
	if (!temp) {
		printf("Error: Memory allocation failed\n");
		return;
	}
	manager->truckArr = temp;

	// Allocate memory for the new truck and copy the data
	manager->truckArr[manager->trucksCount] = (Truck*)malloc(sizeof(Truck));
	if (!manager->truckArr[manager->trucksCount]) {
		printf("Error: Memory allocation failed\n");
		// Free the allocated memory for the truck array
		free(manager->truckArr);
		manager->truckArr = NULL;
		return;
	}

	*(manager->truckArr[manager->trucksCount]) = truck;
	manager->trucksCount++;
}

void addCarFromFile(VehicleManager* manager, Car car) {
	// Reallocate memory for the car array in the manager
	Car** temp = (Car**)realloc(manager->carArr, (manager->carCount + 1) * sizeof(Car*));
	if (!temp) {
		printf("Error: Memory allocation failed\n");
		return;
	}
	manager->carArr = temp;

	// Allocate memory for the new car and copy the data
	manager->carArr[manager->carCount] = (Car*)malloc(sizeof(Car));
	if (!manager->carArr[manager->carCount]) {
		printf("Error: Memory allocation failed\n");
		// Free the allocated memory for the car array
		free(manager->carArr);
		manager->carArr = NULL;
		return;
	}

	*(manager->carArr[manager->carCount]) = car;
	manager->carCount++;
}

void updateCarsFile(const VehicleManager* pManager, int carsBeforeUpdate)
{
	FILE* file = fopen("cars.txt", "r+"); // Open the file in read and write mode
	if (file == NULL) {
		printf("Error opening cars.txt for writing.\n");
		return;
	}

	// Update the vehicle count in the file
	fprintf(file, "cars %d\n", pManager->carCount);

	// Move the file pointer to the end of the file
	fseek(file, 0, SEEK_END);

	// Iterate over the carArr array and append each car's details to the file
	for (int i = carsBeforeUpdate; i < pManager->carCount; ++i) {
		const Car* car = pManager->carArr[i];
		fprintf(file, "%d %d %s %s %d %d\n", car->vehicle.engineType, car->vehicle.year, colorStr[car->vehicle.color],
			car->vehicle.id, car->vehicle.price, car->numOfDoors);
	}

	fclose(file); // Close the file
}

void addMotorcycleFromFile(VehicleManager* manager, Motorcycle motorcycle)
{
	// Reallocate memory for the motorcycle array in the manager
	Motorcycle** temp = (Motorcycle**)realloc(manager->motorcycleArr, (manager->motorcyclesCount + 1) * sizeof(Motorcycle*));
	if (!temp) {
		printf("Error: Memory allocation failed\n");
		return;
	}
	manager->motorcycleArr = temp;

	// Allocate memory for the new motorcycle and copy the data
	manager->motorcycleArr[manager->motorcyclesCount] = (Motorcycle*)malloc(sizeof(Motorcycle));
	if (!manager->motorcycleArr[manager->motorcyclesCount]) {
		printf("Error: Memory allocation failed\n");
		// Free the allocated memory for the motorcycle array
		free(manager->motorcycleArr);
		manager->motorcycleArr = NULL;
		return;
	}

	*(manager->motorcycleArr[manager->motorcyclesCount]) = motorcycle;
	manager->motorcyclesCount++;
}

void updateTrucksFile(const VehicleManager* pManager, int trucksBeforeUpdate)
{
	FILE* file = fopen("trucks.txt", "r+"); // Open the file in read and write mode
	if (file == NULL) {
		printf("Error opening trucks.txt for writing.\n");
		return;
	}

	// Update the vehicle count in the file
	fprintf(file, "trucks %d\n", pManager->trucksCount);

	// Move the file pointer to the end of the file
	fseek(file, 0, SEEK_END);

	// Iterate over the truckArr array and append each truck's details to the file
	for (int i = trucksBeforeUpdate; i < pManager->trucksCount; ++i) {
		const Truck* truck = pManager->truckArr[i];
		fprintf(file, "%d %d %s %s %d %d\n", truck->vehicle.engineType, truck->vehicle.year, colorStr[truck->vehicle.color],
			truck->vehicle.id, truck->vehicle.price, truck->capacitySize);
	}

	fclose(file); // Close the file
}

void updateMotorcyclesFile(const VehicleManager* pManager, int motorcyclesBeforeUpdate)
{
	FILE* file = fopen("motorcycles.txt", "r+"); // Open the file in read and write mode
	if (file == NULL) {
		printf("Error opening motorcycles.txt for writing.\n");
		return;
	}

	// Update the vehicle count in the file
	fprintf(file, "motorcycles %d\n", pManager->motorcyclesCount);

	// Move the file pointer to the end of the file
	fseek(file, 0, SEEK_END);

	// Iterate over the motorcycleArr array and append each motorcycle's details to the file
	for (int i = motorcyclesBeforeUpdate; i < pManager->motorcyclesCount; ++i) {
		const Motorcycle* motorcycle = pManager->motorcycleArr[i];
		fprintf(file, "%d %d %s %s %d %d\n", motorcycle->vehicle.engineType, motorcycle->vehicle.year, colorStr[motorcycle->vehicle.color],
			motorcycle->vehicle.id, motorcycle->vehicle.price, motorcycle->numOfWheels);
	}

	fclose(file); // Close the file
}

void writeCarsToBinary(const VehicleManager* pManager, const char* filename)
{
	FILE* file = fopen(filename, "wb"); // Open the file in binary write mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	// Write the vehicle count to the file
	fwrite(&pManager->carCount, sizeof(int), 1, file);

	// Write each car's details to the file
	for (int i = 0; i < pManager->carCount; ++i) {
		const Car* car = pManager->carArr[i];
		fwrite(&car->vehicle.engineType, sizeof(eEngineType), 1, file);
		fwrite(&car->vehicle.year, sizeof(int), 1, file);
		fwrite(&car->vehicle.color, sizeof(eColor), 1, file);
		fwrite(&car->numOfDoors, sizeof(int), 1, file);
		fwrite(car->vehicle.id, sizeof(char), ID_CAR_LENGTH, file);
		fwrite(&car->vehicle.price, sizeof(int), 1, file);
	}

	fclose(file); // Close the file
}

void writeTrucksToBinary(const VehicleManager* pManager, const char* filename)
{
	FILE* file = fopen(filename, "wb"); // Open the file in binary write mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	// Write the vehicle count to the file
	fwrite(&pManager->trucksCount, sizeof(int), 1, file);

	// Write each truck's details to the file
	for (int i = 0; i < pManager->trucksCount; ++i) {
		const Truck* truck = pManager->truckArr[i];
		fwrite(&truck->vehicle.engineType, sizeof(eEngineType), 1, file);
		fwrite(&truck->vehicle.year, sizeof(int), 1, file);
		fwrite(&truck->vehicle.color, sizeof(eColor), 1, file);
		fwrite(&truck->capacitySize, sizeof(int), 1, file);
		fwrite(truck->vehicle.id, sizeof(char), ID_CAR_LENGTH, file);
		fwrite(&truck->vehicle.price, sizeof(int), 1, file);
	}

	fclose(file); // Close the file
}


void freeMotorcycleArr(VehicleManager* pManager) {
	if (pManager->motorcycleArr != NULL) {
		for (int i = 0; i < pManager->motorcyclesCount; i++) {
			freeMotorcycle(pManager->motorcycleArr[i]);
			//free(pManager->motorcycleArr[i]);
		}
		free(pManager->motorcycleArr);
	}
}

void freeTruckArr(VehicleManager* pManager) {
	if (pManager->truckArr != NULL) {
		for (int i = 0; i < pManager->trucksCount; i++) {
			freeTruck(pManager->truckArr[i]);
			//free(pManager->truckArr[i]);
		}
		free(pManager->truckArr);
	}
}

void freeCarArr(VehicleManager* pManager) {
	if (pManager->carArr != NULL) {
		for (int i = 0; i < pManager->carCount; i++) {
			freeCar(pManager->carArr[i]);
			//free(pManager->carArr[i]);
		}
		free(pManager->carArr);
	}
}

void writeMotorcyclesToBinary(const VehicleManager* pManager, const char* filename)
{
	FILE* file = fopen(filename, "wb"); // Open the file in binary write mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	// Write the vehicle count to the file
	fwrite(&pManager->motorcyclesCount, sizeof(int), 1, file);

	// Write each motorcycle's details to the file
	for (int i = 0; i < pManager->motorcyclesCount; ++i) {
		const Motorcycle* motorcycle = pManager->motorcycleArr[i];
		fwrite(&motorcycle->vehicle.engineType, sizeof(eEngineType), 1, file);
		fwrite(&motorcycle->vehicle.year, sizeof(int), 1, file);
		fwrite(&motorcycle->vehicle.color, sizeof(eColor), 1, file);
		fwrite(&motorcycle->numOfWheels, sizeof(int), 1, file);
		fwrite(motorcycle->vehicle.id, sizeof(char), ID_CAR_LENGTH, file);
		fwrite(&motorcycle->vehicle.price, sizeof(int), 1, file);
	}

	fclose(file); // Close the file
}


Car* addCar(VehicleManager* pManager, int boolBuy) // boolean - if 0=ADD | 1=BUY
{

	Car* pCar = (Car*)calloc(1, sizeof(Car)); // Allocate memory for the vehicle
	if (!pCar) return 0;

	if (!boolBuy)
	{
		initCar(pCar, boolBuy);
		printCar(pCar);    // Print car details

		pManager->carArr = (Car**)realloc(pManager->carArr, (pManager->carCount + 1) * sizeof(Car*));
		if (!pManager->carArr) {
			free(pCar); // Free the allocated car memory
			return 0;
		}
		// Add the new car to the vehicle array in the manager
		pManager->carArr[pManager->carCount] = pCar;
		pManager->carCount++;
		RESET_SORT_FLAGS_ALL_FALSE(pManager);
	}
	else
	{
		initCarForBuy(pCar, boolBuy);
	}
	printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
	printCar(pCar);    // Print car details

	return pCar;
}

eColor getColor()
{
	int option;
	do {
		printf("Please enter one of the following colors:\n");
		for (int i = 0; i < colorSize; i++) {
			switch (i) {
			case black:
				printf(ANSI_COLOR_BLACK "%d) - Black" ANSI_COLOR_RESET "\n", i);
				break;
			case white:
				printf(ANSI_COLOR_WHITE "%d) - White" ANSI_COLOR_RESET "\n", i);
				break;
			case blue:
				printf(ANSI_COLOR_BLUE "%d) - Blue" ANSI_COLOR_RESET "\n", i);
				break;
			case silver:
				printf(ANSI_COLOR_WHITE "%d) - Silver" ANSI_COLOR_RESET "\n", i);
				break;
			case red:
				printf(ANSI_COLOR_RED "%d) - Red" ANSI_COLOR_RESET "\n", i);
				break;
			case green:
				printf(ANSI_COLOR_GREEN "%d) - Green" ANSI_COLOR_RESET "\n", i);
				break;
			case yellow:
				printf(ANSI_COLOR_YELLOW "%d) - Yellow" ANSI_COLOR_RESET "\n", i);
				break;
			default:
				printf("%d) - Unknown Color\n", i);
				break;
			}
		}
		printf("Your choice: ");
		scanf("%d", &option);
	} while (option < 0 || option >= colorSize);
	getchar();

	return (eColor)option;
}



void printCars(const VehicleManager* pManager)
{
	printf("There are %d cars available\n", pManager->carCount); // Print the total number of cars

	// Iterate over the vehicleArr array and print each car
	for (int i = 0; i < pManager->carCount; i++)
	{
		if (i < 9)printf("  (%d)  ", i + 1); // Print index of the car
		else printf("  (%d) ", i + 1);
		printCar(pManager->carArr[i]); // Print car details
	}
}

eEngineType getEngineType()
{
	int option;
	do {
		printf("Please enter one the following types:\n");
		for (int i = 0; i < vehicleTypeSize; i++)
			printf("%d - %s\n", i, engineTypeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= VEHICLE_TYPES_NUM);
	getchar();

	return (eEngineType)option;
}

Truck* addTruck(VehicleManager* pManager, int boolBuy) {
	Truck* pTruck = (Truck*)calloc(1, sizeof(Truck)); // Allocate memory for the vehicle
	if (!pTruck) return 0;

	if (!boolBuy) {
		initTruck(pTruck, boolBuy);
		printTruck(pTruck);    // Print truck details

		pManager->truckArr = (Truck**)realloc(pManager->truckArr, (pManager->trucksCount + 1) * sizeof(Truck*));
		if (!pManager->truckArr) {
			free(pTruck); // Free the allocated truck memory
			return 0;
		}
		// Add the new truck to the vehicle array in the manager
		pManager->truckArr[pManager->trucksCount] = pTruck;
		pManager->trucksCount++;
		RESET_SORT_FLAGS_ALL_FALSE(pManager);
	}
	else {
		initTruckForBuy(pTruck, boolBuy);
	}
	printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
	printTruck(pTruck);    // Print car details
	return pTruck;
}


void printTrucks(const VehicleManager* pManager)
{
	printf("\nThere are %d trucks available\n", pManager->trucksCount); // Print the total number of trucks

	// Iterate over the vehicleArr array and print each truck
	for (int i = 0; i < pManager->trucksCount; i++)
	{
		printf("%d) - ", i + 1); // Print index of the truck
		printTruck(pManager->truckArr[i]); // Print truck details
	}
}

Motorcycle* addMotorcycle(VehicleManager* pManager, int boolBuy)
{
	Motorcycle* pMotorcycle = (Motorcycle*)calloc(1, sizeof(Motorcycle)); // Allocate memory for the motorcycle
	if (!pMotorcycle) return NULL;

	if (!boolBuy) {
		initMotorcycle(pMotorcycle, boolBuy);
		printMotorcycle(pMotorcycle);    // Print motorcycle details

		pManager->motorcycleArr = (Motorcycle**)realloc(pManager->motorcycleArr, (pManager->motorcyclesCount + 1) * sizeof(Motorcycle*));
		if (!pManager->motorcycleArr) {
			free(pMotorcycle); // Free the allocated motorcycle memory
			return NULL;
		}
		// Add the new motorcycle to the vehicle array in the manager
		pManager->motorcycleArr[pManager->motorcyclesCount] = pMotorcycle;
		pManager->motorcyclesCount++;
	}
	else {
		initMotorcycleForBuy(pMotorcycle, boolBuy);
	}
	printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
	printMotorcycle(pMotorcycle);    // Print motorcycle details
	return pMotorcycle;
}

void printMotorcycles(const VehicleManager* pManager)
{
	printf("\nThere are %d motorcycles available\n", pManager->motorcyclesCount); // Print the total number of motorcycles

	// Iterate over the motorcycleArr array and print each motorcycle
	for (int i = 0; i < pManager->motorcyclesCount; i++)
	{
		printf("%d) - ", i + 1); // Print index of the motorcycle
		printMotorcycle(pManager->motorcycleArr[i]); // Print motorcycle details
	}
}



int removeCar(VehicleManager* manager, char* carId)// afterwards change to scan from user 
{
	int index = findCarIndexById(manager->carArr, manager->carCount, carId);
	if (index == -1)
		return 0;
	else
	{
		free(manager->carArr[index]);
		manager->carArr[index] = manager->carArr[manager->carCount - 1];
		manager->carArr[manager->carCount - 1] = NULL;
		manager->carCount--;
		RESET_SORT_FLAGS_ALL_FALSE(manager);
		return 1;
	}
}

int removeTruck(VehicleManager* manager, char* TruckId)// afterwards change to scan from user 
{
	int index = findCarIndexById(manager->truckArr, manager->trucksCount, TruckId);
	if (index == -1)
		return 0;
	else
	{
		free(manager->truckArr[index]);
		manager->truckArr[index] = manager->truckArr[manager->trucksCount - 1];
		manager->truckArr[manager->trucksCount - 1] = NULL;
		manager->trucksCount--;
		RESET_SORT_FLAGS_ALL_FALSE(manager);
		return 1;
	}
}

int removeMotorcycle(VehicleManager* manager, char* MotorId)// afterwards change to scan from user 
{
	int index = findMotorcycleIndexById(manager->motorcycleArr, manager->motorcyclesCount, MotorId);
	if (index == -1)
		return 0;
	else
	{
		free(manager->motorcycleArr[index]);//free pointer
		manager->motorcycleArr[index] = manager->motorcycleArr[manager->motorcyclesCount - 1];
		manager->motorcycleArr[manager->motorcyclesCount - 1] = NULL;
		manager->motorcyclesCount--;
		RESET_SORT_FLAGS_ALL_FALSE(manager);
		return 1;
	}
}


// returns index of carpointer in car arr, if not found: -1.
int findCarIndexById(const Car** carsArr, int carsCount, char* id)
{
	for (int i = 0; i < carsCount; i++)
	{
		if (strcmp(carsArr[i]->vehicle.id, id) == 0)
			return i;
	}
	return -1;

}

int findTruckIndexById(const Truck** trucksArr, int trucksCount, char* id)
{
	for (int i = 0; i < trucksCount; i++)
	{
		if (strcmp(trucksArr[i]->vehicle.id, id) == 0)//both are equal
			return i;
	}
	return -1;

}

int findMotorcycleIndexById(const Motorcycle** motorcyclesArr, int motorcyclesCount, char* id)
{
	for (int i = 0; i < motorcyclesCount; i++)
	{
		if (strcmp(motorcyclesArr[i]->vehicle.id, id) == 0)//both are equal
			return i;
	}
	return -1;

}


int compareById(void* a, void* b)
{
	Car* car1 = *(Car**)a;
	Car* car2 = *(Car**)b;
	if (strcmp(car1->vehicle.id, car2->vehicle.id) > 0)
		return 1;
	else if (strcmp(car1->vehicle.id, car2->vehicle.id) < 0)
		return -1;
	else
		return 0;
}



int compareByColor(const void* a, const void* b)
{
	Car* carA = *(Car**)a;
	Car* carB = *(Car**)b;
	return carA->vehicle.color - carB->vehicle.color;//equal - 0, a>b positive, b>a negative
}

int compareByEngineType(const void* a, const void* b)
{
	Car* carA = *(Car**)a;
	Car* carB = *(Car**)b;
	return carA->vehicle.engineType - carB->vehicle.engineType;//equal - 0, a>b positive, b>a negative
}

int compareByPrice(void* a, void* b)
{
	Car* carA = *(Car**)a;
	Car* carB = *(Car**)b;
	return carA->vehicle.price - carB->vehicle.price;//equal - 0, a>b positive, b>a negative
}

int compareByNumOfDoors(void* a, void* b)
{
	Car* carA = *(Car**)a;
	Car* carB = *(Car**)b;
	return carA->numOfDoors - carB->numOfDoors;//equal - 0, a>b positive, b>a negative
}


void* binarySearch(void** arr, int size, void* target, int (*cmp)(void*, void*)) {
	Car** array = (Car**)arr;


	int low = 0;
	int high = size - 1;

	while (low <= high) {
		int mid = low + (high - low) / 2;

		// Compare the middle element with the target
		int comparison = cmp(&array[mid], &target);//TODO consider write a macro

		if (comparison == 0) {
			// Element found, return its address
			return array[mid];
		}
		else if (comparison < 0) {
			// If middle element is smaller, ignore the left half
			low = mid + 1;
		}
		else {
			// If middle element is larger, ignore the right half
			high = mid - 1;
		}
	}

	// Element not found
	return NULL;
}

void updateSortKinds(VehicleManager* manager, bool sortedByColor, bool sortedById, bool sortedByPrice, bool sortedByEngineType, bool sortedByNumOfDoors)// to know if array is sorted by somethig rightnow
{
	manager->sortedByColor = sortedByColor;
	manager->sortedById = sortedById;
	manager->sortedByPrice = sortedByPrice;
	manager->sortedByEngineType = sortedByEngineType;
	manager->sortedByNumOfDoors = sortedByNumOfDoors;
	//TODO add those to arguments
}
void sortByColor(VehicleManager* manager)//TODO implement h and 2 other sorts
{
	qsort(manager->carArr, manager->carCount, sizeof(Car*), compareByColor);
	FLAGS_SORT_BY_COLOR(manager);
}

void sortById(VehicleManager* manager)//TODO implement h and 2 other sorts
//TODO check if its void
{
	qsort(manager->carArr, manager->carCount, sizeof(Car*), compareById);
	FLAGS_SORT_BY_ID(manager);
}

void sortByPrice(VehicleManager* manager)//TODO implement h and 2 other sorts
{
	qsort(manager->carArr, manager->carCount, sizeof(Car*), compareByPrice);
	FLAGS_SORT_BY_PRICE(manager);
}

void sortByEngineType(VehicleManager* manager)//TODO implement h and 2 other sorts
{
	qsort(manager->carArr, manager->carCount, sizeof(Car*), compareByEngineType);
	FLAGS_SORT_BY_ENGINETYPE(manager);
}

void sortByNumOfDoors(VehicleManager* manager)//TODO implement h and 2 other sorts
{
	qsort(manager->carArr, manager->carCount, sizeof(Car*), compareByNumOfDoors);
	FLAGS_SORT_BY_NUMOFDOORS(manager);
}

void colorBSearchType(VehicleManager* manager)
{
	if (manager->sortedByColor == false)//check if already sorted
		sortByColor(manager);
	//  printf("what color would u like the car to be?");//TODO check shay getcolor
	eColor color = getColor();// scan color from user
	//  scanf("%d", color);
	Car** carPtr = (Car**)malloc(sizeof(Car*));
	*carPtr = (Car*)malloc(sizeof(Car));
	(*carPtr)->vehicle.color = color;
	//initialize car with the color, consider doing modulari.

	Car* foundCar = (Car*)binarySearch((void**)manager->carArr, manager->carCount, *carPtr, compareByColor);
	if (!foundCar)
	{
		printf("currently, there is no %s car ", colorStr[color]);
		return;
	}
	else
	{
		printCar(foundCar);// just print - allocate it, if u want to return, and not just print like here
	}

	free(*carPtr);
	free(carPtr);
}

void idBSearchType(VehicleManager* manager)
{
	if (manager->sortedById == false) //check if already sorted
		sortById(manager);

	char id[ID_CAR_LENGTH + 1]; // Declare an array to store the ID

	getIdFromUser(id);

	Car** carPtr = (Car**)malloc(sizeof(Car*));
	*carPtr = (Car*)malloc(sizeof(Car));
	strcpy((*carPtr)->vehicle.id, id);


	Car* foundCar = (Car*)binarySearch((void**)manager->carArr, manager->carCount, *carPtr, compareById);
	if (!foundCar)
	{
		printf("sorry, couldn't find car with this exact id!!");
		return;
	}
	else
	{
		printCar(foundCar);// just print - allocate it, if u want to return, and not just print like here
	}
	free(*carPtr);
	free(carPtr);
}

void priceBSearchType(VehicleManager* manager)
{
	if (manager->sortedByPrice == false)//check if already sorted
		sortByPrice(manager);
	int price = initPrice(0);
	Car** carPtr = (Car**)malloc(sizeof(Car*));
	*carPtr = (Car*)malloc(sizeof(Car));
	(*carPtr)->vehicle.price = price;

	Car* foundCar = (Car*)binarySearch((void**)manager->carArr, manager->carCount, *carPtr, compareByPrice);
	if (!foundCar)
	{
		printf("currently, there is no car that costs %d\n", price);
		return;
	}
	else
	{
		printCar(foundCar);// just print - allocate it, if u want to return, and not just print like here
	}
	free(*carPtr);
	free(carPtr);
}

void numOfDoorsBSearchType(VehicleManager* manager)
{
	if (manager->sortedByNumOfDoors == false)//check if already sorted
		sortByNumOfDoors(manager);
	int doorsNum = numOfDoors();
	Car** carPtr = (Car**)malloc(sizeof(Car*));
	*carPtr = (Car*)malloc(sizeof(Car));
	(*carPtr)->numOfDoors = doorsNum;

	Car* foundCar = (Car*)binarySearch((void**)manager->carArr, manager->carCount, *carPtr, compareByNumOfDoors);
	if (!foundCar)
	{
		printf("currently, there is no car that have %d doors\n", doorsNum);
		return;
	}
	else
	{
		printCar(foundCar);// just print - allocate it, if u want to return, and not just print like here
	}
	free(*carPtr);
	free(carPtr);
}

void EngineTypeBSearchType(VehicleManager* manager)
{
	if (manager->sortedByEngineType == false)//check if already sorted
		sortByEngineType(manager);

	eColor engineType = getEngineType();// scan color from user

	Car** carPtr = (Car**)malloc(sizeof(Car*));
	*carPtr = (Car*)malloc(sizeof(Car));
	(*carPtr)->vehicle.engineType = engineType;

	//initialize car with the color, consider doing modulari.
	Car* foundCar = (Car*)binarySearch((void**)manager->carArr, manager->carCount, *carPtr, compareByEngineType);
	if (!foundCar)
	{
		printf("Currently, there is no  %s engine car", engineTypeStr[engineType]);
		return;
	}
	else
	{
		printCar(foundCar);
	}

	free(*carPtr);
	free(carPtr);
}




void chooseSearchType(VehicleManager* manager)
{
	int option;
	printf("Please choose search type:\n");
	printf("1. Color\n");
	printf("2. Id\n");
	printf("3. Price\n");
	printf("4. NumOfDoors\n");
	printf("5. EngineType\n");

	scanf("%d", &option);
	switch (option)
	{
	case 1:
	{
		colorBSearchType(manager);
		break;
	}
	case 2:
	{
		idBSearchType(manager);
		break;
	}

	case 3:
	{
		priceBSearchType(manager);
		break;
	}

	case 4:
	{
		numOfDoorsBSearchType(manager);
		break;
	}
	case 5:
	{
		EngineTypeBSearchType(manager);
		break;
	}
	default:
		break;
	}
}


void chooseSortType(VehicleManager* manager)
{
	int option;
	printf("Sort cars by:  \n");
	printf("1. Color\n");
	printf("2. Id\n");
	printf("3. Price\n");
	printf("4. EngineType\n");
	printf("5. NumOfDoors\n");

	scanf("%d", &option);
	switch (option)
	{
	case 1:
	{
		sortByColor(manager);
		printCars(manager);
		break;
	}
	case 2:
	{
		sortById(manager);
		printCars(manager);
		break;
	}

	case 3:
	{
		sortByPrice(manager);
		printCars(manager);
		break;
	}
	case 4:
	{
		sortByEngineType(manager);
		printCars(manager);
		break;
	}
	case 5:
	{
		sortByNumOfDoors(manager);
		printCars(manager);
		break;
	}
	default:
		break;
	}
}



