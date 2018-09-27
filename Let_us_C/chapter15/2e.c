/* To receive the month and year from the keyboard as integers 
 * and prints the calendar. Use user input to change month and year.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int no_of_days(int, int);
int starting_day(int, int);
void draw_calender(int, int, int, int);

int main()
{
	int month, year;
	char input;

	printf("Input month and year to view the calender\n");
	scanf(" %d %d", &month, &year);
	if (month < 1 || month >12 || year < 1) {
		printf("Invalid Input\n");
		exit(1);
	}
	putchar('\n');

	while (1) {
		int len = no_of_days(month, year);
		int day_1 = starting_day(month, year);
	
		draw_calender(month, year, day_1, len);
	
		printf("'n'-> next month, 'p'-> previous month\n");
		printf("'N'-> next year, 'P'-> previous year\n");	
		scanf(" %c", &input);

		switch (input) {
			case 'n':
				++month;
				if (month == 13) {
					month = 1;
					++year;
				}
				break;
			case 'p':
				--month;
				if (month == 0) {
					month = 12;
					--year;
				}
				break;
			case 'N':
				++year;
				break;
			case 'P':
				--year;
				break;
			default:
				printf("Exiting..\n");
				exit(1);
		}
		if (year == 0)
			exit(1);
	}
	return 0;
}
	
void draw_calender(int month, int year, int day_1, int len)
{
	char *months[] = {
		"January", "February", "March", "April", "May",
		"June", "July", "August", "September", "October",
		"November", "December"
	};
	printf("\t\t%s, %d\n", months[month-1], year);
	printf("Sun\tMon\tTue\tWed\tThu\tFri\tSat");

	for (int i = 0; i < day_1 + len; ++i) {
		(i%7) ? 0 : putchar('\n');

		if (i >= day_1)
			printf("%2d\t", i - day_1 + 1);
		else
			putchar('\t');
	}
	putchar('\n');
}

int no_of_days(int month, int year)
{
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (month != 2)
		return days[month - 1];
	else if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		return 29;
	else 
		return 28;
}

int starting_day(int month, int year)
{
	int day1;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	day1 = (year + d1 - d2 + d3) % 7;
	for (int i = 1; i < month; ++i)
		day1 += no_of_days(i, year);
	day1 = day1 % 7;
	return day1;
}
