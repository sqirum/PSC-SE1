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
    
    long long frac = normalized_value & ((1 << (23 - exp)) - 1); // extrair parte fracionária


    unsigned int len = int_to_string(int_float, 10, buffer + pos, buffer_size - pos);
    if (len == 0) return 0;
    pos += len;


    if (pos < buffer_size - 1) {
        buffer[pos++] = '.';
    } else {
        return 0; // pequeno para adicionar o ponto decimal
    }

    long long frac_part = (frac * 1000000LL) >> (23 - exp); // 6 casas decimais + obter parte fracional


    len = int_to_string(frac_part, 10, buffer + pos, buffer_size - pos);
    if (len == 0) return 0;
    pos += len;


    while (len < 6 && pos < buffer_size - 1) {
        buffer[pos++] = '0';
        len++;
    }

    
    if (pos < buffer_size) {
        buffer[pos] = '\0'; // Terminador
    } else {
        return 0; // buffer pequeno
    }

    /**
     * ! Teste
    printf("\nArray Float: [");
    for (size_t i = 0; i < pos; i++) {
        printf("%c", buffer[i]);
        if (i < pos - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    */

    return pos;
}