# STM32 7-Segment Display with Shift Register (SPI Interface)

This project drives a 4-digit 7-segment display (5641AS) using an STM32F0DISCOVERY microcontroller
and a 74HC595 shift register via the SPI interface. Using two switches, the number displayed
through the variable `current_num` will either increment or decrement based on button press.

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
| -         | A-G       | QA-QG       | 7Segment connection to Shift Register | Light up segments to display numbers |
(O̅E̅->GND)
(S̅R̅C̅L̅R̅->VCC)
<div align="center">
  <img src="https://cdn.discordapp.com/attachments/717497591205462036/1433346517057536021/image.png?ex=69045b77&is=690309f7&hm=5b2bbcaf581f086bf9799a11819ca4055cf773ad94b1d305a2c150fcf32691f6" alt="5641AS Pins" width="400"/>
</div>

---

## Files

- `Core/Inc` — Header files
- `Core/Src` — Source files
- `CMakeLists.txt` — Build configuration for STM32Cube and CMake
- `STM32_7Segment.ioc` — CubeIDE project configuration file (pin mappings, peripheral setup)

**Highlighted Files:**
- `main.c` – Initializes peripherals and runs the main loop.
- `SSEG.c` / `SSEG.h` – Handles display multiplexing and SPI communication.

## How to Build and Run

1. Open the project in **STM32CubeIDE** or **VSCode** with STM32 CMake Tools.
2. Open the `.ioc` file to restore pin mappings and peripheral configuration.
3. Connect your STM32 board.
4. Build the project (`Build` / `CMake Build`).
5. Flash the firmware to the board.
6. Press **PA0** / **PA1** to increment/decrement the displayed number.

## References:
[1] Mikrotronics Academy, "STM32 for Beginners | Multiplexing Seven Segment Displays using HAL Libraries GPIO," YouTube, https://www.youtube.com/watch?v=7CjRpUFiBfY (accessed Oct. 29, 2025). 
[2] STMicroelectronics, STR71X GPIO driving four 7-segment display, https://www.st.com/resource/en/application_note/cd00015425-str71x-gpio-driving-four-7segment-display-stmicroelectronics.pdf (accessed Oct. 15, 2025). 
[3] ChatGPT, "Code error fix," OpenAI, Oct. 2025. 
Helped with debugging, suggestions of approach for interrupt code and smooth debouncing, and helped with how to have the digit displays split so that the numbers do not all change with button press at the same time
