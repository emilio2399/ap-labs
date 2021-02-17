#include <stdio.h>
#include <stdlib.h>

//#define   LOWER  0       /* lower limit of table */
//#define   UPPER  100     /* upper limit */
//#define   STEP   20      /* step size */

/* print Fahrenheit-Celsius table */

int main(int argc, char** argv)
{

    if(argc==2){
        printf("Simple conversion\n");
        printf("Fahrenheit: %3d, Celcius: %6.1f\n", atoi(argv[1]), (5.0/9.0)*(atoi(argv[1])-32));
    }else if(argc>3){
        printf("Range Conversion\n");
        int fahr;    
        for (fahr = atoi(argv[1]); fahr <= atoi(argv[2]); fahr = fahr + atoi(argv[3]))
        printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }else{
        printf("Need at least one argument");
    }

    return 0;
}