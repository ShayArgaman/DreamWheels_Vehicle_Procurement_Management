//car.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "car.h"
#include "vehicleManager.h"
#include "general.h"
#include <ctype.h>


void initCar(Car* pCar, int boolBuy)
{
	pCar->vehicle.engineType = getEngineType();

	pCar->vehicle.year = initYear();

	pCar->vehicle.price = initPrice(boolBuy);// no random

	generateID(pCar->vehicle.id); // Generate and assign the ID

	pCar->numOfDoors = numOfDoors();

	pCar->vehicle.color = getColor();

	pCar->vehicle.vehicleType = ITS_A_CAR;

}


int isCarCode(const Car* car, const int* id)
{
	if (!car)
		return 0;
	if (strcmp(car->vehicle.id, id) == 0)
		return 1;

	return 0;
}

void printCar(const Car* pCar) {
	if (!pCar) {
		printf("No car information available.\n");
		return;
	}
	// Print car details
	printf("| Car Engine Type: %s | Year: %4d | ", engineTypeStr[pCar->vehicle.engineType], pCar->vehicle.year);

	// Print color with ANSI escape code
	switch (pCar->vehicle.color) {
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
		printf(ANSI_COLOR_CYAN); // Silver color
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

	printf("Color: %s", colorStr[pCar->vehicle.color]);
	printf(ANSI_COLOR_RESET); // Reset color

	printf(" | Number Of Doors: %d | ID: %s | ", pCar->numOfDoors, pCar->vehicle.id);

	if (pCar->vehicle.price < 1000) {
		printf("Price: $%d\n", pCar->vehicle.price);
	}
	else {
		int price = pCar->vehicle.price;
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

void initCarForBuy(Car* pCar, int boolBuy)
{

	pCar->vehicle.engineType = getEngineType();

	pCar->vehicle.year = initYear();

	pCar->vehicle.price = initPrice(boolBuy); // random

	generateID(pCar->vehicle.id); // Generate and assign the ID

	pCar->numOfDoors = numOfDoors();

	pCar->vehicle.color = getColor(); //make init color

	pCar->vehicle.vehicleType = ITS_A_CAR;

	printf("\n");
}

void freeCar(Car* pCar) {
	if (pCar) {
		free(pCar);
	}
}

// Function to parse a line and create a Car structure
Car parseVehicleLineCar(char* line) {
	Car car;

	// Tokenize the line
	char* token = strtok(line, " ");

	// Check if engine type token exists
	if (token == NULL) {
		// Error: Line does not contain expected fields
		return car; // Returning an uninitialized car
	}
	car.vehicle.engineType = (eEngineType)atoi(token);

	// Get the next token (year)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		return car; // Returning an uninitialized car
	}
	car.vehicle.year = atoi(token);

	// Get the next token (color)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		return car; // Returning an uninitialized car
	}
	// Convert color string to eColor enumeration value
	for (int i = 0; i < colorSize; ++i) {
		if (strcmp(token, colorStr[i]) == 0) {
			car.vehicle.color = (eColor)i;
			break;
		}
	}

	// Get the next token (id)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		return car; // Returning an uninitialized car
	}
	// Copy id token into the id array
	strncpy(car.vehicle.id, token, ID_CAR_LENGTH - 1); // Copy up to ID_CAR_LENGTH - 1 characters
	car.vehicle.id[ID_CAR_LENGTH - 1] = '\0'; // Null-terminate the ID string

	// Get the next token (price)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		free(car.vehicle.id); // Free dynamically allocated memory
		return car; // Returning an uninitialized car
	}
	car.vehicle.price = atoi(token);

	// Get the next token (number of doors)
	token = strtok(NULL, " ");
	if (token == NULL) {
		// Error: Line does not contain expected fields
		free(car.vehicle.id); // Free dynamically allocated memory
		return car; // Returning an uninitialized car
	}
	car.numOfDoors = atoi(token);

	return car;
}

int checkIdValid(const char* str) {
	int i = 0;

	// Check the first two characters
	for (i = 0; i < 2; i++) {
		if (!isdigit(str[i])) // Check if the character is a digit
			return 0; // Not in the correct format
	}

	// Check the third character (should be '-')
	if (str[i++] != '-')
		return 0; // Not in the correct format

	// Check the next two characters
	for (; i < 5; i++) {
		if (!isupper(str[i])) // Check if the character is an uppercase letter
			return 0; // Not in the correct format
	}

	// Check the next character (should be '-')
	if (str[i++] != '-')
		return 0; // Not in the correct format

	// Check the last two characters
	for (; i < 8; i++) {
		if (!isdigit(str[i])) // Check if the character is a digit
			return 0; // Not in the correct format
	}

	// Check if the string has ended
	if (str[i] != '\0')
		return 0; // Not in the correct format

	// If all checks pass, the string is in the correct format
	return 1;
}


void getIdFromUser(char id[ID_CAR_LENGTH + 1]) {
	printf("Please enter an ID:\n");
	do {
		int loopsCounter = 0;
		if (loopsCounter > 0)
			printf("Unmatched format!! Please try again...\n");
		printf("Enter ID in the format XX-YY-XX (X - number, Y - uppercase letter, for example - 35-UH-86): ");
		scanf("%8s", id); // Read input from the user (limit to 8 characters to avoid buffer overflow)
		loopsCounter++;
	} while (!checkIdValid(id));
}


