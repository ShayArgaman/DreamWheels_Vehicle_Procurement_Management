// payment.h
#ifndef __PAYMENT_H__
#define __PAYMENT_H__
#include <stdbool.h>
#include "date.h"

#define CARD_NUMBER_LENGTH 19 // 16 digits + 3 dashes

//payment types
typedef enum {
	MASTER_CARD,
	VISA,
	PAYPAL,
	paymentTypeSize
} ePaymentType;

static const char* paymentTypeStr[paymentTypeSize] = { "Master Card","Visa","Paypal" };

typedef struct {
	ePaymentType paymentType;
	char creditCardNumber[CARD_NUMBER_LENGTH];
	bool paidAll; // finish with payment
	//flout prePayment;
	int splitPayment;
	Date date;

} Payment;


int splitPayment(int downPayment);

ePaymentType getPaymentType();
void takePayment(Payment* payment);
bool isValidCreditCardNumberFormat(const char* creditCardNumber);
void getDateOfPaymentCard(Date* pDate);
void printCardDetails(const Payment* payment);


#endif /* PAYMENT_H */