#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  LG_BUFFER_MAX 300
#define  SM_BUFFER_MAX 150

//main routine -- writes the .html, .js, .css
int write_files(char *cwd, const char *filename, const char *js_class_name,
		const char *custom_html_tag){

  char exts[3][6] = {".html", ".js", ".css"};
  FILE *f_ptr;

  for(size_t i = 0; i < 3; i++){
    char * filepath = build_file_path(cwd, filename,*(exts+i));
    f_ptr = fopen(filepath, "w");
    
    if(f_ptr == NULL){
      fprintf(stderr, "Failure writing to file");
      return EXIT_FAILURE;
    }

    //switch on file extension type
    switch (i){
    case 0:; //html file

      char * custom_tag = build_custom_html_tag(custom_html_tag);
      char * template_tag = build_template_tag(filename, custom_html_tag);
      
      if(custom_tag == NULL || template_tag == NULL){
	return EXIT_FAILURE;
      }
      
      fprintf(f_ptr,
	      "<!DOCTYPE html>\n"
	      "<html>\n"
	      "<head>\n"
	      "\t<meta charset=\"utf-8\">\n"
	      "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
	      "\t<title></title>\n"
	      "</head>\n"
	      "<body>\n"
	      "%s\n"
	      "%s\n"
	      "</body>\n"
	      "</html>\n", custom_tag, template_tag);
      free(custom_tag);
      free(template_tag);
      break;
      
    case 1:       //js file
      fprintf(f_ptr,
	      "'use strict'");
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
    goto STRING_OP_FAIL;
  }
  
  output_len = snprintf(full_path,LG_BUFFER_MAX,
			"%s/%s%s", cwd, filename, file_ext);
  
  if(output_len >= LG_BUFFER_MAX){
    fprintf(stderr, "your file path is likely corrupted due to\n"
	    "buffer overrun");
    goto STRING_OP_FAIL;
  }
  
  return full_path;

 STRING_OP_FAIL:
  return NULL;
}

//build the custom html tag
char * build_custom_html_tag(const char *custom_html_tag){

  int output_len = 0;
  char* full_tag = malloc((strlen(custom_html_tag) * 2) +
			  sizeof(char)*6); //account for <, >, <, /, >, \0 
  if (full_tag == NULL){
    free(full_tag);
    fprintf(stderr, "malloc failed - get more memory");
    goto STRING_OP_FAIL;
  }
  
  output_len = snprintf(full_tag, SM_BUFFER_MAX,
			"<%s></%s>", custom_html_tag, custom_html_tag);
  
  if(output_len >= SM_BUFFER_MAX){
    fprintf(stderr, "Issue creating custom tag");
    goto STRING_OP_FAIL;
  }
  return full_tag;

 STRING_OP_FAIL:
  return NULL;
}

//construct the html template tag and add id
char * build_template_tag(const char *filename, const char *custom_html_tag){

  int output_len = 0;

  char *css_link = malloc(sizeof(char)*SM_BUFFER_MAX);
  if (css_link == NULL){
    fprintf(stderr, "css link malloc failed - get more memory");
    goto STRING_OP_FAIL;
  }

  //construct css link for tempalte
  output_len = snprintf(css_link,SM_BUFFER_MAX,
			"<link rel=\"stylesheet\" href=\"./%s.css\">", filename);

  if(output_len >= SM_BUFFER_MAX){
    fprintf(stderr, "Issue creating css link tag");
    goto STRING_OP_FAIL;
  }

  //construct full template tag
  char *full_tag = malloc(sizeof(char)*LG_BUFFER_MAX);  
  if (full_tag == NULL){
    free(full_tag);
    fprintf(stderr, "malloc failed - get more memory");
    goto STRING_OP_FAIL;
  }
  
  
  output_len = snprintf(full_tag,LG_BUFFER_MAX,
			"<template id=\"%s\">\n"
			"\t%s\n"
			"</template>", custom_html_tag, css_link);
  
  if(output_len >= LG_BUFFER_MAX){
    fprintf(stderr, "Issue creating custom tag");
    goto STRING_OP_FAIL;
  }
  free(css_link);
  return full_tag;

 STRING_OP_FAIL:
  return NULL;
}
