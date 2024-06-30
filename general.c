// general.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "general.h"
#include <ctype.h>
#include "car.h"
#include "vehicleManager.h"

#define MAX_LINE_LENGTH 100

char* myGets(char* buffer, int size)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, stdin);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while (isspace(*--back));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}

int initYear()
{
	int input = 0;
	while (1)
	{
		printf("Enter year: (between: 2000-2024)\n");
		if (!checkNumberValid(&input))
		{
			printf("Invalid input! Please enter a valid number.\n");
			continue;
		}

		if (input >= 2000 && input <= 2024)
			return input;
	}
}

int initPrice(int boolBuy)
{	//booleanBuy - if 0=ADD | 1=BUY
	if (boolBuy == 0) {
		int input = 0;
		while (1)
		{
			printf("Enter price of the vehicle: (between 1$-1M$) ");
			if (!checkNumberValid(&input))
			{
				printf("Invalid input! Please enter a valid number.\n");
				continue;
			}

			if (input > 0 && input <= 999999)
				return input;
			else
				printf("Invalid input! Please enter a price between 1$ and 1M$.\n");
		}
	}
	else
	{
		srand(time(NULL));
		// Generate a random price within the range of $9,999 to $1,000,000
		return rand() % 999990001 + 9999;
	}
}

void generateID(char id[ID_CAR_LENGTH + 1])
{
	srand(time(NULL)); // Seed the random number generator with current time

	// Define the valid characters for each segment of the vehicle number
	const char* validChars[] = { "0123456789", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "0123456789" };

	int index = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			id[index++] = validChars[i][rand() % strlen(validChars[i])]; // Pick a random character from the valid set
		}
		if (i < 2) {
			id[index++] = '-'; // Add a hyphen after each segment except the last one
		}
	}
	id[ID_CAR_LENGTH] = '\0';
}

bool checkNumberValid(int* input) {
	char buffer[100];
	fgets(buffer, sizeof(buffer), stdin);

	// Remove newline character
	if (buffer[strlen(buffer) - 1] == '\n') {
		buffer[strlen(buffer) - 1] = '\0';
	}

	// Check if input is a number
	for (int i = 0; buffer[i] != '\0'; i++) {
		if (!isdigit(buffer[i])) {
			// If any character is not a digit, input is not a number
			return false;
		}
	}

	// Convert input to integer
	*input = atoi(buffer);

	return true;
}

int numOfDoors()
{

	int input;
	while (1)
	{
		printf("Enter number of doors (options: 3/5):\t");
		if (!checkNumberValid(&input))
		{
			printf("Try again. Doors needs to be a number..\n");
			continue;
		}

		if (input == DOOR_NUM - 2 || input == DOOR_NUM)
			return input;
	}
}

void capitalizeWords(char* str) {
	// Capitalize the first letter of each word
	int length = strlen(str);
	int capitalizeNext = 1; // Capitalize next character
	for (int i = 0; i < length; i++) {
		if (isspace(str[i])) {
			capitalizeNext = 1;
		}
		else if (capitalizeNext) {
			str[i] = toupper(str[i]);
			capitalizeNext = 0;
		}
		else {
			str[i] = tolower(str[i]);
		}
	}
}

int getCapacitySize() {
	int capacitySize;

	do {
		printf("Enter the capacity size (Minimum 1000 Kg): ");
		scanf("%d", &capacitySize);

		if (capacitySize < 1000) {
			printf("Error: Capacity size must be at least 1000 Kg.\n");
		}
	} while (capacitySize < 1000);

	return capacitySize;
}

int getNumOfWheels()
{
	int numOfWheels;

	printf("Enter the number of wheels (2 for two wheels, 3 for three wheels): ");
	scanf("%d", &numOfWheels);

	// Validate the input
	while (numOfWheels != 2 && numOfWheels != 3) {
		printf("Invalid input. Please enter 2 for two wheels or 3 for three wheels: ");
		scanf("%d", &numOfWheels);
	}

	return numOfWheels;
}

void readVehiclesFromFile(VehicleManager* manager, const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	char line[MAX_LINE_LENGTH];

	// Read the first line to get the number of vehicles and the type (cars, trucks, or motorcycles)
	if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
		printf("Error reading file %s\n", filename);
		fclose(file);
		return;
	}

	int numVehicles;
	char fileType[MAX_LINE_LENGTH];
	if (sscanf(line, "%s %d", fileType, &numVehicles) != 2) {
		printf("Error parsing file type or number of vehicles from file %s\n", filename);
		fclose(file);
		return;
	}

	// Validate the file type
	if (strcmp(fileType, "cars") != 0 && strcmp(fileType, "trucks") != 0 && strcmp(fileType, "motorcycles") != 0) {
		printf("Error: Unknown vehicle type in file %s\n", filename);
		fclose(file);
		return;
	}

	// Loop through the remaining lines to parse vehicle details
	for (int i = 0; i < numVehicles; ++i) {
		if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
			printf("Error reading vehicle details from file %s\n", filename);
			fclose(file);
			return;
		}
		Car car;
		Truck truck;
		Motorcycle motorcycle; // Add a variable for motorcycle

		// Determine whether it's a car, truck, or motorcycle based on the file type
		if (strcmp(fileType, "cars") == 0) {
			car = parseVehicleLineCar(line);
			addCarFromFile(manager, car);
		}
		else if (strcmp(fileType, "trucks") == 0) {
			truck = parseVehicleLineTruck(line);
			addTruckFromFile(manager, truck);
		}
		else if (strcmp(fileType, "motorcycles") == 0) {
			motorcycle = parseVehicleLineMotorcycle(line); // Parse motorcycle data
			addMotorcycleFromFile(manager, motorcycle); // Add motorcycle to manager
		}
	}

	fclose(file);
}

