//invoice.c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "invoice.h"
#include "orderManager.h"


int initInvoice() {
    static int hugeInt = HUGE_INT_MIN;  // Start with the minimum value

    // Generate a random number within the specified range
    int invoiceNumber = hugeInt++;

    // Check if we have reached the maximum value, wrap around to the minimum value
    if (hugeInt > HUGE_INT_MAX)
        hugeInt = HUGE_INT_MIN;

    printf("Invoice Number: %d\n", invoiceNumber);
    return invoiceNumber;
}

