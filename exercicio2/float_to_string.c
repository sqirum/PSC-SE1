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

    unsigned int len = 0;

    int normalized_value = (1 << 23) | mantissa; // 1,xxxxxxxxxxxxx 
    int int_float; 
    if(exp >= 0) {
        int_float = normalized_value >> (23 - exp); // isolar parte inteira se expoente 0 ou positivo
    } else {
        int_float = 0; // parte inteira caso expoente negativo
    }
    
    long frac = normalized_value & (1 << (23 - exp) - 1); // extrair parte fracionária

    long new_int_float = frac * 1000000; // obter 6 casas decimais

    new_int_float = new_int_float >> (23 - exp); // isolar parte inteira

    





    if (sign) {
        buffer[len++] = '-';
    }

    int size = sizeof(buffer) / sizeof(buffer[0]);
    size_t int_len = int_to_string(normalized_value, 10, buffer, size);
    if (int_len == 0) return 0;

    printf("normalized value=%d\n", normalized_value);
    printf("leng=%d\n", int_len);
    
    
    return 0;
}