#include <stdio.h>
#include <stdarg.h>

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...) {
    va_list ap;
    const char *p;
    unsigned int count = 0;
    char *str;
    int i, ival;
    unsigned int uval;
    double dval;
    char num_buffer[32];
    
    // Verificar parâmetros de entrada
    if (buffer == NULL || format == NULL || buffer_size == 0)
        return 0;
    
    va_start(ap, format);
    
    for (p = format; *p && count < buffer_size - 1; p++) {
        if (*p != '%') {
            buffer[count++] = *p;
            continue;
        }
        
        p++; // Avançar além do '%'
        
        switch (*p) {
            case 'c':
                buffer[count++] = (char)va_arg(ap, int);
                break;
                
            case 's':
                str = va_arg(ap, char*);
                while (*str && count < buffer_size - 1)
                    buffer[count++] = *str++;
                break;
                
            case 'd':
                ival = va_arg(ap, int);
                if (ival < 0) {
                    buffer[count++] = '-';
                    ival = -ival;
                }
                i = 0;
                do {
                    num_buffer[i++] = ival % 10 + '0';
                    ival /= 10;
                } while (ival > 0 && i < 31);
                while (--i >= 0 && count < buffer_size - 1)
                    buffer[count++] = num_buffer[i];
                break;
                
            case 'x':
                uval = va_arg(ap, unsigned int);
                i = 0;
                do {
                    int digit = uval % 16;
                    num_buffer[i++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
                    uval /= 16;
                } while (uval > 0 && i < 31);
                while (--i >= 0 && count < buffer_size - 1)
                    buffer[count++] = num_buffer[i];
                break;
                
            case 'f':
                dval = va_arg(ap, double);
                if (dval < 0) {
                    buffer[count++] = '-';
                    dval = -dval;
                }
                ival = (int)dval;
                i = 0;
                do {
                    num_buffer[i++] = ival % 10 + '0';
                    ival /= 10;
                } while (ival > 0 && i < 31);
                while (--i >= 0 && count < buffer_size - 1)
                    buffer[count++] = num_buffer[i];
                
                if (count < buffer_size - 1) {
                    buffer[count++] = '.';
                    dval -= (int)dval;
                    for (i = 0; i < 6 && count < buffer_size - 1; i++) {
                        dval *= 10;
                        int digit = (int)dval;
                        buffer[count++] = digit + '0';
                        dval -= digit;
                    }
                }
                break;
                
            default:
                buffer[count++] = *p;
                break;
        }
    }
    
    va_end(ap);
    
    if (count < buffer_size)
        buffer[count] = '\0';
    else {
        buffer[buffer_size - 1] = '\0';
        return 0;  // Buffer não foi suficiente
    }
    
    return count;
}