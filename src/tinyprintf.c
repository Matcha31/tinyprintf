#include "tinyprintf.h"

int my_str_len(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void reverse(char s[], int len)
{
    int start = 0;
    int end = len - 1;
    while (start < end)
    {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        end--;
        start++;
    }
}

char *my_itoa_base(unsigned n, char *s, const char *base)
{
    int b = my_str_len(base);
    int i = 0;
    if (n == 0)
    {
        *(s + i) = base[0];
        i++;
        *(s + i) = '\0';
        return s;
    }
    while (n != 0)
    {
        *(s + i) = base[n % b];
        n = n / b;
        i++;
    }
    *(s + i) = '\0';
    reverse(s, i);
    return s;
}

void x_case(va_list ap, int *n)
{
    char str[256];
    my_itoa_base(va_arg(ap, int), str, "0123456789abcdef");
    int j = my_str_len(str);
    for (int k = 0; k < j; k++)
    {
        putchar(str[k]);
        (*n)++;
    }
}

void s_case(va_list ap, int *n)
{
    char *str = va_arg(ap, char *);
    if (str == NULL)
    {
        putchar('(');
        putchar('n');
        putchar('u');
        putchar('l');
        putchar('l');
        putchar(')');
        *n += 6;
    }
    else
    {
        int j = my_str_len(str);
        for (int k = 0; k < j; k++)
        {
            putchar(str[k]);
            (*n)++;
        }
    }
}

void o_case(va_list ap, int *n)
{
    char str[256];
    my_itoa_base(va_arg(ap, int), str, "01234567");
    int j = my_str_len(str);
    for (int k = 0; k < j; k++)
    {
        putchar(str[k]);
        (*n)++;
    }
}

void u_case(va_list ap, int *n)
{
    char str[256];
    my_itoa_base(va_arg(ap, int), str, "0123456789");
    int j = my_str_len(str);
    for (int k = 0; k < j; k++)
    {
        putchar(str[k]);
        (*n)++;
    }
}

void d_case(va_list ap, int *n)
{
    char str[256];
    int a = va_arg(ap, int);
    if (a < 0)
    {
        putchar('-');
        (*n)++;
        my_itoa_base(-a, str, "0123456789");
    }
    else
        my_itoa_base(a, str, "0123456789");
    int j = my_str_len(str);
    for (int k = 0; k < j; k++)
    {
        putchar(str[k]);
        (*n)++;
    }
}

void percent(char c, va_list ap, int *n)
{
    if (c == '%')
    {
        putchar('%');
        (*n)++;
    }
    else if (c == 'c')
    {
        char a = va_arg(ap, int);
        putchar(a);
        (*n)++;
    }
    else if (c == 'd')
        d_case(ap, n);
    else if (c == 'u')
        u_case(ap, n);
    else if (c == 'o')
        o_case(ap, n);
    else if (c == 'x')
        x_case(ap, n);
    else if (c == 's')
        s_case(ap, n);
    else
    {
        putchar('%');
        putchar(c);
        (*n) += 2;
    }
}

int tinyprintf(const char *format, ...)
{
    if (format == NULL)
        return 0;
    int len = my_str_len(format);
    va_list ap;
    va_start(ap, format);
    int n = 0;
    int i = 0;
    while (i < len)
    {
        if (format[i] == '%')
        {
            percent(format[i + 1], ap, &n);
            i += 2;
        }
        else
        {
            putchar(format[i]);
            n++;
            i++;
        }
    }
    va_end(ap);
    return n;
}
