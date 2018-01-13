#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int morph(char *number);
static void signalHandler(int signal);
int respondedProcesses = 0;
int numChildProcess = 0;

int main(int argc, char *argv[]){

  FILE *fid;
  // check the number of command line parmeters
  // if incorrect input print message and exits
  if(argc < 2){
    printf("Usage: %s fileName \n", argv[0]);
    return 1;
  }
  // open the file
  fid = fopen(argv[1], "rb");
  // print message depending whether the file exists
  if (fid == NULL){
    printf("file %s does not exist \n", argv[1]);
    return 1;
  }

  // moving the file pointer to the end of the file using fseek()
  fseek(fid, 0, SEEK_END);
  // determine the file size using ftell().
  int size =ftell(fid);
  // determine how many numbers are in the file
  int len = size / sizeof(unsigned int);
  numChildProcess = len;
  fseek(fid, 0, SEEK_SET);
  // allocate memory for the array of process ids.
  int *cpid = (int*) malloc(size);
  int status;
  // allocate memory for the array of numbers
  unsigned int *num = (unsigned int*)malloc(size);
  // copy the numbers to a new pointer
  unsigned int *ptr = num;
  char buffer[len][len];
  char copyNum[len][len];
  int count = 0;
  // read all the unsigned integers
  fread(num, size, 1, fid);

  printf("\nHere are the numbers in the file:\n");

  for(int i = 0; i < len; i++){
    // convert them into strings
    sprintf(buffer[i], "%u", *ptr);
    printf("%s\n",buffer[i]);
    ptr++;
  }

  printf("\nReady to fork...\n");

  for(int j = 0; j < len; j++){
    // System call fork()returns the child process ID to the parent and returns 0 to the child process.
    cpid[j] = fork();
    // if cpid is 0, it will call children process morph()
    if(cpid[j]==0){
      morph(buffer[j]);
    }
  }
  signal(SIGUSR1, signalHandler);
  for(int k = 0; k < len; k++){
    // wait for each child processes to complete their tasks.
      int tempPid = waitpid(-1, &status, 0);
      int index;
      // when the waitpid() returns the child process id (cpid),
      // the parent program can search for cpid in the array pid.
      for(int x=0;x<len;x++){
        if(tempPid == cpid[x]){
          index = x;
          if(WEXITSTATUS(status) == 1){
            strcpy(copyNum[count], buffer[index]);
            count++;
          }
        }
      }
    }
  // print out all the prime numbers
  printf("\nSuccessful, result shows as follow:\n");
  for(int z = 0; z < count; z++){
      printf("%s is a prime number!\n", copyNum[z]);
  }
  //  free the memory of cpid and num
  free(cpid);
  free(num);
  fclose(fid);
  return 0;
}


int morph(char *number){
  int rc = 0;
  char *cmdParameter[3];
  cmdParameter[0] = "./isPrime";
  cmdParameter[1] = number;
  cmdParameter[2] = NULL;
  rc = execv(cmdParameter[0], cmdParameter);
  return rc;
}

static void signalHandler(int signal){
  ++respondedProcesses;
  printf("Processes finished: %d Processes still working: %d\n", respondedProcesses,(numChildProcess - respondedProcesses));
}
