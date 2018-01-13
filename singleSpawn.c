#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int morph(char *number);

int main(int argc, char *argv[]){

  FILE *fid;
  // check the number of command line parmeters
  // if incorrect number print message and exits
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
  int pid;
  int status;
  printf("Ready to fork...\n");

  unsigned int num;
  char buffer[150];
  // read the first unsigned integer
  fread(&num, sizeof(unsigned int),1, fid);
  // convert it into string
  sprintf(buffer, "%u", num);
  //System call fork() returns the child process ID to the parent and returns 0 to the child process.
  pid = fork();
  // if pid is 0, it will call children process
  if(pid == 0){
    morph(buffer);
  }else{// if pid is non zero, call parent process
    pid = wait(&status);
    // If the child process for which status was returned by the wait or waitpid function exited normally,
    // the WIFEXITED macro evaluates to TRUE
    if(WIFEXITED(status)){// Query status to see if a child process ended normally
      printf("Successful, exit code is %d \n", WEXITSTATUS(status));
    }
    // Obtain exit status of a child process
    // if the WIFEXITED macro indicates that the child process exited normally,
    // the WEXITSTATUS macro returns the exit code specified by the child
    if(WEXITSTATUS(status) == 1){
      printf("%u is a prime number\n", num);
    }
    if(WEXITSTATUS(status) == 0){
      printf("%u is not a prime number\n", num);
    }
  }
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
