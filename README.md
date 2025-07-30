# Smart Door Lock System with Intruder Alert using the LPC1768 microcontroller

This is my first embedded systems project using the **LPC1768** microcontroller. It implements a secure, password-protected door lock system with an intruder alert feature.

## 🔐 Project Overview

- **Microcontroller**: LPC1768 (ARM Cortex-M3)
- **Input**: 4x4 Keypad
- **Output**: 16x2 LCD, Servo Motor, Buzzer
- **Sensors**: IR Sensor for presence detection
- **Security Logic**:
The system uses a 4-digit password for secure access.

The user has a maximum of 3 attempts to enter the correct password.

On each wrong attempt, the buzzer alerts as follows:

1st wrong attempt → 🔊 Buzzer beeps once

2nd wrong attempt → 🔊 Buzzer beeps twice

3rd wrong attempt → 🔊 Buzzer beeps three times, then:

A long continuous beep is triggered

LCD displays "Access Blocked!" and "TRY LATER.."

System is locked using while(1); (halts operations)

## 📄 Files Included

- `main.c` – Main program logic
- `keypad_fun.c` – Keypad handling functions
- `keypad_header.h` – Keypad function declarations
- `lcd_fun.c` – LCD display functions
- `lcd_header.h` – LCD function declarations


## 🛠️ Development & Programming Tools

- **IDE Used**: Keil uVision5  
  Used for writing, compiling, and building the embedded C code for LPC1768.

- **Programming Tool**: Flash Magic  
  Used to upload the generated `.hex` file to the LPC1768 microcontroller via serial interface.

- **Microcontroller**: LPC1768 (ARM Cortex-M3)

> 💡 After compiling the code in Keil, the `.hex` file is found in the `Objects/` folder and is uploaded to the LPC1768 board using **Flash Magic** via USB-to-Serial interface.

## 🎯 Features

- Secure 4-digit password entry
- LCD status display (Access Granted / Denied)
- Buzzer alert after 3 incorrect attempts
- Servo motor to unlock/lock door
- IR sensor to detect nearby user

## 📚 Applications

- Smart home or office entry systems
- Labs, hostels, and secure areas
- Password-protected lockers

## 🙋‍♂️ Author

**Reddi Udaya Ram**  
Student Project – Embedded Systems

---

> 🎓 This is my first GitHub project upload. Feedback and suggestions are welcome!
