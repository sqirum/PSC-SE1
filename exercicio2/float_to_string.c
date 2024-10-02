#include <stdio.h>

typedef union {
    struct {
        unsigned int m: 23;
        unsigned int e: 8;
        unsigned int s: 1;
    };
    float f;
} Float_BF;

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size);

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    if (buffer_size < 8) return 0;

    Float_BF bf;
    bf.f = value;
    
    int sign = bf.s;
    int exp = bf.e - 127;
    unsigned int mantissa = bf.m;
    unsigned int pos = 0;
    unsigned int len = 0;

    long int normalized_value = ((long) 1 << 23) | mantissa; // 1,xxxxxxxxxxxxx 

    if (sign) {
        buffer[pos++] = '-';
    }

    int int_float; 
    if(exp >= 0) {
        int_float = normalized_value >> (23 - exp); // isolar parte inteira se expoente 0 ou positivo
    } else {
        int_float = 0; // parte inteira caso expoente negativo
    }
    
    long frac = normalized_value & (1 << (23 - exp) - 1); // extrair parte fracionária

    
    char int_buffer[33];
    len += int_to_string(int_float, 10, int_buffer, sizeof(int_buffer));
    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {  
        buffer[pos++] = int_buffer[i]; // Copiar parte inteira para o buffer principal
    }

    buffer[pos++] = '.';

    long long new_int_float = frac * 1000000; // obter 6 casas decimais
    new_int_float = new_int_float >> (23 - exp); // isolar parte inteira


    
    

    printf("new_int_float=%lld\n", new_int_float);


    // Test Buffer
    printf("\nArray: [");
    for (int i = 0; i < pos; i++) {
        printf("%c", buffer[i]);
        if (i < pos - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    /*


    char frac_buffer[7];




    printf("buffer_size=%d\n", buffer_size);

    if (int_float > 0) {
        printf("int_float=%d\n", int_float);
        printf("len=%d\n", len);
        len += int_to_string(int_float,10,  buffer, buffer_size);
        printf("afterleng=%d\n", len);
    }

    

    if (new_int_float > 0) {
        printf("new_int_float=%d\n", new_int_float);
        printf("new_int_len=%d\n", len);
        len += int_to_string(new_int_float,10,  buffer, buffer_size) - 1;
    }
    */




    // int size = sizeof(buffer) / sizeof(buffer[0]);
    // size_t int_len = int_to_string(normalized_value, 10, buffer, size);
    // if (int_len == 0) return 0;

    // printf("normalized value=%d\n", normalized_value);
    // printf("leng=%d\n", int_len);
    
    
    return pos;
}