void readCarsFromBinary(VehicleManager* manager, const char* filename)
{
	FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	int numCars;
	// Read the number of cars from the file
	if (fread(&numCars, sizeof(int), 1, file) != 1) {
		printf("Error reading number of cars from file %s\n", filename);
		fclose(file);
		return;
	}

	// Loop through the cars and add them to the manager
	for (int i = 0; i < numCars; ++i) {
		Car car;

		// Read car details
		if (fread(&car.vehicle.engineType, sizeof(eEngineType), 1, file) != 1 ||
			fread(&car.vehicle.year, sizeof(int), 1, file) != 1 ||
			fread(&car.vehicle.color, sizeof(eColor), 1, file) != 1 ||
			fread(&car.numOfDoors, sizeof(int), 1, file) != 1 ||
			fread(car.vehicle.id, sizeof(char), ID_CAR_LENGTH, file) != ID_CAR_LENGTH ||
			fread(&car.vehicle.price, sizeof(int), 1, file) != 1) {
			printf("Error reading car details from file %s\n", filename);
			fclose(file);
			return;
		}

		// Add car to the manager
		addCarFromFile(manager, car);
	}

	fclose(file);
}



void readTrucksFromBinary(VehicleManager* manager, const char* filename)
{
	FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	int numTrucks;
	// Read the number of trucks from the file
	if (fread(&numTrucks, sizeof(int), 1, file) != 1) {
		printf("Error reading number of trucks from file %s\n", filename);
		fclose(file);
		return;
	}

	// Loop through the trucks and add them to the manager
	for (int i = 0; i < numTrucks; ++i) {
		Truck truck;

		// Read truck details
		if (fread(&truck.vehicle.engineType, sizeof(eEngineType), 1, file) != 1 ||
			fread(&truck.vehicle.year, sizeof(int), 1, file) != 1 ||
			fread(&truck.vehicle.color, sizeof(eColor), 1, file) != 1 ||
			fread(&truck.capacitySize, sizeof(int), 1, file) != 1 ||
			fread(truck.vehicle.id, sizeof(char), ID_CAR_LENGTH, file) != ID_CAR_LENGTH ||
			fread(&truck.vehicle.price, sizeof(int), 1, file) != 1) {
			printf("Error reading truck details from file %s\n", filename);
			fclose(file);
			return;
		}

		// Add truck to the manager
		addTruckFromFile(manager, truck);
	}

	fclose(file);
}


void readMotorcyclesFromBinary(VehicleManager* manager, const char* filename)
{
	FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
	if (file == NULL) {
		printf("Error opening file %s\n", filename);
		return;
	}

	int numMotorcycles;
	// Read the number of motorcycles from the file
	if (fread(&numMotorcycles, sizeof(int), 1, file) != 1) {
		printf("Error reading number of motorcycles from file %s\n", filename);
		fclose(file);
		return;
	}

	// Loop through the motorcycles and add them to the manager
	for (int i = 0; i < numMotorcycles; ++i) {
		Motorcycle motorcycle;

		// Read motorcycle details
		if (fread(&motorcycle.vehicle.engineType, sizeof(eEngineType), 1, file) != 1 ||
			fread(&motorcycle.vehicle.year, sizeof(int), 1, file) != 1 ||
			fread(&motorcycle.vehicle.color, sizeof(eColor), 1, file) != 1 ||
			fread(&motorcycle.numOfWheels, sizeof(int), 1, file) != 1 ||
			fread(motorcycle.vehicle.id, sizeof(char), ID_CAR_LENGTH, file) != ID_CAR_LENGTH ||
			fread(&motorcycle.vehicle.price, sizeof(int), 1, file) != 1) {
			printf("Error reading motorcycle details from file %s\n", filename);
			fclose(file);
			return;
		}

		// Add motorcycle to the manager
		addMotorcycleFromFile(manager, motorcycle);
	}

	fclose(file);
}




void printWithCommas(float num) {
	// Extract the integer and fractional parts separately
	int price_int = (int)num;
	float fractionalPart = num - price_int;

	// Calculate the number of thousands, millions, and the remaining amount
	int thousands = price_int / 1000;
	int remaining = price_int % 1000;

	// Print the formatted price with commas
	if (thousands > 0) {
		printf("$%d,%03d", thousands, remaining);
	}
	else {
		printf("$%d", remaining);
	}

	// Print the fractional part if it's not zero
	if (fractionalPart != 0.0f) {
		printf("%.1f", fractionalPart * 10); // Shift the fractional part one position to the left
	}
	else {
		printf(".0"); // Ensure to print a decimal point followed by zero if no fractional part
	}

	printf("\n");
}
