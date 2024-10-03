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
    
    if (buffer == NULL || format == NULL || buffer_size == 0)
        return 0;
    
    va_start(ap, format);
    
    for (p = format; *p; p++) {
        if (*p != '%') {
            if (count < buffer_size - 1)
                buffer[count] = *p;
            count++;
            continue;
        }
        
        p++;
        
        switch (*p) {
            case 'c':
                if (count < buffer_size - 1)
                    buffer[count] = (char)va_arg(ap, int);
                count++;
                break;
                
            case 's':
                str = va_arg(ap, char*);
                if (str != NULL) {
                    while (*str) {
                        if (count < buffer_size - 1)
                            buffer[count] = *str;
                        count++;
                        str++;
                    }
                }
                break;
                
            case 'd':
                ival = va_arg(ap, int);
                if (ival < 0) {
                    if (count < buffer_size - 1)
                        buffer[count] = '-';
                    count++;
                    ival = -ival;
                }
                i = 0;
                do {
                    num_buffer[i++] = ival % 10 + '0';
                    ival /= 10;
                } while (ival > 0 && i < 31);
                while (--i >= 0) {
                    if (count < buffer_size - 1)
                        buffer[count] = num_buffer[i];
                    count++;
                }
                break;
                
            case 'x':
                // Adicionar prefixo "0x"
                if (count < buffer_size - 1)
                    buffer[count] = '0';
                count++;
                if (count < buffer_size - 1)
                    buffer[count] = 'x';
                count++;
                
                uval = va_arg(ap, unsigned int);
                i = 0;
                if (uval == 0) {
                    if (count < buffer_size - 1)
                        buffer[count] = '0';
                    count++;
                } else {
                    do {
                        int digit = uval % 16;
                        num_buffer[i++] = digit < 10 ? digit + '0' : digit - 10 + 'a';
                        uval /= 16;
                    } while (uval > 0 && i < 31);
                    
                    while (--i >= 0) {
                        if (count < buffer_size - 1)
                            buffer[count] = num_buffer[i];
                        count++;
                    }
                }
                break;
                
            case 'f':
                dval = va_arg(ap, double);
                if (dval < 0) {
                    if (count < buffer_size - 1)
                        buffer[count] = '-';
                    count++;
                    dval = -dval;
                }
                ival = (int)dval;
                i = 0;
                do {
                    num_buffer[i++] = ival % 10 + '0';
                    ival /= 10;
                } while (ival > 0 && i < 31);
                while (--i >= 0) {
                    if (count < buffer_size - 1)
                        buffer[count] = num_buffer[i];
                    count++;
                }
                
                if (count < buffer_size - 1)
                    buffer[count] = '.';
                count++;
                dval -= (int)dval;
                for (i = 0; i < 6; i++) {
                    dval *= 10;
                    int digit = (int)dval;
                    if (count < buffer_size - 1)
                        buffer[count] = digit + '0';
                    count++;
                    dval -= digit;
                }
                break;
                
            default:
                if (count < buffer_size - 1)
                    buffer[count] = *p;
                count++;
                break;
        }
    }
    
    va_end(ap);
    
    if (count < buffer_size)
        buffer[count] = '\0';
    else if (buffer_size > 0)
        buffer[buffer_size - 1] = '\0';
    
    return count;
}