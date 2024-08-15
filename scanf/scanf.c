// Start The Implementation Of The Functions
/*
    %%       - print '%'
    %c       - character
    %s       - string
    %d, %u   - decimal integer
    %x, %X   - hex integer
*/

/*
|| function return '\n'
|| getting all thing after %
|| in string sometime we do not need "s"
|| after \c --> print c as a character
|| number of % is not same of number of variables
    string case : 
        stop into space
        [^\n] --> The string is read until the newline character
        size of entered string > size of string --> generate an error
        %3s --> take just three character and stop into spaces
        &str --> generate An Error
        %[^\n]09810983s --> no problem
        %[^\n]20s --> :until the newline character, 20 characters are read
        %[^\"] --> reads a string until the "
        %[^\n] --> string is new_line || %[^\"]
        
    integer case : 
        %d --> normal case
        %.3d : error
        %dd : No Problem
        
    float case
        %f --> normal case
        %.3f : error
        
    chracter case:
        %c --> normal case
        %.3c : error
        
        
        search about using regex in strcmp()
        
        
        problem with integer
        problem with buffer size
        search about using regex in c in scanf()
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "scanf.h"
#include <ctype.h>

char _scanf(char *str, ...) {
    char *p = str;
    va_list args;
    va_start(args, str);
    // getting the characters
    char buffer[100];
    ssize_t n = read(0, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    // return first token
    char *token = strtok(buffer, " ");
    while (*p != '\0') {
        if (*p == '%') {
            p++;
            // getting what is comming after %
            char *afterChrcs = NULL;
            int i = 0;
            if (*p != 'd' && *p != 's' && *p != 'c' && *p != 'f') {
                afterChrcs = (char *) malloc(sizeof(char) * 20);
                while (*p != 'd' && *p != 's' && *p != 'c' && *p != 'f') {
                    afterChrcs[i] = *p; i++; p++;
                }
            }
            // test cases
            switch(*p) {
                case 'd': {
                    error(afterChrcs);
                    int *param = va_arg(args, int *);
                    if (token != NULL) {
                        *param = atoi(token);
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                case 's': {
                    // printf("String is %s\n", token);
                    char *str = va_arg(args, char *);
                    if (token != NULL && afterChrcs == NULL) {
                        strcpy(str, token);
                        token = strtok(NULL, " ");
                    }
                    if (afterChrcs != NULL) {
                        custom_string(str, afterChrcs, token);
                        return '\n'; // for reading until new line
                    }
                    break;
                }
                case 'f': {
                    error(afterChrcs);
                    // printf("Float is %s\n", token);
                    float *param = va_arg(args, float *);
                    if (token != NULL) {
                        *param = atof(token);
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                case 'c': {
                    error(afterChrcs);
                    // printf("Character is %s\n", token);
                    char *c = va_arg(args, char *);
                    if (token != NULL) {
                        *c = token[0];
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                default: {
                    printf("Unknown format specifier: %c\n", *p);
                }
            }
        } else if (*p != ' ') {
            error("error");
        } else;
        p++;
    }
    va_end(args);
    return '\n';
}



void error(char *str) {
    char error_message[20] = "Unknown Characters";
    if (str != NULL) {
        printf("Compiler --> %s", error_message);
        exit(1);
    }
}

int find(const char *str, char c) { 
    for(int i = 0; str[i] != '\0'; i++) if(str[i] == c) return i; 
    return -1;
} 



int is_integer(const char *str) {
    // Check if the string is empty
    if (str == NULL || *str == '\0') return 0;
    int i = 0;
    // Check for an optional leading negative sign
    if (str[0] == '-') {
        if (strlen(str) == 1) return 0;
        i = 1;
    }
    // Check each character to see if it is a digit
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1; // is integer
}



void custom_string(char *str, char *afterChrcs, char *token) {
    int pos_slash = find(afterChrcs, 94);
    // handle the test cases of reading until character after "^"
    if (pos_slash != -1) {
        while (token != NULL) {
            if (find(token, (int) afterChrcs[pos_slash + 1]) != -1) {
                int length = strlen(str); int i = 0;
                while (token[i] != afterChrcs[pos_slash + 1]) {
                    str[length] = token[i];
                    length++; i++;
                }
                str[length] = '\0'; break; 
            }
            strcat(str, token);
            strcat(str, " ");
            token = strtok(NULL, " ");
        }
    }
    
    // test cases of "%3s"
    if (is_integer(afterChrcs)) {
        int nbr_digits = atoi(afterChrcs);
        int j, length_token;
        while (token != NULL) {
            length_token = strlen(token);
            j = 0;
            for (int i = 0; i < nbr_digits; i++) {
                str[i] = token[j]; j++;
            }
            if (length_token < nbr_digits) {
                token = strtok(NULL, " ");
            }
        }
    }
    
    
    
    
    // test cases of "%[^\n]20s"
    
    
    
    return;
}





































