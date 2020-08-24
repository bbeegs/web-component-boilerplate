#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  BUFFER_MAX 200


int main(int argc, char **argv){
  
  char base_path[BUFFER_MAX] = {};

  //check for the only arg that should be present
  if(argc != 2){
    fprintf(stderr,
	    "Invalid argument length\n"
	    "Pass only the name of file\n"
	    "Ex: my_web_component\n" );
    goto exit_on_error;
  }
  
  //ensure call to getcwd succeeded
  if(getcwd(base_path, BUFFER_MAX) == NULL){
    fprintf(stderr, "failed to get current working directory.");
    goto exit_on_error;
  }
  
  
  write_files(base_path, argv[1]);
  
 exit_on_error:
  return -1;

  return 0;
}
