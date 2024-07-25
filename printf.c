


#include <stdarg.h>
#include <stdio.h>

// Tasks
/*
    Find a Type Of Second Argument Of printf()
    find a another way to print something in stdout
    
    we have the format specifiers [ %d, %s, %i, %c, %f ]
    
    start with one specifier
*/


// Informations
/*
    ... :  arbitrary number of arguments like list
    va_list: pointe to the list that contain all arguments
    va_start: initialse a list by given [ listOfArgs & first param ]
    va_arg: getting first param by taking [ listOgArgs & type of arg ]
*/

void _printf(char *str, ...) {
    char *p = str;
    va_list args;
    va_start(args, str);
    for (; *p != '\0'; p++) {
        if (*p == '%') {
            p++;
            if (*p  == 'd') {
                // integer
            } else if (*p == 'c') {
                // character
                
            } else if (*p == 'f') {
                // float
                
            } else if (*p == 's') {
                // string
                
            } else {
                // error || another type
                
            }
        }
    }
}

















