#include <lpc17xx.h>
#include <stdint.h>
#include "lcd_header.h"
#include "keypad_header.h"

#define BUZZER_PIN   (1 << 27)  // Buzzer connected to P1.27
#define IR_SENSOR_PIN (1 << 9)  // IR sensor connected to P0.9

char correct_password[] = "4444";
char entered_password[5];
uint8_t attempts = 0;

int i;

// ------------------- Servo PWM initialization -------------------
void servo_pwm_init(void) {
    LPC_PINCON->PINSEL3 |= (1 << 9);      // Set P1.20 as PWM1.2
    LPC_SC->PCONP |= (1 << 6);            // Power up PWM1
    LPC_PWM1->PR = 0;                     // Set prescaler to 0
    LPC_PWM1->MR0 = 20000;                // Set period to 20ms (50Hz)
    LPC_PWM1->MR2 = 1500;                 // Initial position (approx. 90 degrees)
    LPC_PWM1->MCR = (1 << 1);             // Reset on MR0 match
    LPC_PWM1->LER = (1 << 0) | (1 << 2); // Load MR0 and MR2 values
    LPC_PWM1->PCR = (1 << 10);            // Enable PWM1.2 output
    LPC_PWM1->TCR = (1 << 0) | (1 << 3); // Enable counter and PWM
}

// ------------------- Rotate servo to specified angle -------------------
void servo_rotate(uint16_t pulse_width_us) {
    int j;
    LPC_PWM1->MR2 = pulse_width_us;       // Update pulse width
    LPC_PWM1->LER |= (1 << 2);            // Load new value into PWM1

    for (j = 0; j < 50; j++) {
        delay(20); // Wait to allow servo movement
    }
}

// ------------------- Door motor operation -------------------
void motor_open(void) {
    lcd_cmd(0x01);         // Clear LCD
    servo_rotate(500);     // Rotate servo to close
    delay(2000);           // Wait

    lcd_cmd(0x01);
    lcd_str("Door Opening...");
    
    servo_rotate(1400);    // Rotate servo to open
    delay(500);

    lcd_cmd(0x01);
    lcd_str("Door Closed");
    delay(500);
}

// ------------------- Buzzer alert -------------------
void buzzer_alert(uint8_t count) {
    if (count < 4) {
        for (i = 0; i < count; i++) {
            LPC_GPIO1->FIOSET = BUZZER_PIN;  // Turn ON buzzer
            delay(1000);
            LPC_GPIO1->FIOCLR = BUZZER_PIN;  // Turn OFF buzzer
            delay(500);
        }
    } else {
        LPC_GPIO1->FIOSET = BUZZER_PIN;      // Continuous buzzer for block
        delay(8000);
        LPC_GPIO1->FIOCLR = BUZZER_PIN;
    }
}

// ------------------- Compare passwords -------------------
int compare_passwords(char *a, char *b) {
    for (i = 0; i < 4; i++) {
        if (a[i] != b[i]) {
            return 0; // Password mismatch
        }
    }
    return 1; // Passwords match
}

// ------------------- Main function -------------------
int main(void) {
    lcd_init();              // Initialize LCD
    servo_pwm_init();        // Initialize servo PWM

    LPC_GPIO1->FIODIR |= BUZZER_PIN;  // Set buzzer pin as output
    LPC_GPIO1->FIOCLR = BUZZER_PIN;   // Turn off buzzer

    LPC_GPIO0->FIODIR &= ~IR_SENSOR_PIN;  // Set IR sensor as input

    lcd_str("Door Lock System");
    delay(4000);
    lcd_cmd(0x01);
    lcd_str("WELCOME");
    delay(3000);
    lcd_cmd(0x01);

    while (1) {
        // Wait for IR sensor detection
        lcd_cmd(0x01);
        lcd_str("Waiting for");
        lcd_cmd(0xC0);
        lcd_str("person...");
        
        // Wait while sensor pin is high (no person)
        while ((LPC_GPIO0->FIOPIN & IR_SENSOR_PIN));

        lcd_cmd(0x01);
        lcd_str("Person Detected");
        delay(3000);
        lcd_cmd(0x01);

        // Allow up to 3 password attempts
        while (attempts < 3) {
            if (attempts > 0) {
                lcd_cmd(0x01);
                lcd_str("Attempt ");
                lcd_char('1' + attempts);
                delay(2000);
                lcd_cmd(0x01);
            }

            get_password();  // Get password from keypad

            if (compare_passwords(correct_password, entered_password)) {
                lcd_cmd(0x01);
                lcd_str("Access Granted");
                lcd_cmd(0xC0);
                lcd_str("WELCOME HOME");
                delay(3000);

                motor_open();     // Open door
                attempts = 0;     // Reset attempts for next user
                break;            // Return to IR detection loop
            } else {
                lcd_cmd(0x01);
                lcd_str("Wrong Password");
                delay(2000);

                if (attempts == 2) {
                    buzzer_alert(3); // 3 short buzzes for last attempt
                    lcd_cmd(0x01);
                    lcd_str("Access Blocked!");
                    lcd_cmd(0xC0);
                    lcd_str("TRY LATER..");
                    delay(4000);
                    buzzer_alert(4); // Long buzzer alert
                    while (1);       // Lock system indefinitely
                } else {
                    buzzer_alert(attempts + 1);
                    attempts++;
                }
            }
        }
    }
}
