// Start The Implementation Of The Functions
/*
    %c       - character
    %s       - string
    %d       - Integer
    %f       - float
*/

/*
        problem with buffer size
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
    char buffer[1000];
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
            if (*p != 'd' && *p != 's' && *p != 'c' && *p != 'f' && *p != '\0') {
                afterChrcs = (char *) calloc(50, sizeof(char));
                while (*p != 'd' && *p != 's' && *p != 'c' && *p != 'f' && *p != '\0') {
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
                    char *str = va_arg(args, char *);
                    if (token != NULL && afterChrcs == NULL) {
                        strcpy(str, token);
                        token = strtok(NULL, " ");
                    }
                    if (afterChrcs != NULL) {
                        custom_string(str, afterChrcs, token);
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                case 'f': {
                    error(afterChrcs);
                    float *param = va_arg(args, float *);
                    if (token != NULL) {
                        *param = atof(token);
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                case 'c': {
                    error(afterChrcs);
                    char *c = va_arg(args, char *);
                    if (token != NULL) {
                        *c = token[0];
                        token = strtok(NULL, " ");
                    }
                    break;
                }
                case '\0': {
                    char *str = va_arg(args, char *);
                    custom_string(str, afterChrcs, token);
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
    // handle the test cases of reading until character after "^" && test cases of "%[^\n]20s"
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
        // get all digits after ]
        int pos_bracket = find(afterChrcs, 93);
        char *p = afterChrcs + pos_bracket + 1;
        int nbr_digits = atoi(p);
        if (nbr_digits != - 1 && *p != '\0') {
            int length_str = strlen(str);
            for (int i = nbr_digits + 1; i < length_str; i++) {
                str[i] = '\0';
            }
        }
        return;
    }
    
    // test cases of "%3s"
    if (is_integer(afterChrcs)) {
        int nbr_digits = atoi(afterChrcs);
        int j = 0;
        while (token != NULL && j < nbr_digits) {
            for (int i = 0; i < strlen(token) && j < nbr_digits; i++) {
                str[j] = token[i]; j++;
                if (strlen(str) >= nbr_digits) break; 
            }
            if (j < nbr_digits) {
                str[j] = ' '; j++;
                token = strtok(NULL, " ");
            }
            nbr_digits -= j;
        }
        str[j] = '\0';
    }
    return;
}





































