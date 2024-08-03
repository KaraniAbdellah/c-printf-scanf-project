#include "printf.h"
#include <stdio.h>

int main() {
    int n = 42;
    float pi = 103.494;
    char c = 'A';
    char str[100] = "Information";
    _printf("Float : %f\nInteger : %.4d\nString : %.3s\nCharacter : %c\nAdreesse : %p", pi, n, str, c, &n);
    printf("\n%.100s and %.90f\n", str, pi);
    
    
    return 0;
}




