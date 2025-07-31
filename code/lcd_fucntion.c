#include "lcd_header.h"
#include <lpc17xx.h>

#define p0 LPC_GPIO0

void delay(uint16_t d) {
    uint16_t i, j;
    for (i = 0; i < d; i++)
        for (j = 0; j < 100; j++);
}

void enable_fun() {
    p0->FIOSET = EN;
    delay(10);
    p0->FIOCLR = EN;
    delay(10);
}

void lcd_cmd(uint8_t cmd) {
    p0->FIOCLR = RS;
    p0->FIOCLR = LCD_DATA;
    p0->FIOSET = (cmd << 15);
    enable_fun();
}

void lcd_char(uint8_t data) {
    p0->FIOSET = RS;
    p0->FIOCLR = LCD_DATA;
    p0->FIOSET = (data << 15);
    enable_fun();
}

void lcd_str(char *s) {
    while (*s != '\0') {
        lcd_char(*s++);
        delay(300);
    }
}

void lcd_init() {
    p0->FIODIR = (RS | EN | LCD_DATA);
    lcd_cmd(0x38);
    lcd_cmd(0x0E);
    lcd_cmd(0x01);
}
