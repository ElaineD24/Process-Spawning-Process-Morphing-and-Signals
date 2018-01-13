#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

  unsigned int num;
  char buffer[150];
  //  read the first unsigned integer
  fread(&num, sizeof(unsigned int),1, fid);
  // convert it into string
  sprintf(buffer, "%u", num);
  morph(buffer);
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
