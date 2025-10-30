# STM32 7-Segment Display with Shift Register (SPI Interface)

This project drives a 4-digit 7-segment display (5641AS) using an STM32F0DISCOVERY microcontroller
and a 74HC595 shift register via the SPI interface.

## Features
- Displays a 4-digit number using SPI communication.
- Increments/decrements the displayed number via pushbuttons (PA0 / PA1).
- Supports hardware-based multiplexing for smooth display refresh.
- Debounce logic included for reliable button input.

---

## Hardware Connections

| STM32 Pin | 5641AS Pin | 74HC595 Pin | Function | Notes |
|-----------|------------|-------------|----------|-------|
| PA7       | -         | SER         | SPI MOSI | Serial data input to shift register |
| PA5       | -         | SRCLK       | SPI SCK  | Clock signal for shift register |
| PA6       | -         | RCLK        | Latch    | Latch clock to update outputs |
| PC0–PC3   | D1-D4     | -           | Digit select | Active-low control     |
| PA0       | -         | –           | Button 1 | Increment displayed number |
| PA1       | -         | –           | Button 2 | Decrement displayed number |
| -         | A-G       | Q0-Q6       | 7Segment connection to Shift Register | Lights up segments to show numbers |
---

## Files

- `Core/Inc` — Header files
- `Core/Src` — Source files
  - **Highlighted Files**
    - `main.c` – Initializes peripherals and runs the main loop.
    - `SSEG.c` / `SSEG.h` – Handles display multiplexing and SPI communication.
- `CMakeLists.txt` – Build configuration for STM32Cube and CMake.

## 🔧 How to Build
1. Open in **STM32CubeIDE** or **VSCode** with **STM32 CMake Tools**.
2. Connect your STM32 board.
3. Build and flash to your board.
