#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  LG_BUFFER_MAX 300


//main routine -- writes the .html, .js, .css
int write_files(char *cwd, const char *filename, const char *js_class_name,
		const char *custom_html_tag){

  char exts[3][6] = {".html", ".js", ".css"};
  FILE *f_ptr;

  for(size_t i = 0; i < 3; i++){
    char * filepath = build_file_path(cwd, filename,*(exts+i));
    if (filepath == NULL){
       fprintf(stderr, "Failure constructing file path");
       return EXIT_FAILURE;
    }
    f_ptr = fopen(filepath, "w");
    
    if(f_ptr == NULL){
      fprintf(stderr, "Failure writing to file");
      return EXIT_FAILURE;
    }

    //switch on file extension type
    switch (i){
      
    case 0:; //html file
      fprintf(f_ptr,
	      "<!DOCTYPE html>\n"
	      "<html>\n"
	      "<head>\n"
	      "\t<meta charset=\"utf-8\">\n"
	      "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
	      "\t<title></title>\n"
	      "</head>\n"
	      "<body>\n"
	      "<%s></%s>\n"
	      "\t<template id=\"%s\">\n"
	      "\t\t<link rel=\"stylesheet\" href=\"./%s.css\">\n"
	      "\t</template>\n"
	      "\t<script src=\"./%s.js\"></script>\n"
	      "</body>\n"
	      "</html>\n",
	      custom_html_tag,
	      custom_html_tag,
	      custom_html_tag,
	      filename,
	      filename);
      
      break;
      
    case 1:       //js file
      fprintf(f_ptr,
	      "'use strict'\n"
	      "class %s extends HTMLElement {\n"
	      "\tconstructor() {\n"
	      "\t\tsuper();\n"
	      "\t\tconst shadow = this.attachShadow({ mode: \"open\" });\n"
	      "\t\tconst template = document.getElementById('%s');\n"
	      "\t\tconst content = template.content.cloneNode(true);\n"
	      "\t\tshadow.appendChild(content);\n"
	      "\t}\n\n"
	      "\tconnectedCallback() {\n\n"
	      "\t}\n\n"
	      "\tdisconnectedCallback() {\n\n"
	      "\t}\n\n"  
	      "\tattributeChangedCallback(name, oldValue, newValue) {\n"
	      "\n\t}\n\n"
	      "\tadoptedCallback() {\n\n"
	      "\t}"
	      "\n\n}\n\n"
	      "window.customElements.define('%s', %s);\n"
	      ,js_class_name,
	      custom_html_tag,
	      custom_html_tag,
	      js_class_name);
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
  return EXIT_SUCCESS;
}

//builds a complete file path
char * build_file_path(char *cwd, const char *filename, char *file_ext){

  int output_len = 0;
  char* full_path = malloc(strlen(cwd) + strlen(filename) +
			   strlen(file_ext) + sizeof(char)*3); 

  if (full_path == NULL){
    free(full_path);
    fprintf(stderr, "malloc failed - get more memory");
    goto  string_op_fail;
  }
  
  output_len = snprintf(full_path,LG_BUFFER_MAX,
			"%s/%s%s", cwd, filename, file_ext);
  
  if(output_len >= LG_BUFFER_MAX){
    fprintf(stderr, "your file path is likely corrupted due to\n"
	    "buffer overrun");
    free(full_path);
    goto string_op_fail;
  }
  
  return full_path;

 string_op_fail:
  return NULL;
}

