//orderManager.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderManager.h"
#include "vehiclemanager.h"
#include "invoice.h"

#define EMPLOYEE_DISCOUNT(price) ((price) * 0.7)

void initOrder(OrderManager* order)
{
	order->customerArray = NULL;
	order->customerCount = 0;
	EmployeesInit(&order->employees);
}

void printInvoice(const OrderManager* order)
{
	if (order->customerCount == 0) {
		printf("There is not invoices");
		return;
	}

	for (int i = 0; i < order->customerCount; i++)
	{
		printCustomer(order->customerArray[i]);
		printOrders(order->customerArray[i]); // print customer and his vehicle
	}
	printf("\n\n");

}


void printOrder(Customer* customer, int index)
{
	if (index < 0 || index >= customer->purchasedCarCount) {
		printf("Invalid index.\n");
		return;
	}

	VehicleBasic* vehicle = customer->purchasedVehicle[index];

	if (vehicle->vehicleType == 1)
		printCar((Car*)vehicle);
	else if (vehicle->vehicleType == 2)
		printTruck((Truck*)vehicle);
	else if (vehicle->vehicleType == 3)
		printMotorcycle((Motorcycle*)vehicle);

	printf("\n");

	int vehiclePrice = vehicle->price;
	printf("==============================================================================\n");
	printf("|                               INVOICE                                      |\n");
	printf("==============================================================================\n");
	printf("|                                                                            |\n");
	printf("|                       Invoice Number: %d                             |\n", customer->invoiceNumber);
	printf("|                                                                            |\n");
	printf("| Customer Name: %s                                                       |\n", customer->name);
	printf("| Email: %s                                          Phone: %s |\n", customer->mail, customer->phoneNumber);
	printf("|                                                                            |\n");
	printf("|----------------------------------------------------------------------------|\n");
	printf("|                          PURCHASED VEHICLES                                |\n");
	printf("|----------------------------------------------------------------------------|\n");
	printf("| Item Description            | Quantity | Unit Price ($)  | Total Price ($) |\n");
	printf("|----------------------------------------------------------------------------|\n");

	// Print vehicle details
	char* vehicleTypeStr = (vehicle->vehicleType == 1) ? "Car" : ((vehicle->vehicleType == 2) ? "Truck" : "Motorcycle");
	printf("| %-27s |    1     |   $%d        |    $%d       |\n", vehicleTypeStr, vehicle->price, vehicle->price);

	printf("|----------------------------------------------------------------------------|\n");
	printf("|                                                                            |\n");
	if (customer->payment->splitPayment == 1)
	{
		printf("| Total Vehicles: 1                                       Total Paid: $%d |\n", vehiclePrice);

		printf("| Payment Status: Paid All                                                   |\n"); // Assuming payment status is not available
	}
	else
	{
	printf("| Total Vehicles: 1                                   Subtotal: $%f |\n", vehiclePrice * 0.1);

	printf("| Payment Status: Didn't Pay All                                             |\n"); // Assuming payment status is not available

	printf("| Amount remaining to pay : $%f                                    |\n", vehiclePrice * 0.9);
	printf("| Total Amount Due: $%d                                                   |\n", vehiclePrice); // Assuming total amount due is not available
	printf("| Spread to you for %d months, Each month you have to pay $%f        |\n", customer->payment->splitPayment, (vehiclePrice * 0.9) / customer->payment->splitPayment);

	printf("|                                                                            |\n");
	printf("|                                                                            |\n");


	}
	printf("|                                                                            |\n");
	printf("| Thank you for choosing DreamWheels! We appreciate your business.           |\n");
	printf("|                                                                            |\n");
	printf("==============================================================================\n\n");
}

void printOrders(const Customer* customer)
{
	printf("\n\n");
	for (int i = 0; i < customer->purchasedCarCount; i++)
	{
		printOrder(customer, i);
	}
}

