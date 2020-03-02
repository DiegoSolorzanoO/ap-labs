// Diego Solorzano Ortiz A01422048

#include <stdio.h>
#include <stdlib.h>

int validate_data(int yearday, int leap) {
    if (((leap==1 && yearday<=366) || (leap==0 && yearday<=365)) && yearday>0)
    {
        return 1;
    } 
    else
    {
        printf("ERROR: Your year day is out of bounds!\n");
        return 0;
    }
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    static char daytab[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    int leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (validate_data(yearday,leap)==1) {
        int last;
        while (yearday>0) {
            last = yearday;
            yearday -= daytab[leap][*pmonth];
            if (yearday>0) {
                *pmonth+=1;
            } else {
                *pday = last;
            }
        }
    } else {
        *pmonth = -1;
        return;
    }
};

int main(int argc, char *argv[]) {
    if (argv[1] && argv[2])
    {
        int year = atoi(argv[1]);
        int yearday = atoi(argv[2]);
        int month = 0, day = 0;
        int *pmonth, *pday;
        pmonth = &month;
        pday = &day;
        char* months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}; 

        month_day(year,yearday,pmonth,pday);
        if (month!=-1)
        {
            printf("%s %02d, %d\n",months[month],day,year);   
        }
    } else
    {
        printf("Data missing, add the year and year day to work correctly\n");
    }
    return 0;
}
