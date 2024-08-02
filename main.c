#include "printf.h"
#include <stdio.h>

int main() {
    
    int n = 42;
    float pi = 103.494;
    char c = 'A';
    char str[100] = "Information";
    _printf("Float : %.6f\nInteger : %d\nString : %s\nCharacter : %c\nAdreesse : %p", pi, n, str, c, &n);
    return 0;
}




