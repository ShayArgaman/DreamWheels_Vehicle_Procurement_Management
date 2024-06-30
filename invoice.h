//invoice.h
#ifndef __INVOICE_H__
#define __INVOICE_H__
#include "customer.h"

#define HUGE_INT_MIN 25341525  // Minimum value for the huge integer
#define HUGE_INT_MAX 47483647  // Maximum value for the huge integer (maximum value for a regular int)


typedef struct {
	Customer* customer;
	int orderNumber;

} Invoice;

int initInvoice();


#endif