void buyNewVehicle(OrderManager* order, VehicleManager* manager)
{
	if (!createCustomer(order)) {
		printf("Failed to create a customer.\n");
		return;
	}
	int price = 0;
	int ptrID = 0;
	int choice = 0;
	int vehiclesCount = manager->carCount + manager->trucksCount + manager->motorcyclesCount; //add motorcycles
	while (choice != 1 && choice != 2) {
		printf("\n1) - Make an order for personal import (vehicle of your choice)\n");
		printf("2) - Purchase from our available vehicles in stock (We've %d available)\n", vehiclesCount);

		printf("Enter your choice (1 or 2): ");
		if (scanf("%d", &choice) != 1) {
			printf("Invalid input. Please enter 1 or 2.\n");
			// Clear input buffer
			while (getchar() != '\n');
			continue;
		}

		if (choice != 1 && choice != 2)
			printf("Invalid choice. Please enter 1 or 2.\n");
	}
	// Reallocate memory for an additional purchased Vehicle
	(VehicleBasic*)order->ptrCustomer->purchasedVehicle = (VehicleBasic*)realloc(order->ptrCustomer->purchasedVehicle, (order->ptrCustomer->purchasedCarCount + 1) * sizeof(VehicleBasic));
	if (!order->ptrCustomer->purchasedVehicle) {
		printf("Failed to allocate memory for the new car.\n");
		return;
	}
	if (choice == 1) { // Make an order for personal import (car of your choice)
		// Buy new car (create)
		order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount] = buyVehicle(manager, choice);
		price = (int)(order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount]->price);
		printf("\n\nPrice: %d\n", price);
		order->ptrCustomer->purchasedCarCount++;
	}
	else if (vehiclesCount > 0) {
		// Buy from available Vehicle
		order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount] = buyFromStock(order, manager);
		printf("\n");
		printf("==================================================\n");
		printf("                  VEHICLE PURCHASED\n");
		printf("==================================================\n\n");
		printf("Congratulations on your purchase from our available stock!\n");
		price = (int)(order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount]->price);
		bool eligbleToDiscount = isEligbleToDiscount(order);//here i was//RAN
		if (eligbleToDiscount)//Check if eligible to discount
		{
			printf("\nPrice before discount:%d\n", price);
			(int)(order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount]->price) = (int)EMPLOYEE_DISCOUNT(price);
			price = (int)EMPLOYEE_DISCOUNT(price);
			printf("Price after employee discount: % d\n", price);
		}
		else  // without employee discount
			printf("\n\nPrice: %d\n", price);

		// Get the ID of the purchased car and remove it from stock
		char* vehicleID;
		vehicleID = order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount]->id;
		removeVehicle(manager, order, vehicleID);

		order->ptrCustomer->purchasedCarCount++;
	}
	else {
		printf("\nNo vehicles available in our stock\n");
		return;
	}
	printf("\n");
	printCustomer(order->ptrCustomer);
	printf("\nDelivery Information:");
	printf("\n----------------------------\n");
	printDate(&order->ptrCustomer->dateArrive);

	order->ptrCustomer->invoiceNumber = initInvoice();
	initPayment(order->ptrCustomer, price);
	printOrder(order->ptrCustomer, order->ptrCustomer->purchasedCarCount - 1);
}

void freeOrderManager(OrderManager* order) {
	if (order) {
		if (order->customerArray) {
			for (int i = 0; i < order->customerCount; i++) {
				freeCustomer(order->customerArray[i]);
			}
			free(order->customerArray);
		}
		//free(order);
	}
}

void freeEmployee(Employee* employee) {
	if (employee) {
		free(employee);
	}
}


void removeVehicle(VehicleManager* manager, OrderManager* order, char* vehicleID)//determine witch type of vrhilce and removes it accordingly
{
	int vehicleType = order->ptrCustomer->purchasedVehicle[order->ptrCustomer->purchasedCarCount]->vehicleType;
	if (vehicleType == ITS_A_CAR)
		removeCar(manager, vehicleID);
	else if (vehicleType == ITS_A_TRUCK)
		removeTruck(manager, vehicleID);
	else if (vehicleType == ITS_A_MOTORCYCLE)
		removeMotorcycle(manager, vehicleID);
}

