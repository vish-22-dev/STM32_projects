#ifndef UART_H
#define UART_H
#include <stdint.h>

void init_uart(void);
char read_uart_char(void);
void write_uart_char (char ch);
void read_uart_string(char *buffer, uint32_t max_length);
void write_uart_string (char *str);

#endif