#include "printf.h"

int main() {
    int n = 73;
    float pi = -103.4932904;
    char c = 'A';
    char str[100] = "Information";
    _printf("Float : %.2f\nInteger : %d\nString : %s\nCharacter : %c\nHex : %x\n", pi, n, str, c, n);
    _printf("Integer : %.9d\n", n);
    _printf("Float : %.10f\n", pi);
    _printf("string = %.5s\n", str);
    return 0;
}




