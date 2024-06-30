//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "vehicleManager.h"
#include "orderManager.h"
#include "date.h"
#include "general.h"
#include "car.h"

int main() {

	srand(time(NULL));
	OrderManager order;
	VehicleManager manager;
	initManager(&manager);
	initOrder(&order);

	printf("\n");
	printf("                              **************************************************\n");
	printf("                              *                                                *\n");
	printf("                              *              Welcome to DreamWheels!           *\n");
	printf("                              *                                                *\n");
	printf("                              *        *================================*      *\n");
	printf("                              *        |        Your Ultimate           |      *\n");
	printf("                              *        |        Destination for         |      *\n");
	printf("                              *        |                                |      *\n");
	printf("                              *        |    Exquisite Cars, Trucks,     |      *\n");
	printf("                              *        |        and Motorcycles         |      *\n");
	printf("                              *        *================================*      *\n");
	printf("                              *                                                *\n");
	printf("                              **************************************************\n");
	printf("\n");

	// Ask the user where they want to read the files from
	int filesChoice;
	do {
		printf("Where do you want to read the files from?\n");
		printf("1. Text files\n");
		printf("2. Binary files\n");
		printf("Enter your choice: ");
		scanf("%d", &filesChoice);
		printf("\n");

		switch (filesChoice) {
		case 1:
			// Read vehicles from text files
			readVehiclesFromFile(&manager, "cars.txt"); // Read cars from cars.txt
			readVehiclesFromFile(&manager, "trucks.txt"); // Read trucks from trucks.txt
			readVehiclesFromFile(&manager, "motorcycles.txt"); // Read motorcycles from motorcycles.txt
			break;
		case 2:
			// Read vehicles from binary files
			readCarsFromBinary(&manager, "cars.bin"); // Read cars from binary file
			readTrucksFromBinary(&manager, "trucks.bin"); // Read trucks from binary file
			readMotorcyclesFromBinary(&manager, "motorcycles.bin"); // Read motorcycles from binary file
			break;
		default:
			printf("Invalid choice! Please try again.\n\n");
			break;
		}
	} while (filesChoice != 1 && filesChoice != 2);

	int carsBeforeUpdate = manager.carCount;
	int trucksBeforeUpdate = manager.trucksCount;
	int motorcyclesBeforeUpdate = manager.motorcyclesCount;
	int addManual = 0;

	int choice;
	do {
		displayMenu();
		scanf("%d", &choice);
		printf("\n");
		switch (choice) {
		case 1:
			if (!addVehicle(&manager, addManual))
				printf("error add car");
			break;
		case 2:
			printVehicle(&manager);
			break;
		case 3:
			printALLvehicles(&manager);
			break;
		case 4:
			buyNewVehicle(&order, &manager, choice);
			break;
		case 5:
			printCustomers(&order);
			break;
		case 6:
			chooseSearchType(&manager);
			break;
		case 7:
			chooseSortType(&manager);
			break;
		case 8:
			printInvoice(&order);

		case -1:
			// Write the updated cars, trucks, and motorcycles data to the txt file
			updateCarsFile(&manager, carsBeforeUpdate);
			updateTrucksFile(&manager, trucksBeforeUpdate);
			updateMotorcyclesFile(&manager, motorcyclesBeforeUpdate);

			// Write the updated cars, trucks, and motorcycles data to the binary file
			writeCarsToBinary(&manager, "cars.bin");
			writeTrucksToBinary(&manager, "trucks.bin");
			writeMotorcyclesToBinary(&manager, "motorcycles.bin");
			
			// Compress file
			saveBinaryFileCompressedCustomers(order.customerArray, order.customerCount, "customers_compress.bin");
			break;
		default:
			printf("Invalid choice! Please try again.\n");
			break;
		}
	} while (choice != -1);

	freeManager(&manager);
	freeOrderManager(&order);

	printf("\n");
	printf("                              **************************************************\n");
	printf("                              *                                                *\n");
	printf("                              *              Exiting DreamWheels...            *\n");
	printf("                              *                                                *\n");
	printf("                              *          *============================*        *\n");
	printf("                              *          |      Thank You for         |        *\n");
	printf("                              *          |     Visiting Our Store!    |        *\n");
	printf("                              *          |                            |        *\n");
	printf("                              *          |      Have a Great Day!     |        *\n");
	printf("                              *          *============================*        *\n");
	printf("                              *                                                *\n");
	printf("                              **************************************************\n");
	printf("\n");


	printf("Bye bye :)\n\n");
	return 0;

}

void displayMenu() 
{
	printf("\n\nMain Menu:\n");
	printf("1. Create a vehicle\n");
	printf("2. Print by vehicle type\n");
	printf("3. Print all existing vehicles\n");
	printf("4. Buy a vehicle \n");
	printf("5. Print all existing customers\n");
	printf("6. Search for a car\n");
	printf("7. Sort cars by choosen type\n");
	printf("8. Print all exist invoices\n");

	printf("-1. Exit\n");
	printf("Enter your choice: ");
}