VehicleBasic* buyFromStock(OrderManager* order, VehicleManager* manager)
{
	printALLvehicles(manager);

	int vehiclesCount = manager->carCount + manager->trucksCount + manager->motorcyclesCount;
	int choice;
	while (1) {
		// Get user choice
		printf("Enter the number of the vehicle you want to buy: ");
		if (scanf("%d", &choice) != 1) {
			printf("Invalid input. Please enter a valid number.\n");
			continue;
		}

		if (choice < 1 || choice > vehiclesCount) {
			printf("Invalid choice. Please enter a number between 1 and %d.\n", vehiclesCount);
			continue;
		}

		// Determine if the chosen vehicle is a car, truck, or motorcycle
		if (choice <= manager->carCount)
		{
			// Chosen vehicle is a car
			Car* chosenCar = manager->carArr[choice - 1];
			Car* carCopy = malloc(sizeof(Car));
			if (carCopy == NULL) {
				printf("Memory allocation failed.\n");
				return NULL;
			}
			memcpy(carCopy, chosenCar, sizeof(Car));
			carCopy->vehicle.vehicleType = ITS_A_CAR;
			printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
			printCar(manager->carArr[choice - 1]);
			//return (VehicleBasic*)manager->carArr[choice - 1]; // Return pointer to the chosen car copy, car from stock will remove
			return (VehicleBasic*)carCopy;
		}
		else if (choice <= manager->carCount + manager->trucksCount)
		{
			// Chosen vehicle is a truck
			Truck* chosenTruck = manager->truckArr[choice - manager->carCount - 1];
			Truck* truckCopy = malloc(sizeof(Truck));
			if (truckCopy == NULL) {
				printf("Memory allocation failed.\n");
				return NULL;
			}
			memcpy(truckCopy, chosenTruck, sizeof(Truck));
			truckCopy->vehicle.vehicleType = ITS_A_TRUCK;
			printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
			printTruck(truckCopy);
			return (VehicleBasic*)truckCopy; // Return pointer to the chosen truck copy
		}
		else
		{
			// Chosen vehicle is a motorcycle
			Motorcycle* chosenMotorcycle = manager->motorcycleArr[choice - manager->carCount - manager->trucksCount - 1];
			Motorcycle* motorcycleCopy = malloc(sizeof(Motorcycle));
			if (motorcycleCopy == NULL) {
				printf("Memory allocation failed.\n");
				return NULL;
			}
			memcpy(motorcycleCopy, chosenMotorcycle, sizeof(Motorcycle));
			motorcycleCopy->vehicle.vehicleType = ITS_A_MOTORCYCLE;
			printf("\n------------------\tYour order has been successfully received  ------------------\n\n");
			printMotorcycle(motorcycleCopy);
			return (VehicleBasic*)motorcycleCopy; // Return pointer to the chosen motorcycle copy
		}
	}
}


VehicleBasic* buyVehicle(VehicleManager* manager, int boolBuy) //booleanBuy - if 0=ADD | 1=BUY
{
	int option;
	do {
		printf("Which vehicle type do you want to buy? :)\n");
		printf("1 - car\n");
		printf("2 - Truck\n");
		printf("3 - Motorcycle\n\n");
		printf("Your choice:\t");
		scanf("%d", &option);
	} while (option < 0 || option > VEHICLE_TYPES_NUM);
	getchar();

	switch (option) {
	case 1:
		return addCar(manager, boolBuy);
		break;
	case 2:
		return addTruck(manager, boolBuy);
		break;
	case 3:
		return addMotorcycle(manager, boolBuy);
		break;
	}
	return NULL;
}

void printCustomers(const OrderManager* order)
{
	printf("There are %d customers available\n", order->customerCount); // Print the total number of customers

	// Iterate over the vehicleArr array and print each car
	for (int i = 0; i < order->customerCount; i++)
	{
		printf("%d) - ", i + 1); // Print index of the car
		printCustomer(order->customerArray[i]); // Print car details
	}
}

