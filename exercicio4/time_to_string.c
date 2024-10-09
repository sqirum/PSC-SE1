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

    const int min_buffer_size = 35;
    if (buffer_size < min_buffer_size) {
        return 0;
    }

    if (tm->tm_wday < 0 || tm->tm_wday > 6) {
        return mini_snprintf(buffer, buffer_size,
            "domingo, 00-01-1900, 00:00:00");
    }

    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;

    char day[3], mon[3], hour[3], min[3], sec[3], year_str[5];
    
    // Converter cada número para string com zero à esquerda
    mini_snprintf(day, sizeof(day), "%d%d", tm->tm_mday / 10, tm->tm_mday % 10);
    mini_snprintf(mon, sizeof(mon), "%d%d", month / 10, month % 10);
    mini_snprintf(hour, sizeof(hour), "%d%d", tm->tm_hour / 10, tm->tm_hour % 10);
    mini_snprintf(min, sizeof(min), "%d%d", tm->tm_min / 10, tm->tm_min % 10);
    mini_snprintf(sec, sizeof(sec), "%d%d", tm->tm_sec / 10, tm->tm_sec % 10);
    mini_snprintf(year_str, sizeof(year_str), "%d%d%d%d", 
        year / 1000, (year / 100) % 10, (year / 10) % 10, year % 10);

    return mini_snprintf(buffer, buffer_size,
        "%s, %s-%s-%s, %s:%s:%s",
        weekDays[tm->tm_wday],
        day, mon, year_str,
        hour, min, sec);
}