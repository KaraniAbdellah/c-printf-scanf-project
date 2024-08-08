#include <stdbool.h>
#ifndef _PRINTF
#define _PRINTF


    void _printf(char *str, ...);
    void _print_d(int n, bool check, char *str_nbr); // print an integer
    void _print_c(char c, bool check, char *str_nbr); // print a character
    void _print_f(float f, bool check, char *str_nbr); // print a float number
    void _printf_s(char *str, bool check, char *str_nbr); // print string


#endif


