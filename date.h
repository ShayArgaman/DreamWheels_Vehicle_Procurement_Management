//date.h
#pragma once

#define MIN_YEAR 2023

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

Date generateRandomDate();

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
