#include "printf.h"

int main() {
    
    int d = 1234567890;
    float f = 90.03;
    char c = 'd';
    char str[20] = "MOM!!";
    long int ld = 10220303;
    _printf("We Have Just %d, \
        \nLetter Is %c, \
        \nFloat Number Is %f, \
        \nString Is %s, \
        \nAnd Last is %ld \n", 
        d, c, f, str, ld);
    
    
    return 0;
}




