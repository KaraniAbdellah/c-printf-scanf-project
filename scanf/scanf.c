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
        
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char _scanf(char *str, ...) {
    char *p = str;
    va_list args;
    va_start(args, str);
    char message[20] = "Unuknow Character";
    while (*p != '\0') {
        if (*p == '%') {
            p++;
            // getting what is comping after %
            char *afterChrcs = (char *) malloc(sizeof(char));
            int i = 0;
            while (*p != 'd' && *p != 's' && *p != 'c') {
                afterChrcs[i] = *p; i++; p++;
            }
            // test cases
            switch(*p) {
                case 'd': {
                    char buffer[20];
                    int *param = va_arg(args, int *);
                    read(1, buffer, sizeof(buffer - 1));
                    *param = atoi(buffer);
                    break;
                }
                case 's': {
                    printf("%c", *p);
                    break;
                }
                case 'f': {
                    char buffer[20];
                    float *param = va_arg(args, float *);
                    read(1, buffer, sizeof(buffer - 1));
                    *param = atof(buffer);
                    break;
                }
                default: {
                    printf("%s", message);
                }
            }
        } else {
            printf("%s", message);
        } 
        p++;
    }
    // char buf[20] = "kdkdkd";
    // read(1, buf, sizeof(buf));
    // write(0, buf, sizeof(buf));
    return '\n';
}



































