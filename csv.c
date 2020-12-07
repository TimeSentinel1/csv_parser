#include "csv.h"
#include <string.h>


void free_csv_line( char **parsed ) {
    char **ptr;

    for ( ptr = parsed; *ptr; ptr++ ) {
        free( *ptr );
    }

    free( parsed );
}

static int count_fields( const char *line, const char ch) {
    const char *ptr;
    int cnt, fQuote;

    for ( cnt = 1, fQuote = 0, ptr = line; *ptr; ptr++ ) {
        if ( fQuote ) {
            if ( *ptr == '\"' ) {
                if ( ptr[1] == '\"' ) {
                    ptr++;
                    continue;
                }
                fQuote = 0;
            }
            continue;
        }
        if(*ptr == '\"')
        {
             fQuote = 1;
            continue;
        } else if(*ptr == ch){
            cnt++;
            continue;
        } else {
            continue;
        }

   
    }

    if ( fQuote ) {
        return -1;
    }

    return cnt;
}

/*
 *  Given a string containing no linebreaks, or containing line breaks
 *  which are escaped by "double quotes", extract a NULL-terminated
 *  array of strings, one for every cell in the row.
 */
char **parse_csv( const char *line,const char ch) {
    char **buf, **bptr, *tmp, *tptr;
    const char *ptr;
    int fieldcnt, fQuote, fEnd;

    fieldcnt = count_fields( line,ch);

    if ( fieldcnt == -1 ) {
        return NULL;
    }

    buf = malloc( sizeof(char*) * (fieldcnt+1) );

    if ( !buf ) {
        return NULL;
    }

    tmp = malloc( strlen(line) + 1 );

    if ( !tmp ) {
        free( buf );
        return NULL;
    }

    bptr = buf;

    for ( ptr = line, fQuote = 0, *tmp = '\0', tptr = tmp, fEnd = 0; ; ptr++ ) {
        if ( fQuote ) {
            if ( !*ptr ) {
                break;
            }

            if ( *ptr == '\"' ) {
                if ( ptr[1] == '\"' ) {
                    *tptr++ = '\"';
                    ptr++;
                    continue;
                }
                fQuote = 0;
            }
            else {
                *tptr++ = *ptr;
            }

            continue;
        }
            if(*ptr == '\"')
            {
                fQuote = 1;
                continue;
            } else if (*ptr == '\0')
            {
                fEnd = 1;
            } else if(*ptr == ch)
            {
                     *tptr = '\0';
                *bptr = StringDup( tmp );

                if ( !*bptr ) {
                    for ( bptr--; bptr >= buf; bptr-- ) {
                        free( *bptr );
                    }
                    free( buf );
                    free( tmp );

                    return NULL;
                }

                bptr++;
                tptr = tmp;

                if ( fEnd ) {

                } else {
                  continue;
                }
            } else {
                 *tptr++ = *ptr;
                continue;
            }

            

        if ( fEnd ) {
            break;
        }
    }

    *bptr = NULL;
    free( tmp );
    return buf;
}