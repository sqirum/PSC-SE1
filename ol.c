#include <stdio.h>

typedef union {
    struct {
        unsigned int m: 23;
        unsigned int e: 8;
        unsigned int s: 1;
    };
    float f;
} Float_BF;

size_t int_to_string(int value, int base, char buffer[], size_t buffer_size) {
    if ((base != 2 && base != 8 && base != 10 && base != 16) || buffer_size == 0) {
        return 0;
    }

    const int int_max_bits = 32;
    const int terminator = 1;
    const char *prefix = "";
    char digits[] = "0123456789abcdef";
    char temp_arr[33]; // int_max_bits + terminator => não funciona colocar o size como variável?
    int idx = 0;
    int prefix_len = 0;
    unsigned int uvalue = (unsigned int)value;


    switch (base) {
        case 2: 
            prefix = "0b"; 
            prefix_len = 2; 
            break;
        case 8: 
            prefix = "0"; 
            prefix_len = 1; 
            break;
        case 16: 
            prefix = "0x"; 
            prefix_len = 2; 
            break;
    }

    do {
        temp_arr[idx++] = digits[uvalue % base];
        uvalue /= base;
    } while (uvalue > 0 && idx < int_max_bits);

    int total_len = idx + prefix_len + terminator;

    if (total_len > buffer_size) {
        return 0;
    }

    // Prefixos
    int buffer_idx = 0;
    for (int i = 0; i < prefix_len; i++) {
        buffer[buffer_idx++] = prefix[i];
    }

    // Numeros
    for (int i = idx; i > 0; i--) {
        buffer[buffer_idx++] = temp_arr[i - 1];
    }

    // Terminador
    buffer[buffer_idx] = '\0';

    return buffer_idx;
}

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    if (buffer_size < 8) return 0;  // Precisamos de espaço para pelo menos "-x.yyyy\0"

    Float_BF bf;
    bf.f = value;
    
    int sign = bf.s;
    int exp = bf.e - 127;
    unsigned int mantissa = bf.m;
    
    unsigned int pos = 0;
    
    if (sign) {
        buffer[pos++] = '-';
    }
    
    // Adicionar bit implícito à mantissa
    long long value_int = (1LL << 23) | mantissa;
    
    value_int >>= 6; // shift 6 casas decimais
    
    // Ajustar baseado no expoente
    if (exp > 0) {
        if (exp <= 24) {  // Prevenir overflow
            value_int <<= exp;
        } else {
            return 0;  // Número muito grande para representar
        }
    } else if (exp < 0) {
        exp = -exp;
        if (exp <= 24) {  // Prevenir underflow
            value_int >>= exp;
        } else {
            value_int = 0;
        }
    }
    
    // Dividir em parte inteira e fracionária
    int integer_part = (int)(value_int >> 29);
    long long fractional_part = value_int & ((1LL << 29) - 1);
    
    // Converter parte inteira usando int_to_string
    char int_buffer[20];
    size_t int_len = int_to_string(integer_part, 10, int_buffer, sizeof(int_buffer));
    if (int_len == 0) return 0;
    
    // Copiar parte inteira para o buffer principal
    for (size_t i = 0; i < int_len; i++) {
        if (pos >= buffer_size - 8) return 0;  // Verificar se há espaço suficiente
        buffer[pos++] = int_buffer[i];
    }
    
    // Adicionar ponto decimal
    if (pos >= buffer_size - 7) return 0;
    buffer[pos++] = '.';
    
    // Converter parte fracionária
    // Multiplicar por 10^6 e dividir por 2^29
    fractional_part *= 1000000LL;
    fractional_part >>= 29;
    
    // Converter a parte fracionária para string
    char frac_buffer[7];
    int frac_value = (int)fractional_part;
    
    // Garantir 6 dígitos com zeros à esquerda
    int zeros = 6;
    int temp = frac_value;
    while (temp > 0) {
        temp /= 10;
        zeros--;
    }
    
    // Adicionar zeros à esquerda
    for (int i = 0; i < zeros; i++) {
        if (pos >= buffer_size - 1) return 0;
        buffer[pos++] = '0';
    }
    
    if (frac_value > 0) {
        size_t frac_len = int_to_string(frac_value, 10, frac_buffer, sizeof(frac_buffer));
        for (size_t i = 0; i < frac_len && pos < buffer_size - 1; i++) {
            buffer[pos++] = frac_buffer[i];
        }
    }
    
    // Adicionar terminador nulo
    if (pos >= buffer_size) return 0;
    buffer[pos] = '\0';
    
    return pos;
}