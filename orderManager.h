// orderManager.h
#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "customer.h"
#include "vehicleManager.h"
#include "employee.h"
#include "GeneralList.h"
#include "Car.h"
#define NUM_OF_EMPLOYEES 4
#define FIRST_EMPLOYEE_ID 1000

typedef struct {
	Customer** customerArray;
	int customerCount;
	Customer* ptrCustomer;
	LIST employees;
} OrderManager;

void initOrder(OrderManager* order);
void buyNewVehicle(OrderManager* order, VehicleManager* manager);
void freeOrderManager(OrderManager* order);
void freeEmployee(Employee* employee);

void removeVehicle(VehicleManager* manager, OrderManager* order, char* MotorId);
VehicleBasic* buyVehicle(VehicleManager* manager, int boolBuy); // booleanBuy - if 0=ADD | 1=BUY
int createCustomer(OrderManager* manager);
void printCustomers(const OrderManager* order);
VehicleBasic* buyFromStock(OrderManager* order, VehicleManager* manager);
Customer* checkPhoneNumberExists(OrderManager* manager, const char* phoneNumber);
void EmployeesInit(LIST* employeeList);
Employee* findEmployeeById(LIST* employeeList, int id);
bool isEligbleToDiscount(OrderManager* order);

void printInvoice(const OrderManager* order);
void printOrders(const Customer* customer);
void printOrder(Customer* customer, int index);


#endif // ORDER_MANAGER_H
