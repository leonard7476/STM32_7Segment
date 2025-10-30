# STM32 7-Segment Display with Shift Register (SPI Interface)

This project drives a 4-digit 7-segment display using an STM32F0DISCOVERY microcontroller
and a 74HC595 shift register via the SPI interface.

## 🧠 Features
- Displays a 4-digit number using SPI communication.
- Increments/decrements the displayed number via pushbuttons (PA0 / PA1).
- Supports hardware-based multiplexing for smooth display refresh.
- Debounce logic included for reliable button input.

## ⚙️ Hardware Connections
| STM32 Pin | 74HC595 Pin | Description |
|------------|--------------|--------------|
| PA7 | SER | Serial data input |
| PA5 | SRCLK | Shift register clock |
| PA6 | RCLK | Latch clock |
| PC0–PC3 | Digit select lines | Control each of 4 digits |
| PA0 | Button 1 | Increment |
| PA1 | Button 2 | Decrement |

## 🧩 Files
- `main.c` – Initializes peripherals and runs the main loop.
- `SSEG.c` / `SSEG.h` – Handles display multiplexing and SPI communication.
- `CMakeLists.txt` – Build configuration for STM32Cube and CMake.

## 🔧 How to Build
1. Open in **STM32CubeIDE** or **VSCode** with **STM32 CMake Tools**.
2. Connect your STM32 board.
3. Build and flash to your board.
