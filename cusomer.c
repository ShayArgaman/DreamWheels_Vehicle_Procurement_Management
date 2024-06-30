// customer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "orderManager.h"
#include "general.h"
#include <ctype.h>

void initCustomer(Customer* customer) {

	customer->name = (char*)malloc(100 * sizeof(char)); // Assuming maximum name length is 100 characters
	if (!customer->name)
		return 0;

	customerValidName(customer->name);

	customer->mail = customerValidMail();

	printf("------- Your details have been successfully received -------\n");
	customer->dateArrive = generateRandomDate();

	customer->payment = NULL;
}

void freeCustomer(Customer* customer) {
	if (customer) {
		free(customer->name);
		free(customer->mail);
		free(customer->payment);
		free(customer);
	}
}

void freeVehicleBasic(VehicleBasic* vehicle) {
	if (vehicle) {
		free(vehicle);
	}
}

void freeVehicleBasicArray(Customer* customer) {
	if (customer) {
		for (int i = 0; i < customer->purchasedCarCount; i++) {
			freeVehicleBasic(customer->purchasedVehicle[i]); // Free each VehicleBasic instance
		}
		free(customer->purchasedVehicle); // Free the array of pointers
		free(customer); // Free the customer structure itself
	}
}

void initPayment(Customer* customer, int paymentPrice)
{
	customer->payment = malloc(sizeof(Payment));

	if (customer->payment != NULL)
		customer->payment->splitPayment = splitPayment(paymentPrice);
	else
		printf("Memory allocation failed for payment.");

	if (customer->payment != NULL) {
		if (customer->payment->splitPayment == 1)
			customer->payment->paidAll = true; // paid all the price
		else
			customer->payment->paidAll = false;
	}
	customer->payment->paymentType = getPaymentType(); // ask for card type

	takePayment(customer->payment); // ask for card details

	getDateOfPaymentCard(customer->payment);
	printf("\nThank you for choosing DreamWheels!\n");

	printf("\n\n------Your payment details have been collected successfully.-------\n\n");
}

// Function to print customer details
void printCustomer(const Customer* customer) {
	if (!customer) {
		printf("Invalid customer.\n");
		return;
	}
	printf("Customer Details:\n");
	printf("Name: %s\n", customer->name);
	printf("Mail: %s\n", customer->mail);
	printf("Phone Number: %s\n", customer->phoneNumber); // Assuming phoneNumber is a string

}

bool isValidPhoneNumber(const char* phone) {
	// Simple phone number validation
	int length = strlen(phone);
	int digitCount = 0;
	int dashCount = 0;

	for (int i = 0; i < length; i++) {
		if (isdigit(phone[i])) {
			digitCount++;
		}
		else if (phone[i] == '-') {
			dashCount++;
		}
		else {
			return false; // Non-digit and non-dash character found
		}
	}

	// Check if the phone number has the correct length and dash count
	if ((digitCount == 10 && dashCount == 1) || digitCount == 10) {
		return true;
	}

	return false;
}


bool isValidEmail(const char* email) {
	// Simple email validation
	int atCount = 0;
	int dotCount = 0;
	int length = strlen(email);
	for (int i = 0; i < length; i++) {
		if (email[i] == '@') {
			atCount++;
		}
		else if (email[i] == '.') {
			dotCount++;
		}
		else if (isspace(email[i])) { // Check for spaces
			printf("Email can't include spaces.\n");
			return false; // If a space is found, return false
		}
	}
	return (atCount == 1 && dotCount >= 1 && email[0] != '@' && email[length - 1] != '@' && email[0] != '.' && email[length - 1] != '.');
}

char* customerValidMail() {
	char input[100]; // Buffer to store input temporarily
	while (1) {
		printf("Enter your email: ");
		myGets(input, sizeof(input)); // Get input

		// Check if the input is empty
		if (input[0] == '\0') {
			printf("Please enter a valid email.\n");
			continue;
		}

		// Check if the input is a valid email address
		if (!isValidEmail(input)) {
			printf("Invalid email format. Please enter a valid email.\n");
			continue;
		}
		// Exit loop if input is valid
		break;
	}

	// Dynamically allocate memory for the email buffer based on input size
	char* email = (char*)malloc((strlen(input) + 1) * sizeof(char));
	if (email == NULL) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	// Copy input to the dynamically allocated buffer
	strcpy(email, input);

	return email;
}

