#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   LOWER  0       /* lower limit of table */
#define   UPPER  300     /* upper limit */
#define   STEP   20      /* step size */

/* print Fahrenheit-Celsius table */

int main(int argc, char **argv)
{
    int fahr;

    if(argv[2] && argv[3]) {
	int lower = atoi(argv[1]);
	int upper = atoi(argv[2]);
	int step = atoi(argv[3]);
	for (fahr = lower; fahr <= upper; fahr = fahr + step)
	   printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    } else {
	if(argv[1]) {
	   printf("Fahrenheit: %3d, Celcius: %6.1f\n", atoi(argv[1]), (5.0/9.0)*(atoi(argv[1])-32));
	}
    }
    
    return 0;
}
