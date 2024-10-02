#include <stdio.h>

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

    // Check Values
    for(int i = 0; i < buffer_idx; i++) {
        printf("%c\n", buffer[i]);
    }

    return buffer_idx;
}