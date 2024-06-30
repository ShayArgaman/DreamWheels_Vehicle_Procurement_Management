//date.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>


Date generateRandomDate()
{
    Date randomDate;

    // Get the current year
    time_t t = time(NULL);
    struct tm* currentTime = localtime(&t);
    int currentYear = currentTime->tm_year + 1900;

    // Set the year randomly within the next 1 or 2 years
    randomDate.year = currentYear + rand() % 2 + 1;

    // Set the month randomly between 1 and 12
    randomDate.month = rand() % 12 + 1;

    // Set the day randomly based on the month and whether it's a leap year
    int maxDaysInMonth;
    if (randomDate.month == 2) {
        // Check if it's a leap year
        if ((randomDate.year % 4 == 0 && randomDate.year % 100 != 0) || (randomDate.year % 400 == 0)) {
            maxDaysInMonth = 29;
        }
        else {
            maxDaysInMonth = 28;
        }
    }
    else if (randomDate.month == 4 || randomDate.month == 6 || randomDate.month == 9 || randomDate.month == 11) {
        maxDaysInMonth = 30;
    }
    else {
        maxDaysInMonth = 31;
    }
    randomDate.day = rand() % maxDaysInMonth + 1;
    //printDate(&randomDate);
    return randomDate;
}


void printDate(const Date* pDate)
{
    // Print the random date
    printf("Expected to arrive in:\t");
    printf("%02d-%02d-%d\n", pDate->day, pDate->month, pDate->year);
}


//#define SPECIAL_TAV '/'
//
//void getCorrectDate(Date* pDate)
//{
//	char date[MAX_STR_LEN];
//	int ok = 1;
//
//	do {
//		printf("Enter Flight Date dd%c%cmm%c%cyyyy  minimum year %d\t",
//			SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, MIN_YEAR);
//		myGets(date, MAX_STR_LEN);
//		ok = checkDate(date, pDate);
//		if (!ok)
//			printf("Error try again\n");
//	} while (!ok);
//}


//int	 checkDate(char* date, Date* pDate)
//{
//	int day, month, year;
//	if (strlen(date) != 12)
//		return 0;
//	if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
//		|| (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
//		return 0;
//	sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
//	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
//		return 0;
//
//	if (day > DAY_MONTHS[month - 1])
//		return 0;
//
//	pDate->day = day;
//	pDate->month = month;
//	pDate->year = year;
//
//	return 1;
//}
