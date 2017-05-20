/* This was done in Fall 2015. */
/* This program determines which day of the week a given calendar day falls on. */

/* Jacob Chapin */
/* CS211 Assignment 2*/

#include <stdio.h>

/* Function Prototypes */

int length(int, int);
int day_of_week(int, int, int);
void print_calendar(int, int);

int main(void)
{
	/* Get month and year */
	
	int month, year;
	printf("Enter month (1 = Jan, ..., 12 = Dec): ");
	scanf("%d", &month);
	
	/* Make sure month is valid */
	
	while (month < 1 || month > 12)
	{
		printf("Error: month must be in range 1..12\n");
		printf("Enter month (1 = Jan, ..., 12 = Dec): ");
		scanf("%d", &month);
	}
	printf("Enter year (>0): ");
	scanf("%d", &year);
	
	/* Make sure year is valid */
	
	while (year < 1)
	{
		printf("Error: year must be > 0\n");
		printf("Enter year (>0): ");
		scanf("%d", &year);
	}

	int days = length(month, year);
	int first_day = day_of_week(1, month, year);

	/* Print the calendar */

	print_calendar(first_day, days);
	return 0;
}

/* Gets the number of days in the chosen month */

int length(int month, int year)
{
	int days;
	switch (month)
	{
		case 1:
			days = 31;
			break;
		
		/* Returns 29 days if year is a leap year */
		
		case 2:
			if ((year % 4) == 0 && (year % 100) != 0)
			{
				days = 29;
			}
			else
			{
				if ((year % 400) == 0)
				{
					days = 29;
				}
				else
				{
					days = 28;
				}
			}
			break;
		
		case 3:
			days = 31;
			break;
		
		case 4:
			days = 30;
			break;

		case 5:
			days = 31;
			break;

		case 6:
			days = 30;
			break;

		case 7:
			days = 31;
			break;

		case 8:
			days = 31;
			break;

		case 9:
			days = 30;
			break;

		case 10:
			days = 31;
			break;

		case 11:
			days = 30;
			break;

		case 12:
			days = 31;
			break;
	}
	return days;
}

/* Get the day of the week on which the day of the month falls */

int day_of_week(int day, int month, int year)
{
	/* h = day of the week. 0 = Saturday, 6 = Friday */
	/* j = century = floor of (year / 100) */
	/* k = year within century = year % 100 */
	/* m = month. 3 = March, 14 = February. */
	

	/* Adjust month and year values if needed */

	int m;
	if (month == 1)
	{
		m = 13;
		year--;
	}
	else if (month == 2)
	{
		m = 14;
		year--;
	}
	else
	{
		m = month;
	}
	int j = year / 100;
	int k = year % 100;

	/* Zeller's Congruence */

	int h = (day+((13*(m+1))/5)+k+(k/4)+(j/4)+(5*j))%7;
	return h;
}

/* Print desired calendar */

void print_calendar(int start_day, int month_length)
{
	/* Print days of the week*/
	
	printf("Sun Mon Tue Wed Thu Fri Sat\n");

	/* Print whitespace leading up to the first day */

	int blank = start_day - 1;
	if (blank < 0)
	{
		blank = 6;
	}
	int i;
	for (i = 0; i < blank; i++)
	{
		printf("    ");
	}

	/* Print the rest of the calendar */

	int weekday = blank + 1;
	int monthday;
	for (monthday = 1; monthday <= month_length; monthday++)
	{
		printf("%3d ", monthday);
		if (weekday % 7 == 0)
		{
			printf("\n");
		}
		weekday++;
	}

	/* Print a newline character if needed for clean output */
	
	if (((weekday - 1) % 7) != 0)
	{
		printf("\n");
	}
}
