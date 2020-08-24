#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  BUFFER_MAX 300

char exts[3][6] = {".html", ".js", ".css"};

int write_files(char *cwd, char *filename){
  int result  = 0;
  for(size_t i = 0; i < 3; i++){
    char * filepath = build_file_path(cwd, filename,*(exts+i));
    printf("%s\n", filepath);
    free(filepath);
  }
  return result;
}


char * build_file_path(char *cwd, char *filename, char *file_ext){
  char* full_path = malloc(strlen(cwd) + strlen(filename) +
			   strlen(file_ext) + sizeof(char)*3); 
  if (full_path == NULL){
    free(full_path);
    fprintf(stderr, "malloc failed - get more memory");
  }
  
  int output_len = 0;
  output_len = snprintf(full_path,
			BUFFER_MAX,
			"%s/%s%s", cwd, filename, file_ext);
  if(output_len >= BUFFER_MAX){
    fprintf(stderr, "your file path is likely corrupted due to\n"
	    "buffer overrun");
  }
  return full_path;
}

