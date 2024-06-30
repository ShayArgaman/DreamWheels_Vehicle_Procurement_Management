#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <stdbool.h>
#include "car.h"
#include "date.h"
#include "truck.h"
#include "payment.h"

#define MAX_NAME_LENGTH 100
#define PHONE_NUMBER_LEN 21

typedef struct {
	char* name;
	char* mail;
	char phoneNumber[PHONE_NUMBER_LEN]; // 20 characters for phone number + 1 for null terminator
	Date dateArrive;
	VehicleBasic** purchasedVehicle;
	int purchasedCarCount;
	Payment* payment;
	struct Invoice* invoiceNumber;
} Customer;

// Function prototypes
void initCustomer(Customer* customer);
void initPayment(Customer* customer, int paymentPrice);
void freeCustomer(Customer* customer);
void freeVehicleBasicArray(Customer* customer);

void customerValidPhoneNumber(char phoneNumber[]);
int customerValidName(char* name);
void printCustomer(const Customer* customer);
bool isValidPhoneNumber(const char* phone);
char* customerValidMail();
bool isValidEmail(const char* email);

// Compress file
int saveBinaryFileCompressedCustomer(const Customer* customer, FILE* f);
int saveBinaryFileCompressedCustomers(Customer** customerArray, int customerCount, const char* fileName);


#endif // CUSTOMER_H