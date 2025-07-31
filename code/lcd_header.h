#include<lpc17xx.h>
#include <stdint.h>

#define RS (1 << 10)
#define EN (1 << 11)
#define LCD_DATA (0xFF << 15)

void delay(uint16_t d);
void enable_fun(void);
void lcd_cmd(uint8_t cmd);
void lcd_char(uint8_t data);
void lcd_str(char *s);
void lcd_init(void);

