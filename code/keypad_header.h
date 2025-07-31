#include<lpc17xx.h>
#define p2 LPC_GPIO2

extern char entered_password[5];  // Declare extern variable for sharing

char get_keypad_key(void);
void get_password(void);


