#ifndef CSV_DOT_H_INCLUDE_GUARD
#define CSV_DOT_H_INCLUDE_GUARD

#include <stdio.h>
#include <stdlib.h>
#define CSV_ERR_LONGLINE 0
#define CSV_ERR_NO_MEMORY 1

char **parse_csv( const char *line, const char ch);
char* StringDup(char *src);
void free_csv_line( char **parsed );
char **split_on_unescaped_newlines(const char *txt);
char *fread_csv_line(FILE *fp, int max_line_size, int *done, int *err);

#endif
