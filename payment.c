#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "payment.h"
#include "orderManager.h"
#include "vehicleBasic.h"
#include "general.h"


int splitPayment(int downPayment) {
    int numPayments;

    printf("\nEnter the number of payments to split (between 1 and 12)\n");
    printf("Note: With split you will have to pay now a down payment. 10%% of the value vehicle\n");
    printf("The down payment of your vehicle is: ");
    printWithCommas((double)(downPayment * 0.1));
    printf("\nNumber of payments: ");

    while (1) {
        if (scanf("%d", &numPayments) != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (numPayments < 1 || numPayments > 12) {
            printf("Invalid number of payments. Please enter a number between 1 and 12.\n");
            continue;
        }

        printf("Payment split successfully into %d payments.\n", numPayments);
        return numPayments;
    }
}

bool isValidCreditCardNumberFormat(const char* creditCardNumber) {
    int dashCount = 0;
    for (int i = 0; creditCardNumber[i] != '\0'; i++) {
        if (i % 5 == 4) { // Check for dashes at every fifth position
            if (creditCardNumber[i] != '-') {
                return false; // Return false if a dash is missing
            }
            dashCount++;
        }
        else {
            if (!isdigit(creditCardNumber[i])) {
                return false; // Return false if a non-digit character is encountered
            }
        }
    }
    return (dashCount == 3); // Return true only if there are exactly 3 dashes
}

void takePayment(Payment* payment) {
    printf("Please enter payment details:\n");
    char creditCardNumber[CARD_NUMBER_LENGTH + 1]; // 16 digits + 3 dashes + 1 null terminator
    while (1) {
        // Input credit card number
        printf("Enter credit card number (in format XXXX-XXXX-XXXX-XXXX): ");
        scanf("%s", creditCardNumber);

        // Validate credit card number format
        if (isValidCreditCardNumberFormat(creditCardNumber)) {
            // Copy credit card number to payment struct
            // Assuming payment struct is defined with a member 'creditCardNumber'
            strcpy(payment->creditCardNumber, creditCardNumber);
            break; // Exit the loop if the format is valid
        }
        else {
            printf("Invalid credit card number format. Please enter a valid 16-digit number in the format XXXX-XXXX-XXXX-XXXX.\n");
        }
    }
}


void printCardDetails(const Payment* payment) {
    printf("Payment Type: %s\n", paymentTypeStr[payment->paymentType]);

    printf("Card Number: ");
    // Print masked characters for the card number
    for (int i = 0; i < CARD_NUMBER_LENGTH - 3; i++) {
        printf("*");
    }
    // Print the last three numbers of the card
    printf("%s\n", payment->creditCardNumber + (CARD_NUMBER_LENGTH - 4)); // Assuming creditCardNumber is a string
}


void getDateOfPaymentCard(Date* pDate) {
    while (1) {
        printf("Enter expiration date of payment card (MM-YYYY): ");
        int month, year;
        if (scanf("%d-%d", &month, &year) != 2) {
            // If the input format is incorrect
            printf("Invalid format. Please enter the date in the format MM-YYYY.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        // Calculate the cutoff date: April 2024
        const int cutoffMonth = 4;
        const int cutoffYear = 2024;

        // Convert input date to a comparable format
        int inputComparable = year * 100 + month;
        int cutoffComparable = cutoffYear * 100 + cutoffMonth;

        // Check if the entered date is on or after the cutoff date
        if (inputComparable <= cutoffComparable) {
            printf("Invalid date. Please enter a date after April 2024.\n");
            continue;
        }

        // Valid date, assign to pDate and exit the loop
        pDate->month = month;
        pDate->year = year;
        break;
    }
}

ePaymentType getPaymentType()
{
    int option;
    do {
        printf("Please enter the card type you wish to pay with: \n");
        for (int i = 0; i < paymentTypeSize; i++)
            printf("%d - %s\n", i, paymentTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= paymentTypeSize);
    getchar();

    return (ePaymentType)option;
}