int customerValidName(char* name) {
	if (name == NULL) {
		printf("Invalid pointer to name.\n");
		return 0; // Return 0 to indicate failure 
	}

	char input[MAX_NAME_LENGTH]; // Buffer to store input temporarily
	while (1) {
		printf("Enter your full name (Reservation Name): ");
		myGets(input, sizeof(input)); // Get input

		if (input[0] == '\0') {
			printf("Please enter a valid name.\n");
			continue;
		}

		// Copy input to the provided buffer
		strcpy(name, input);

		// Check if the name contains a space character
		if (strchr(name, ' ') == NULL) {
			printf("Please enter both your first and last names separated by a space.\n");
			continue;
		}
		// Capitalize the first letter of each word
		capitalizeWords(name);

		// Exit loop if input is valid
		break;
	}
	return 1; // Return 1 to indicate success
}


void customerValidPhoneNumber(char phoneNumber[]) {
	while (1) {
		printf("Enter your phone number (050-1234567): ");
		scanf("%19s", phoneNumber); // Read up to 19 characters to leave space for the null terminator

		// Check if the input is empty
		if (phoneNumber[0] == '\0') {
			printf("Please enter a valid phone number.\n");
			continue;
		}

		// Check if the input has the correct length
		if (strlen(phoneNumber) != 11) {
			printf("Invalid phone number format. Please enter a valid phone number.\n");
			continue;
		}

		// Check if the first three characters are digits
		for (int i = 0; i < 3; i++) {
			if (!isdigit(phoneNumber[i])) {
				printf("Invalid phone number format. Please enter a valid phone number.\n");
				continue;
			}
		}

		// Check if the fourth character is '-'
		if (phoneNumber[3] != '-') {
			printf("Invalid phone number format. Please enter a valid phone number.\n");
			continue;
		}

		// Check if the rest of the characters are digits
		for (int i = 4; i < 11; i++) {
			if (!isdigit(phoneNumber[i])) {
				printf("Invalid phone number format. Please enter a valid phone number.\n");
				continue;
			}
		}

		// Exit loop if input is valid
		break;
	}
}

int saveBinaryFileCompressedCustomer(const Customer* customer, FILE* f)
{
	if (!customer || !f) {
		return 0;
	}

	// Writing name length, mail length, and budget
	int nameLen = strlen(customer->name);
	int mailLen = strlen(customer->mail);
	if (nameLen > MAX_NAME_LENGTH || mailLen >= MAX_NAME_LENGTH) {
		return 0; // Invalid lengths
	}

	fwrite(&nameLen, sizeof(int), 1, f);
	fwrite(&mailLen, sizeof(int), 1, f);

	// Writing name, mail, and phone number
	fwrite(customer->name, sizeof(char), nameLen, f);
	fwrite(customer->mail, sizeof(char), mailLen, f);
	fwrite(customer->phoneNumber, sizeof(char), PHONE_NUMBER_LEN, f); // Assuming fixed length for phone number

	// Writing number of purchased vehicles
	fwrite(&(customer->purchasedCarCount), sizeof(int), 1, f);

	// Writing purchased vehicles (assuming a fixed number of purchased vehicles)
	for (int i = 0; i < customer->purchasedCarCount; i++) {
		fwrite(customer->purchasedVehicle[i], sizeof(VehicleBasic), 1, f);
	}

	fwrite(customer->payment, sizeof(Payment), 1, f);
	return 1;
}

// Function to save an array of customers to a compressed binary file
int saveBinaryFileCompressedCustomers(Customer** customerArray, int customerCount, const char* fileName)
{
	if (!customerArray || customerCount <= 0 || !fileName) {
		return 0;
	}

	FILE* f = fopen(fileName, "wb");
	if (!f) {
		return 0; // File opening failed
	}

	// Writing the number of customers
	fwrite(&customerCount, sizeof(int), 1, f);

	// Writing each customer
	for (int i = 0; i < customerCount; i++) {
		if (!saveBinaryFileCompressedCustomer(customerArray[i], f)) {
			fclose(f);
			return 0; // Writing customer failed
		}
	}

	fclose(f);
	return 1; // All customers written successfully
}


