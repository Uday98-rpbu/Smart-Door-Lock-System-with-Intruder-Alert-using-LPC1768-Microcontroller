#include <lpc17xx.h>
#include "keypad_header.h"
#include "lcd_header.h"


char get_keypad_key() {
    uint8_t key;
    p2->FIODIR = 0xF0;  // upper nibble output, lower input

    while (1) {
        p2->FIOPIN = 0x70;  // scan row 1
        key = p2->FIOPIN & 0xFF;
        switch (key) {
            case 0x77: return '@';
            case 0x7B: return '%';
            case 0x7D: return '/';
            case 0x7E: return '0';
        }

        p2->FIOPIN = 0xB0;  // scan row 2
        key = p2->FIOPIN & 0xFF;
        switch (key) {
            case 0xB7: return '*';
            case 0xBB: return '9';
            case 0xBD: return '8';
            case 0xBE: return '7';
        }

        p2->FIOPIN = 0xD0;  // scan row 3
        key = p2->FIOPIN & 0xFF;
        switch (key) {
            case 0xD7: return '-';
            case 0xDB: return '6';
            case 0xDD: return '5';
            case 0xDE: return '4';
        }

        p2->FIOPIN = 0xE0;  // scan row 4
        key = p2->FIOPIN & 0xFF;
        switch (key) {
            case 0xE7: return '+';
            case 0xEB: return '3';
            case 0xED: return '2';
            case 0xEE: return '1';
        }
    }
}

void get_password() {
    int index = 0;
    char key;
    lcd_cmd(0x01);
    lcd_str("Enter Password:");
    lcd_cmd(0xC0);

    while (index < 4) {
        key = get_keypad_key();
        if (key >= '0' && key <= '9') {
            entered_password[index++] = key;
            lcd_char('*');
            delay(3000);
        }
    }
    entered_password[4] = '\0';
}
