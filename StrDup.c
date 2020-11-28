#include "csv.h"
#include <string.h>
char *Stringdup(char *src) {
    char *dst = malloc(strlen (src) + 1);  
    if (dst == NULL) return NULL;         
    strcpy(dst, src);                      
    return dst;                            
}