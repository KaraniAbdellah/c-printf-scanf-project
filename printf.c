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
    bool check;
    char *str_nbr;
    for (p = str; *p != '\0'; p++) {
        // print The String
        check = false; str_nbr = NULL;
        if (*p != '%') _print_c(*p, check, str_nbr);
        if (*p == '%') {
            p++; check = false; str_nbr = NULL;
            if (*p == '.') {
                // start getting number if digits or charcaters
                p++; int count = 0;
                str_nbr = (char *) malloc(2 * sizeof(char));
                while (*p != 'd' && *p != 's' && *p != 'f' && *p != 'c') {
                    str_nbr[count] = *p;
                    p++; count++;
                    str_nbr = realloc(str_nbr, (count + 2) * sizeof(char));
                }
                str_nbr[count] = '\0';
                check = true;
                // printf("\nHint : str_nbr : %s || count = %d || check = %d\n", str_nbr, count, check);
            }
            if (*p  == 'd') {
                // integer
                int param = va_arg(args, int);
                _putchar(param, check, str_nbr);
            }
            if (*p == 'c') {
                // character
                char param = va_arg(args, int);
                _print_c(param, check, str_nbr);
            }
            if (*p == 'f') {
                // float
                float param = va_arg(args, double);
                
                _print_f(param, check, str_nbr);
            } 
            if (*p == 's') {
                // string
                char *param = va_arg(args, char*);
                _printf_string(param, check, str_nbr);
            } 
            if (*p == 'x' || *p == 'p' || *p == 'i') {
                // error || another type
                _printf_string("Error || Another Type\n", check, str_nbr);
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

// convert string to number
int toNumber(char *str_nbr) {
    int re = 0;
    for (int i = 0; str_nbr[i] != '\0'; i++) {
        re = re * 10 + ((int) str_nbr[i] - 48);
    }
    return re;
}


// add zero to string
char *add_zero(char *str, int nbr_of_digits, int length) {
    char *new_str = (char *) malloc(sizeof(char) * (nbr_of_digits + length + 1));
    int i = 0;
    while (i < nbr_of_digits) {
        new_str[i] = '0';
        i++;
    }
    for (int j = 0; str[j] != '0'; j++) {
        new_str[i] = str[j]; i++;
    }
    new_str[i] = '\0';
    return new_str;
}


// print a number
void _putchar(int n, bool check, char *str_nbr) {
    int count = 0;
    int length = _get_integer_digits(n);
    char *str = toString(length, n);
    if (check == true && str_nbr != NULL) {
        int nbr_of_digits = toNumber(str_nbr);
       //  printf("\nlength = %d and str = %s and nbr_of_digits = %d\n", length, str, nbr_of_digits);
        char *new_str = add_zero(str, nbr_of_digits, length);
        write(1, new_str, length + nbr_of_digits);
        return;
    }
    write(1, str, length);
}


// print a character
void _print_c(char c, bool check, char *str_nbr) {
    if (check == true && str_nbr != NULL) {
        _printf_string("    --> Complier : Error\n", false, NULL);
        exit(0);
    }
    write(1, &c, sizeof(c));
}




// concatinate two strings
char *concatinate(char *str1, char *str2, int l1, int l2) {
    char *str_re = (char *) malloc(sizeof(l1 + l2 + 2));
    for (int i = 0; i < l1 + l2 + 1; i++) {
        if (i < l1) str_re[i] = str1[i];
        else if (i == l1) str_re[i] = '.';
        else str_re[i] = str2[i - l1 - 1];
    }
    str_re[l2 + l1 + 1] = '\0';
    return str_re;
}


// trancate a float
char *truncation_float(char *str, int nbr_of_digits, int length) {
    if (nbr_of_digits <= length) {
        for (int i = nbr_of_digits; i < length; i++) {
            str[i] = '\0';
        }
        return str;
    } else {
        char *new_str = (char *) malloc(sizeof(char) * (nbr_of_digits + length));
        for (int i = 0; i < length; i++) new_str[i] = str[i];
        for (int i = length; i < nbr_of_digits; i++) new_str[i] = '0';
        return new_str;
    }
}


// print a float number
void _print_f(float f, bool check, char *str_nbr) {
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
    int re1 = (int) f; // first part
    int re2 = nbrTwo; // second
    
    // convert to strings and getting number of digits
    char length1 = _get_integer_digits(re1);
    char length2 = _get_integer_digits(re2);
    char *str1 = toString(length1, re1);
    char *str2 = toString(length2, re2);
    
    // concatinate two strings
    char *str_re =  concatinate(str1, str2, length1, length2);
    
    // check if there nbr of digits specifiers
    int nbr_of_digits = 0;
    if (check == true && str_nbr != NULL) {
        nbr_of_digits = toNumber(str_nbr);
        char *new_str = truncation_float(str2, nbr_of_digits, length2);
        // concatinate two strings
        char *str_re2 =  concatinate(str1, new_str, length1, nbr_of_digits);
        write(1, str_re2, length1 + nbr_of_digits + 1);
        return;
     }
    // Print The Result
    write(1, str_re, length1 + length2);
}


// trancate a string
char *truncation_string(char *str, int nbr_of_characters, int length) {
    char *new_str = (char *) malloc(sizeof(char) * (nbr_of_characters + length + 1));
    for (int i = 0; i < nbr_of_characters; i++) {
        new_str[i] = str[i];
    }
    return new_str;
}


// print a string
void _printf_string(char *str, bool check, char *str_nbr) {
    // get the length of string
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) count++;
    int nbr_of_characters = 0;
    if (check == true && str_nbr != NULL) {
        nbr_of_characters = toNumber(str_nbr);
        // printf("\ncount = %d and str = %s and nbr_of_characters = %d\n", count, str, nbr_of_characters);
        if (nbr_of_characters < count) {
            char *new_str = truncation_string(str, nbr_of_characters, count);
            write(1, new_str, count + nbr_of_characters);
            return;
        }
    }
    write(1, str, count);
}



// Try To Find The Error
// If Every Thing Working Good -->  Try To Reduce The Complexity


// Some Test Cases --> You Can Generate An Error
















