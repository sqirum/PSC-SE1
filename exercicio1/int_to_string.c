#include <stdio.h>

// int int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {
//     if (base != 2 && base != 8 && base != 10 && base != 16) {
//         return 0;
//     }

//     char *prefix = "";

//     switch (base) {
//         case 2: prefix = "0b";
//         break;
//         case 8: prefix = "0o";
//         break;
//         case 16: prefix = "0x";
//         break;
//     }

//     while (value > 0) {
//         int remainder = value % base;
//         int value = value / base;
//         printf("remainder = %d\n", remainder);
//         printf("value= = %d\n", value);
//     }
// }


size_t int_to_string(int value, int base, char buffer[], size_t buffer_size) {
    if ((base != 2 && base != 8 && base != 10 && base != 16) || buffer_size == 0) {
        return 0;
    }

    const int int_max_bits = 32;
    const int terminator = 1;
    const int total_bits = int_max_bits + terminator;
    const char *prefix = "";
    char digits[] = "0123456789abcdef";
    char tempArr[total_bits];
    size_t idx = 0;
    size_t prefix_len = 0;
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
        tempArr[idx++] = digits[uvalue % base];
        uvalue /= base;
    } while (uvalue > 0 && idx < int_max_bits);

    // Calcular o tamanho total necessário
    size_t total_len = idx + prefix_len + terminator;  // +1 para o terminador nulo

    // Verificar se o buffer é grande o suficiente
    if (total_len > buffer_size) {
        return 0;
    }

    // Copiar o prefixo
    size_t buffer_idx = 0;
    for (size_t i = 0; i < prefix_len; i++) {
        buffer[buffer_idx++] = prefix[i];
    }

    // Copiar os dígitos em ordem reversa
    for (size_t i = idx; i > 0; i--) {
        buffer[buffer_idx++] = tempArr[i - 1];
    }

    // Adicionar o terminador nulo
    buffer[buffer_idx] = '\0';

    return buffer_idx;  // Retorna o tamanho da string produzida (sem contar o terminador nulo)
}