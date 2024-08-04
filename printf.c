#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "printf.h"
#include <unistd.h>
#include <stdbool.h>


#define MAX_SPECIFIER_LENGTH 100


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
    va_list args;
    va_start(args, str);
    bool check;
    char *str_nbr;
    for (const char *p = str; *p != '\0'; p++) {
        // print The String
        check = false; str_nbr = NULL;
        if (*p != '%') _print_c(*p, check, str_nbr);
        if (*p == '%') {
            p++;
            if (*p == '.') {
                // start getting numbers of digits or charcaters
                p++; int count = 0;
                str_nbr = (char *) malloc(MAX_SPECIFIER_LENGTH * sizeof(char));
                while (*p && (*p != 'd' && *p != 's' && *p != 'f' && *p != 'c')) {
                    if (count < MAX_SPECIFIER_LENGTH - 1) {
                        str_nbr[count++] = *p; p++;
                    }
                }
                str_nbr[count] = '\0';
                check = true;
            }
            switch (*p) {
                case 'd': {
                    // integer
                    int param = va_arg(args, int);
                    _print_d(param, check, str_nbr); break;
                }
                case 'c': {
                    // character
                    char param = va_arg(args, int);
                    _print_c(param, check, str_nbr); break;
                }
                case 'f': {
                    // float
                    float param = va_arg(args, double);
                    _print_f(param, check, str_nbr); break;
                }
                case 's': {
                    // string
                    char *param = va_arg(args, char*);
                    _printf_s(param, check, str_nbr); break;
                }
                case 'x':
                case 'p':
                case 'i':
                case 'u':
                case 'n': {
                    // error || another type
                    _printf_s("Error || Another Type\n", check, str_nbr); break;
                }
                default:
                    // handle unknown format specifiers
                    _printf_s("Error || Unknown Format Specifier\n", check, str_nbr); break;
            }
        }
    }
}




// get the number of digits from a number
int calculate_digits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    int count = 0;
    while (n != 0) {
        n /= 10;
        count++;
    }
    return count;
}


// convert number to string --> fix this function to negative numbers for float
char *to_string(int length, int n) {
    char *number = (char *) malloc(sizeof(char) * (length + 1)); 
    int count = 0;
    if (n < 0) {
        number[count++] = '-';
        n = -n;
    }
    if (n == 0) number[count++] = '0';
    else {
        int end = length;
        while (n != 0) {
            number[end--]  = (char) ((n % 10) + '0');
            n = n / 10;
        }
    }
    number[length + 1] = '\0';
    return number;
}

// convert string to number
int to_number(char *str_nbr) {
    int re = 0;
    for (int i = 0; str_nbr[i] != '\0'; i++) {
        re = re * 10 + ((int) str_nbr[i] - 48);
    }
    return re;
}


// add zero to string
char *add_zeros(char *str, int nbr_of_digits, int length) {
    char *new_str = (char *) malloc(sizeof(char) * (nbr_of_digits + length + 1));
    int i = 0;
    while (i < nbr_of_digits) {
        new_str[i] = '0';
        i++;
    }
    for (int j = 0; j < length; j++) {
        new_str[i] = str[j]; i++;
    }
    new_str[i] = '\0';
    return new_str;
}


// print a number
void _print_d(int n, bool check, char *str_nbr) {
    int length = calculate_digits(n);
    char *str = to_string(length, n);
    if (check == true && str_nbr != NULL) {
        int nbr_of_digits = to_number(str_nbr);
        char *new_str = add_zeros(str, nbr_of_digits, length);
        write(1, new_str, length + nbr_of_digits);
        free(new_str);
        return;
    }
    write(1, str, length + 1);
    free(str);
}


// print a character
void _print_c(char c, bool check, char *str_nbr) {
    if (check == true && str_nbr != NULL) {
        _printf_s("    --> Complier : Error\n", false, NULL);
        exit(0);
    }
    write(1, &c, sizeof(c));
}




// concatinate two strings
char *concatinate(char *str1, char *str2, int l1, int l2) {
    char *str_re = (char *) malloc(sizeof(char) * (l1 + l2 + 2));
    // Copy first string
    for (int i = 0; i < l1; i++) {
        str_re[i] = str1[i];
    }
    str_re[l1] = '.';
    for (int i = 0; i < l2; i++) {
        str_re[l1 + 1 + i] = str2[i];
    }
    str_re[l1 + l2 + 1] = '\0'; 
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
        for (int i = 0; i < length; i++) {
            new_str[i] = str[i];
        }
        for (int i = length; i < nbr_of_digits; i++) {
            new_str[i] = '0';
        }
        new_str[nbr_of_digits] = '\0';
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
    char length1 = calculate_digits(re1);
    char length2 = calculate_digits(re2);
    char *str1 = to_string(length1, re1);
    char *str2 = to_string(length2, re2);
    
    // check if there nbr of digits specifiers
    if (check == true && str_nbr != NULL) {
        int nbr_of_digits = to_number(str_nbr);
        char *new_str = truncation_float(str2, nbr_of_digits, length2);
        // concatinate two strings
        char *str_re2 =  concatinate(str1, new_str, length1, length2 + nbr_of_digits);
        write(1, str_re2, length1 + nbr_of_digits + length2);
        return;
    }
    // concatinate two strings
    char *str_re =  concatinate(str1, str2, length1, length2);
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
void _printf_s(char *str, bool check, char *str_nbr) {
    // get the length of string
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) count++;
    int nbr_of_characters = 0;
    if (check == true && str_nbr != NULL) {
        nbr_of_characters = to_number(str_nbr);
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
















