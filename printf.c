#include <stdarg.h>
#include "printf.h"
#include <stdio.h>
#include <unistd.h>

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
    va_start: initialse a list by given [ listOfArgs & first_param ]
    va_arg: getting first param by taking [ listOfArgs & type_of_arg ]
    
    ssize_t write(int fd, const void *buf, size_t count);
        fd : file descriptor is stdout = 1
        buf: data to be written
        count: nbr of byte to write

*/

void _printf(char *str, ...) {
    char *p;
    va_list args;
    va_start(args, str);
    for (p = str; *p != '\0'; p++) {
        // print The String
        if (*p != '%') _print_c(*p);
        if (*p == '%') {
            p++;
            if (*p  == 'd') {
                // integer
                int param = va_arg(args, int);
                _putchar(param);
            } else if (*p == 'c') {
                // character
                char param = va_arg(args, int);
                _print_c(param);
            } else if (*p == 'f') {
                // float
                float param = va_arg(args, double);
                _print_f(param);
            } else if (*p == 's') {
                // string
                char *param = va_arg(args, char*);
                _printf_string(param);
            } else {
                // error || another type
                _printf_string("Error || Another Type");
            }
        }
    }
}


void _putchar(int n) {
    write(1, &n, sizeof(int));
}

void _print_c(char c) {
    write(1, &c, sizeof(char));
}

void _print_f(float f) {
    write(1, &f, sizeof(float));
}

void _printf_string(char *str) {
    write(1, &str, sizeof(str) / sizeof(char));
}









