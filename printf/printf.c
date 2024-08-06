#include <stdarg.h>
#include <stdlib.h>
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
    va_end(args);
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


// coonvert number to string
char *to_string(int length, int n) {
    char *number = (char *) malloc(sizeof(char) * (length + 2));
    if (number == NULL) exit(1);
    int count = 0, start, end;
    if (n < 0) {
        n = -n;
        number[count++] = '-';
    }
    if (n == 0) number[count++] = '0';
    else {
        if (count == 0) {
            start = 0; end = length - 1; count = length;
        } else {
            start = 1; end = length; count = length + 1;
        }
        for (int i = end; i >= start; i--) {
            number[i] = (char) ((int) (n % 10) + 48);
            n /= 10;
        }
    }
    number[count] = '\0';
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
    if (new_str == NULL) exit(1);
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
        if (nbr_of_digits > length) {
            nbr_of_digits -= length; // "%.3d" and n = 34 --> add just one zero
            char *new_str = add_zeros(str, nbr_of_digits, length);
            write(1, new_str, length + nbr_of_digits);
            free(new_str);
            return;
        }
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




// concatenate two strings
char *concatenate(char *str1, char *str2, int l1, int l2, int nbr_of_digits) {
    char *str_re = (char *) malloc(sizeof(char) * (l1 + l2 + 2));
    if (str_re == NULL) exit(1);
    // Copy first string
    for (int i = 0; i < l1; i++) {
        str_re[i] = str1[i];
    }
    if (nbr_of_digits != 0) str_re[l1] = '.';
    for (int i = 0; i < l2; i++) {
        str_re[l1 + 1 + i] = str2[i];
    }
    str_re[l1 + l2 + 1] = '\0';
    return str_re;
}


// trancate a float
char *truncation_float(char *str, int nbr_of_digits, int length) {
    char *new_str = (char *) malloc(sizeof(char) * (nbr_of_digits + 1));
    if (new_str == NULL) exit(1);
    for (int i = 0; i < nbr_of_digits; i++) {
        new_str[i] = (i < length) ? str[i] : '0';
    }
    new_str[nbr_of_digits] = '\0';
    return new_str;
}

// get fractional part
int get_fractional_part(float fract_part) {
    float result, check_nbr;
    int multiplier = 10;
    while (1) {
        result = fract_part * multiplier;
        check_nbr = result - (int) result;
        if (check_nbr == 0) break;
        multiplier *= 10;
    }
    return (int) result;
}

// print a float number
void _print_f(float f, bool check, char *str_nbr) {
    // get the first and second part of float number
    int first_part = (int) f;
    int second_part = get_fractional_part(f - first_part);
    if (second_part < 0) second_part = -second_part;
    
    
    // convert to strings and getting number of digits
    char length1 = calculate_digits(first_part);
    char length2 = calculate_digits(second_part);
    char *str1 = to_string(length1, first_part);
    char *str2 = to_string(length2, second_part);
    if (str1[0] == '-') length1 += 1;
    
    // check if there nbr of digits specifiers
    if (check && str_nbr != NULL) {
        int nbr_of_digits = to_number(str_nbr);
        char *new_str = truncation_float(str2, nbr_of_digits, length2);
        // concatenate two strings
        char *str_re2 =  concatenate(str1, new_str, length1, length2 + nbr_of_digits, nbr_of_digits);
        write(1, str_re2, length1 + nbr_of_digits + 1);
        free(str1); free(str2); free(new_str); free(str_re2);
        return;
    }
    // concatenate two strings
    char *str_re =  concatenate(str1, str2, length1, length2, 1);
    // Print The Result
    write(1, str_re, length1 + length2);
    free(str1); free(str2); free(str_re);
}


// trancate a string
char *truncation_string(char *str, int nbr_of_characters, int length) {
    char *new_str = (char *) malloc(sizeof(char) * (nbr_of_characters + length + 1));
    if (new_str == NULL) exit(1);
    for (int i = 0; i < nbr_of_characters; i++) {   
        new_str[i] = str[i];
    }
    return new_str;
}


// print a string
void _printf_s(char *str, bool check, char *str_nbr) {
    // get the length of string
    int count = 0;
    while (str[count] != '\0') count++;
    int nbr_of_characters = count;
    if (check && str_nbr != NULL) {
        nbr_of_characters = to_number(str_nbr);
        if (nbr_of_characters < count) {
            char *new_str = truncation_string(str, nbr_of_characters, count);
            write(1, new_str, count + nbr_of_characters);
            free(new_str);
            return;
        }
    }
    write(1, str, count);
}



// Revise The Code --> Part Of va_list
// make a video and then samll documentation of printf

// Start scanf() --> see a video













