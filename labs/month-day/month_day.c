#include <stdio.h>
#include <stdlib.h>


void month_day(int year, int yearday, int* pyear, int* pday){

    	if (*pday > 366){
            printf("Date not valid\n");
            return;
	}

	int months_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "Octobe", "November", "December"};
	if (year % 4 == 0)
		months_days[1] = 29;
	int yday = *pday;
	int month_cont = 0;
	for(int i = 0; i < 12; i++){
		if (yday > months_days[i]){
			yday = yday - months_days[i];
			month_cont ++;
		}else{
			break;
		}
	}
	printf("%s %d, %d\n", months[month_cont], yday, *pyear);
}

int main(int argc, char* argv[]) {
	int year = atoi(argv[1]);
	int day = atoi(argv[2]);
	int* p_year = &year;
	int* p_day = &day;
	month_day(year, day, p_year, p_day);
	return 0;
}
