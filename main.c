#include "printf.h"
#include <stdio.h>

int main() {
    int n = -42;
    float pi = -103.494;
    char c = 'A';
    char str[100] = "Information";
    // _printf("Float : %.2f\nInteger : %d\nString : %s\nCharacter : %c\nHex : %x\n", pi, n, str, c, n);
    // _printf("Integer : %d\nFloat : %f\n", n, pi);
    _printf("Float : %f\n", pi);
    return 0;
}




