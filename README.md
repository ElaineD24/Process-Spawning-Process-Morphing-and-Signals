# Process-Spawning-Process-Morphing-and-Signals
Assignment 5  12/08/2017

STUDENT INFORMATIONS
-------------------
NAME : Elaine Deng
STUDENT ID : 101045610

PROGRAM PURPOSE
---------------
Reading from binary files:
  opening and closing a file (fopen() and fclose(), reading from a file (fread())

Process spawning:
  differentiating between parent and child processes (fork())
  examining the return code of the child process()
  waiting for a child process (wait() and waitpid())

Program Morphing:
  changing from one program to another (excev())

Usage of signals:
  signals and function pointers

This program can open a binary file which contains unsigned integers and check whether the integers are prime. singlePrime and singleSpawn can only check the fist unsigned integer while multiSpawn can check all the unsigned integers in the binary file since I did the first bonus question.

FILES INFORMATIONS
------------------
There are 13 files in total:

README

Four Makefiles:
Makefile1
Makefile2
Makefile3
Makefile4

createBinary.c - a program that creates a binary file from a given set of numbers
isPrime.c - the base program for checking whether a number is a prime number
singlePrime.c - read from a binary file you give as a command line parameter the fist unsigned integer and morph itself to the isPrime program
singleSpawn.c - it will spawn a child process
multiSpawn.c - it will spawn multiple child processes
multiSpawnSignal.c
prime.bin - a file that contains 12 unsigned numbers in binary format
prime.txt - a file that contains 12 unsigned numbers in ASCII format

COMPILE AND INSTRUCTIONS ON USING THE PROGRAM
---------------------------------------------
1. You need to compile isPrime.c, use:
gcc -o isPrime isPrime.c

then you can test any number whether it is prime, for example:
./isPrime 3

2. You need to compile singlePrime.c, use:
make -f Makefile1

then this program will read from a binary file you give as a command line parameter the fist unsigned integer and morph itself to the isPrime program, to run and test it:
./singlePrime prime.bin

3. You need to compile singleSpawn.c, use:
make -f Makefile2

then this program will spawn a child process and the parent program will wait and print out whether the given input number is prime, to run and test it:
./singleSpawn prime.bin

4. You need to compile multiSpawn.c, use:
make -f Makefile3

then this program will spawn multiple child processes and the parent program will wait until all the child processes have completed and then print all the prime numbers, to run and test it:
./multiSpawn prime.bin

5. You need to compile multiSpawnSignal.c and uncomment the two kills in main() in isPrime.c, then use:
make -f Makefile4

then it will print how many processes have finished their execution and how many processes are still working, to run and test it:
./multiSpawnSignal prime.bin


LIMITATION
----------
1. In isPrime.c, the print statement has been commented, so there won't be any output after you run isPrime or singlePrime.
2. If you want to test whether the first two program runs correctly, you can just uncomment the print statement.
3. Since the Task III overview said we should wait until all the child processes have completed their work and then prints all the prime numbers, my program will wait and then print all the integers at the same time instead of printing them one by one.
4. The first bonus question has been attempted. Therefore, in multiSpawn.c, the program will go through all the unsigned integers and check whether they are prime numbers instead of just checking the first ten numbers.
5. The second bonus question has been attempted. Therefore, you need to uncomment the two kills in main() in isPrime.c then compile Makefile4.
