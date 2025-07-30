# Smart Door Lock System with Intruder Alert using LPC1768 microcontroller

This is my first embedded systems project using the **LPC1768** microcontroller. It implements a secure, password-protected door lock system with an intruder alert feature.

## 🔐 Project Overview

- **Microcontroller**: LPC1768 (ARM Cortex-M3)
- **Input**: 4x4 Keypad
- **Output**: 16x2 LCD, Servo Motor, Buzzer
- **Sensors**: IR Sensor for presence detection
- **Security**: Access is granted on correct password. After 3 wrong attempts, buzzer alert is triggered and access is blocked.

## 📄 Files Included

- `main.c` – Main program logic
- `keypad_fun.c` – Keypad handling functions
- `lcd_fun.c` – LCD display functions
- `lcd_header.h` – LCD header file
- `smart_door_lock.pptx` – Project presentation
- `Project_Report.pdf` – Detailed project documentation

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
