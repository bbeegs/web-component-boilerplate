#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "compgen.h"
#define  BUFFER_MAX 200


int main(int argc, char **argv){

  //declarations
  char base_path[BUFFER_MAX] = {};
  const char *filename;
  const char *js_class_name;
  const char *custom_html_tag;
  
  //check for the only arg that should be present
  if(argc != 4){
    fprintf(stderr,
	    "Invalid argument length\n"
	    "Compgen expects 3 arguments: filename, javascript "
	    "component class name, and custom html tag\n"
	    "Ex: my_web_component MyWebComponent my-web-comp\n" );
    goto exit_on_error;
  }

  //assign cli args
  filename = argv[1];
  js_class_name = argv[2];
  custom_html_tag = argv[3];

  if(strchr(custom_html_tag, '-') == NULL){
    fprintf(stderr, "custom html tag must contain a dash\n");
    goto exit_on_error;
  }
  
  //ensure call to getcwd succeeded
  if(getcwd(base_path, BUFFER_MAX) == NULL){
    fprintf(stderr, "failed to get current working directory.");
    goto exit_on_error;
  }
  
  
  write_files(base_path, filename, js_class_name, custom_html_tag);
  
 exit_on_error:
  return -1;

  return 0;
}
