#include "printf.h"
#include <stdio.h>

int main() {
    
    int n = 42;
    float pi = 103.494;
    char c = 'A';
    char str[100] = "Information";
    _printf("The value of pi is approximately %f and %.9f\n and the answer is %d\n which is a great number for '%c'\n%s\n", 
    pi, pi, n, c, str);
    return 0;
}




