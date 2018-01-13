/*
File is isPrime.c

Purpose:
a program that checks if a given number is a prime number

input:
number - a positive int  entered via the command line parameters.  For example isPrime 1234

output:
0 - if the input number is not a prime number
1 - if the input number is a prime number
2 - if the command line parameter is not correct

Assumption:
the program does not check if the number is a positive integer

*/

/**************************************************************/
// INCLUDE FILES
//
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <signal.h>


/*************************************************************/
// PROTYPES
//
int isPrime(unsigned int number);


/*************************************************************/


int main(int argc, char *argv[])

{
	int i;

	unsigned int number;

	if (argc < 2) return(2);
	else number = atoi(argv[1]);
	if (isPrime(number)) {
		// please uncomment below when you test multiSpawnSignal.c
		// kill(getppid(), SIGUSR1);
		exit(1);
	}
	// please uncomment below when you test multiSpawnSignal.c
	// kill(getppid(), SIGUSR1);
	exit(0);
}


/*************************************************************/
/*
Purpose: check if the input number is a prime number
input:
number - the number to be checked

return:
0 - if the number is not a prime number
1 - if the number is a prime number
*/

int isPrime(unsigned int number)
{
	int i;
	for(i = 2; i*i <= number; i++) {
		usleep(100);
		if (number % i == 0) {
			return(0);
		}
	}
    // printf("%d is a prime number\n",number);
	return(1);
}
