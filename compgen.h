#ifndef COMPGEN_H
#define COMPGEN_H

int write_files(char *cwd, const char *filename, const char *js_class_name, const char *custom_html_tag);
char * build_file_path(char *cwd, const char *filename, char *file_ext);
char * build_custom_html_tag(const char *custom_html_tag);
char * build_template_tag(const char *filename, const char *custom_html_tag);
#endif
