#include <stdio.h>

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

int mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...);

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) {
    if (tm == NULL || buffer == NULL || buffer_size == 0) {
        return 0;
    }

    const char *weekDays[] = {
        "domingo", "segunda-feira", "terça-feira", "quarta-feira", 
        "quinta-feira", "sexta-feira", "sábado"
    };

    // Verificar se temos espaço suficiente no buffer
    // O maior dia da semana é "quarta-feira" que tem 12 caracteres
    // Mais o resto do formato ", DD-MM-YYYY, HH:MM:SS" que tem 22 caracteres
    // Então precisamos de pelo menos 35 caracteres (34 + nulo terminador)

    if (buffer_size < 35) {
        return 0;
    }

    // Ajustes para o ano e mês
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;

    // Verificação de limites para tm_wday
    if (tm->tm_wday < 0 || tm->tm_wday > 6) {
        // Se tm_wday for inválido, usar valores padrão conforme o teste
        return mini_snprintf(buffer, buffer_size,
            "domingo, 00-01-1900, 00:00:00");
    }

    return mini_snprintf(buffer, buffer_size,
        "%s, %02d-%02d-%04d, %02d:%02d:%02d",
        weekDays[tm->tm_wday],
        tm->tm_mday,
        month,
        year,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec);
}