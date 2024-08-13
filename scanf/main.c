#include <stdio.h>
#include "scanf.h"


int main() {
    
    // start a simple test
    // scanf("%", str);
    // printf("%s", str);
    
    char str[20];
    int n = 10;
    float f = 100.48;
    char c = 's';
    _scanf("%d %f %c %s", &n, &f, &c, str);
    printf("\nn = %d\nf = %f\nstr = %s\ncharacter = %c", n, f, str, c);
    
    
    
    return 0;
}




