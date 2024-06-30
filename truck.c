//truck.c
// truck.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicleManager.h"
#include "truck.h"
#include "general.h"

void initTruck(Truck* pTruck, int boolBuy)
{
	pTruck->vehicle.engineType = getEngineType();

	pTruck->vehicle.year = initYear();

	pTruck->vehicle.price = initPrice(boolBuy); // random for buy

	generateID(pTruck->vehicle.id); // Generate and assign the ID

	pTruck->vehicle.color = getColor();

	pTruck->capacitySize = getCapacitySize();

	pTruck->vehicle.vehicleType = ITS_A_TRUCK;
}

void printTruck(const Truck* pTruck) {
	if (!pTruck) {
		printf("No truck information available.\n");
		return;
	}
	// Print truck details
	printf("| Truck Engine Type: %s | Year: %4d | ", engineTypeStr[pTruck->vehicle.engineType], pTruck->vehicle.year);

	// Print color with ANSI escape code
	switch (pTruck->vehicle.color) {
	case black:
		printf(ANSI_COLOR_BLACK);
		break;
	case white:
		printf(ANSI_COLOR_WHITE);
		break;
	case blue:
		printf(ANSI_COLOR_BLUE);
		break;
	case silver:
		printf(ANSI_COLOR_CYAN);
		break;
	case red:
		printf(ANSI_COLOR_RED);
		break;
	case green:
		printf(ANSI_COLOR_GREEN);
		break;
	case yellow:
		printf(ANSI_COLOR_YELLOW);
		break;
	default:
		printf(ANSI_COLOR_RESET); // Default color
	}

	printf("Color: %s | ", colorStr[pTruck->vehicle.color]);
	printf(ANSI_COLOR_RESET); // Reset color
	printf("Capacity Size: %d kg | ", pTruck->capacitySize); // The maximum weight of cargo that the truck can carry (Kg)
	printf("ID: %s | ", pTruck->vehicle.id);

	if (pTruck->vehicle.price < 1000) {
		printf("Price: $%d\n", pTruck->vehicle.price);
	}
	else {
		int price = pTruck->vehicle.price;
		int billions = price / 1000000000;
		int millions = (price / 1000000) % 1000;
		int thousands = (price / 1000) % 1000;
		int remaining = price % 1000;
		if (billions > 0) {
			printf("Price: $%d,%03d,%03d,%03d\n", billions, millions, thousands, remaining);
		}
		else if (millions > 0) {
			printf("Price: $%d,%03d,%03d\n", millions, thousands, remaining);
		}
		else {
			printf("Price: $%d,%03d\n", thousands, remaining);
		}
	}
}

void initTruckForBuy(Truck* pTruck, int boolBuy)
{
	pTruck->vehicle.engineType = getEngineType();

	pTruck->vehicle.year = initYear();

	pTruck->vehicle.price = initPrice(boolBuy); // random

	generateID(pTruck->vehicle.id); // Generate and assign the ID

	pTruck->vehicle.color = getColor(); //make init color

	pTruck->capacitySize = getCapacitySize();

	pTruck->vehicle.vehicleType = ITS_A_TRUCK;

	printf("\n");
}



Truck parseVehicleLineTruck(char* line) {
	Truck truck;

	// Tokenize the line
	char* token = strtok(line, " ");

	// Check if engine type token exists
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Engine type token not found\n");
		return truck; // Returning an uninitialized truck
	}
	truck.vehicle.engineType = (eEngineType)atoi(token);

	// Get the next token (year)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Year token not found\n");
		return truck; // Returning an uninitialized truck
	}
	truck.vehicle.year = atoi(token);

	// Get the next token (color)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Color token not found\n");
		return truck; // Returning an uninitialized truck
	}
	// Convert color string to eColor enumeration value
	for (int i = 0; i < colorSize; ++i) {
		if (strcmp(token, colorStr[i]) == 0) {
			truck.vehicle.color = (eColor)i;
			break;
		}
	}

	// Get the next token (id)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: ID token not found\n");
		return truck; // Returning an uninitialized truck
	}
	// Copy id token into the id array
	strncpy(truck.vehicle.id, token, ID_CAR_LENGTH - 1); // Copy up to ID_CAR_LENGTH - 1 characters
	truck.vehicle.id[ID_CAR_LENGTH - 1] = '\0'; // Null-terminate the ID string

	// Get the next token (price)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Price token not found\n");
		return truck; // Returning an uninitialized truck
	}
	truck.vehicle.price = atoi(token);

	// Get the next token (capacity size)  
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Capacity size token not found\n");
		return truck; // Returning an uninitialized truck
	}
	truck.capacitySize = atoi(token);  // The maximum weight of cargo that the truck can carry (Kg)

	return truck;
}

void freeTruck(Truck* truck) {
	if (truck) {
		free(truck);
	}
}

