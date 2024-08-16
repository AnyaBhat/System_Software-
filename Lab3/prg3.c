#include <stdio.h>

int main() {
    // Variables of different types
    int integer = 42;
    float floating_point = 3.14159;
    double double_precision = 2.71826345732;
    char character = 'A';
    char string[] = "Hello, World!";
    unsigned int unsigned_integer = 1234567890;

 
    printf("Integer (d): %d\n", integer);        
    printf("Unsigned Integer (u): %u\n", unsigned_integer); 
    printf("Hexadecimal (x): %x\n", integer);   
    printf("Hexadecimal (X): %X\n", integer);  
    
   
    printf("Float (f): %.2f\n", floating_point);
    printf("Double (lf): %.5lf\n", double_precision); 
    
    // Printing character and string values
    printf("Character (c): %c\n", character);   
    printf("String (s): %s\n", string);         

    // Printing with different formats and width specifiers
    printf("Integer with width (10): %10d\n", integer); // Right-align within 10 spaces
    printf("Integer with width and leading zeros (010): %010d\n", integer); // Right-align with leading zeros
    printf("Float with width (10) and precision (2): %10.2f\n", floating_point); // Width 10, precision 2
    
    // Printing address
    printf("Address of integer: %p\n", (void*)&integer); // Print memory address of integer

    return 0;
}

