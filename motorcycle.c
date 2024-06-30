// motorcycle.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "motorcycle.h"
#include "vehicleManager.h"
#include "general.h"

void initMotorcycle(Motorcycle* pMotorcycle, int boolBuy)
{
	pMotorcycle->vehicle.engineType = getEngineType();

	pMotorcycle->vehicle.year = initYear();

	pMotorcycle->vehicle.price = initPrice(boolBuy); // random for buy

	generateID(pMotorcycle->vehicle.id); // Generate and assign the ID

	pMotorcycle->vehicle.color = getColor();

	pMotorcycle->numOfWheels = getNumOfWheels();

	pMotorcycle->vehicle.vehicleType = ITS_A_MOTORCYCLE;
}


void printMotorcycle(const Motorcycle* pMotorcycle)
{
	if (!pMotorcycle) {
		printf("No motorcycle information available.\n");
		return;
	}

	// Print motorcycle details
	printf("| Motorcycle Engine Type: %s | Year: %4d | ", engineTypeStr[pMotorcycle->vehicle.engineType], pMotorcycle->vehicle.year);

	// Print color with ANSI escape code
	switch (pMotorcycle->vehicle.color) {
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

	printf("Color: %s | ", colorStr[pMotorcycle->vehicle.color]);
	printf(ANSI_COLOR_RESET); // Reset color
	printf("Numer Of Wheels: %d | ", pMotorcycle->numOfWheels);
	printf("ID: %s | ", pMotorcycle->vehicle.id);

	if (pMotorcycle->vehicle.price < 1000) {
		printf("Price: $%d\n", pMotorcycle->vehicle.price);
	}
	else {
		int price = pMotorcycle->vehicle.price;
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

void initMotorcycleForBuy(Motorcycle* pMotorcycle, int boolBuy)
{
	pMotorcycle->vehicle.engineType = getEngineType();

	pMotorcycle->vehicle.year = initYear();

	pMotorcycle->vehicle.price = initPrice(boolBuy); // random

	generateID(pMotorcycle->vehicle.id); // Generate and assign the ID

	pMotorcycle->vehicle.color = getColor(); //make init color

	pMotorcycle->numOfWheels = getNumOfWheels();

	pMotorcycle->vehicle.vehicleType = ITS_A_MOTORCYCLE;

	printf("\n");
}


Motorcycle parseVehicleLineMotorcycle(char* line)
{
	Motorcycle motorcycle;

	// Tokenize the line
	char* token = strtok(line, " ");

	// Check if engine type token exists
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Engine type token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	motorcycle.vehicle.engineType = (eEngineType)atoi(token);

	// Get the next token (year)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Year token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	motorcycle.vehicle.year = atoi(token);

	// Get the next token (color)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Color token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	// Convert color string to eColor enumeration value
	for (int i = 0; i < colorSize; ++i) {
		if (strcmp(token, colorStr[i]) == 0) {
			motorcycle.vehicle.color = (eColor)i;
			break;
		}
	}

	// Get the next token (id)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: ID token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	// Copy id token into the id array
	strncpy(motorcycle.vehicle.id, token, ID_CAR_LENGTH - 1); // Copy up to ID_CAR_LENGTH - 1 characters
	motorcycle.vehicle.id[ID_CAR_LENGTH - 1] = '\0'; // Null-terminate the ID string

	// Get the next token (price)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Price token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	motorcycle.vehicle.price = atoi(token);

	// Get the next token (numOfWheels)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		printf("Error: Number of wheels token not found\n");
		return motorcycle; // Returning an uninitialized motorcycle
	}
	motorcycle.numOfWheels = (eNumOfWheels)atoi(token);

	return motorcycle;
}

void freeMotorcycle(Motorcycle* motorcycle) {
	if (motorcycle) {
		free(motorcycle);
	}
}