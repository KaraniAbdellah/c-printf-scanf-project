#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "printf.h"
#include <unistd.h>
#include <stdbool.h>


// Tasks
/*
    Find a Type Of Second Argument Of printf() --> ...
    find a another way to print something in stdout --> write(stdout, &data, byteNumber)
    
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
            if (*p == '.') {
                p++;
                if (*(p) != 'f' && *(p) != 'd' && *(p) != 's') {
                    p++;
                    if (*(p) == 'f') {
                        float param = va_arg(args, double);
                        _print_f(param, true, (p--));
                        p++;
                    }
                    
                }
                else p++;
            }
            else if (*p  == 'd') {
                // integer
                int param = va_arg(args, int);
                _putchar(param);
            } else if (*p == 'c') {
                // character
                char param = va_arg(args, int);
                _print_c(param);
            }  else if (*p == 'f') {
                // float
                float param = va_arg(args, double);
                _print_f(param, false, NULL);
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




// get the number of digits of a number
int _get_integer_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        count++;
    }
    return count;
}


// convert number to string
char *toString(int length, int n) {
    char *number = (char *) malloc(sizeof(char) * (length + 1)); 
    // convert number to string
    int count = 0;
    while (n != 0) {
        number[length - 1 - count]  = (char) ((n % 10) + 48);
        n = n / 10;
        count++;
    }
    number[length] = '\0';
    return number;
}


// print a number
void _putchar(int n) {
    int count = 0;
    int length = _get_integer_digits(n);
    char *str = toString(length, n);
    write(1, str, length);
}


// print a character
void _print_c(char c) {
    write(1, &c, sizeof(c));
}


/*
    problem with floating number reset number like 
        0.03 = 0.0299998
*/

// concatinate two strings
char *concatinate(char *str1, char *str2, int l1, int l2) {
    char *str_re = (char *) malloc(sizeof(l1 + l2 + 1));
    int i = 0;
    for (; str1[i] != '\0'; i++) str_re[i] = str1[i];
    str_re[i] = ',';
    i = 1;
    for (; str2[i] != '\0'; i++) str_re[i + l1] = str2[i - 1];
    return str_re;
}

// trancate a number
void truncation(char *str, int nbr, int l) {
    printf("\nl = %d and nbr = %d\n", l, nbr);
    while (nbr != 0) {
        str[l] = '\0';
        l--;
        nbr--;
    }
}

// print a float number
void _print_f(float f, bool is_point, char *c_nbr) {
    // get the first and second part of float number
    float nbrOne = f - (int) f;
    float nbrTwo, check_nbr;
    int i = 10;
    while (1) {
        nbrTwo = nbrOne * i;
        check_nbr = nbrTwo - (int) nbrTwo;
        if (check_nbr == 0) break;
        i *= 10;
    }
    int re1 = (int) f;
    int re2 = nbrTwo;
    // convert to strings
    char length1 = _get_integer_digits(re1);
    char length2 = _get_integer_digits(re2);
    char *str1 = toString(length1, re1);
    char *str2 = toString(length2, re2);
    // concatinate two strings
    char *str_re =  concatinate(str1, str2, length1, length2);
    
    if (is_point == true) {
        int nbr = (int) *c_nbr - 48;
        if (nbr < length2) {
            int size_str_re = length1 + length2;
            truncation(str_re, nbr, size_str_re);
        }
    }
    
    // print The Result
    write(1, str_re, length1 + length2);
}


// print a string
void _printf_string(char *str) {
    // get the length os string
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) count++;
    write(1, str, count);
}