int createCustomer(OrderManager* manager)
{
	char phoneNumber[20] = { 0 }; // Temporary storage for phone number input

	// Prompt the user for the phone number
	customerValidPhoneNumber(phoneNumber);

	Customer* existingCustomer = checkPhoneNumberExists(manager, phoneNumber);
	if (existingCustomer != NULL) {
		// Existing customer found
		printf("\n\t\tWelcome back: %s!\n", existingCustomer->name);
		printf("Good to see you again. We remember your previous orders.\n");
		manager->ptrCustomer = existingCustomer; // Assign the customer to ptrCustomer
		printf("You have already on your name %d orders.\n", existingCustomer->purchasedCarCount);

		return 1; // Return 1 to indicate success
	}

	// If no existing customer found, proceed with customer initialization
	Customer* new_customer = (Customer*)calloc(1, sizeof(Customer));
	if (!new_customer) return 0;

	// Initialize the new customer

	strncpy(new_customer->phoneNumber, phoneNumber, sizeof(new_customer->phoneNumber) - 1);
	new_customer->phoneNumber[sizeof(new_customer->phoneNumber) - 1] = '\0'; // Ensure null-termination

	// Initialize other details using initCustomer
	initCustomer(new_customer);

	// Allocate memory for the array of purchased cars
	(Car*)new_customer->purchasedVehicle = (Car*)malloc(sizeof(Car));
	if (!new_customer->purchasedVehicle) {
		free(new_customer->name);
		free(new_customer->mail);
		free(new_customer);
		return 0;
	}

	new_customer->purchasedCarCount = 0; // Initialize purchased car count to 0


	// Reallocate memory for customerArray
	(Customer*)manager->customerArray = (Customer*)realloc(manager->customerArray, (manager->customerCount + 1) * sizeof(Customer));
	if (!manager->customerArray) {
		free(new_customer->name);
		free(new_customer->mail);
		free(new_customer);
		return 0;
	}

	// Add the new customer to customerArray
	manager->customerArray[manager->customerCount] = new_customer;
	manager->customerCount++;
	manager->ptrCustomer = new_customer; // Assign the customer to ptrCustomer

	return 1; // Return 1 to indicate success
}

Customer* checkPhoneNumberExists(OrderManager* manager, const char* phoneNumber)
{
	// Iterate over each customer in the array
	for (int i = 0; i < manager->customerCount; i++) {
		Customer* customer = manager->customerArray[i];
		// Compare phone numbers
		if (strcmp(customer->phoneNumber, phoneNumber) == 0) {
			// If phone number matches, return the address of the customer
			return customer;
		}
	}
	// If phone number doesn't exist, return NULL
	return NULL;
}


void EmployeesInit(LIST* employeeList)
//TODO: insert to a function "createAndUpdateHead"
{	// create the first employee
	Employee* firstEmp = (Employee*)malloc(sizeof(Employee));
	if (!firstEmp)
		return;
	firstEmp->id = FIRST_EMPLOYEE_ID;

	//create and update the first node to contain the first employee in it's data
	employeeList->head = *(NODE*)malloc(sizeof(NODE));
	employeeList->head.key = (void*)firstEmp;
	employeeList->head.next = NULL;

	// curr will always indicate the current last node in the list
	NODE* curr = &employeeList->head;

	for (int i = 1; i <= NUM_OF_EMPLOYEES; i++)
	{
		Employee* emp = (Employee*)malloc(sizeof(Employee));
		emp->id = FIRST_EMPLOYEE_ID + i;
		L_insert(curr, emp);
		curr = curr->next;
	}
}


Employee* findEmployeeById(LIST* employeeList, int id) {
	NODE* curr = &employeeList->head; // Start from the first node

	// Iterate through the linked list
	while (curr != NULL) {
		Employee* emp = (Employee*)curr->key; // Get the employee from the current node

		// Compare the ID of the current employee with the given ID
		if (emp->id == id) {
			return emp; // Return the employee if found
		}

		// Move to the next node
		curr = curr->next;
	}

	return NULL; // Return NULL if employee with the given ID is not found
}

//How to see in debugger the id, how to do more ellegant debugging
bool isEligbleToDiscount(OrderManager* order)
{
	int answer;
	bool discount = false;
	do
	{
		printf("\nAre u a worker? (For Discount)\n1. Yes\n2. No\n");
		scanf("%d", &answer);
	} while (answer < 1 || answer > 2);

	if (answer == 1)
	{
		int ID;
		printf("Please enter your employre ID:  ");
		scanf("%d", &ID);
		Employee* res = findEmployeeById(&order->employees, ID);
		if (res == NULL)
			printf("ID of worker doesn't exist. \n");
		else
		{
			printf("Welcome employee ID: %d\n enjoy you'r 30 percent discount (: ", ID);
			discount = true;
		}
	}
	return discount;


}