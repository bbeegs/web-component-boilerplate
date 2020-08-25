#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  BUFFER_MAX 300

int write_files(char *cwd, const char *filename, const char *js_class_name, const char *custom_html_tag){

  char exts[3][6] = {".html", ".js", ".css"};
  FILE *f_ptr;
  for(size_t i = 0; i < 3; i++){
    char * filepath = build_file_path(cwd, filename,*(exts+i));
    f_ptr = fopen(filepath, "w");
    if(f_ptr == NULL){
      return -1;
    }
    switch (i){
    case 0: //html file
      fprintf(f_ptr,
	      "<!DOCTYPE html>\n"
	      "<html>\n"
	      "<head>\n"
	      "\t<meta charset=\"utf-8\">\n"
	      "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
	      "\t<title></title>\n"
	      "</head>\n"
	      "<body>\n"
	      "</body>\n"
	      "</html>\n");
      break;
    case 1:       //js file
      fprintf(f_ptr, "'use strict'");
      break;
    case 2:       //css file
      fprintf(f_ptr,
	      ":host{}");
      break;
    }
    fclose(f_ptr);
    printf("%s\n", filepath);
    free(filepath);
  }
  return 0;
}


char * build_file_path(char *cwd, const char *filename, char *file_ext){
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

