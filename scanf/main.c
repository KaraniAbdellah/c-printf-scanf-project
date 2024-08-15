#include <stdio.h>
#include "scanf.h"


int main() {
    
    // start a simple test
    // scanf("%", str);
    // printf("%s", str);
    
    char str1[40], str2[40];
    int n = 10;
    float f = 100.48;
    char c = 's';
    _scanf("%1s %d %f %c", str1, &n, &f, &c);
    // scanf("%s", str1);
    printf("\nn = %d\nf = %f\nstr1 = %s\ncharacter = %c\nstr2 = %s", n, f, str1, c, str2);
    
    
    
    // wrong test cases
    // _scanf("%[^\n]", str);
    // scanf("%[^\n]", str);
    

    
    
    return 0;
}




