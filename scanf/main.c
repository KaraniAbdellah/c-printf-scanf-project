#include <stdio.h>
#include "scanf.h"


int main() {
    char str1[40], str2[40];
    int n = 10;
    float f = 100.48;
    char c = 's';
    _scanf("%[^/n]2s", &str1);
    printf("\nn = %d || f = %f || str1 = %s || character = %c || str2 = %s\n", n, f, str1, c, str2);
    return 0;
}




