#include "SSEG.h"
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_gpio.h"

extern SPI_HandleTypeDef hspi1;
//current number
extern volatile int current_num;
const uint8_t sseg_map[10] = {
    0x3F, //00111111
    0x06, //00000110
    0x5B, //01011011
    0x4F, //01001111
    0x66, //01100110
    0x6D, //01101101
    0x7D, //01111101
    0x07, //00000111
    0x7F, //01111111
    0x6F  //01101111
};

uint8_t digits[4];

void SSEG_Off(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);
}

void SSEG_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure GPIO pins for D pins (PC0 to PC3)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    SSEG_Off();

    //rclk (PA6)
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

    //buttons (PA0, PA1)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //nvic
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void SSEG_Out() {
    uint16_t digit_pins[4] = {GPIO_PIN_3, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0};
    for (int i = 0; i < 4; i++) {
        SSEG_Off(); //turn off digits
        uint8_t num_pattern = sseg_map[digits[i]];
        HAL_SPI_Transmit(&hspi1, &num_pattern, 1, HAL_MAX_DELAY);
        //pulse
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOC, digit_pins[i], GPIO_PIN_RESET); //turn on current digit
        HAL_Delay(1);
    }
}

void EXTI0_1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t last_press_inc = 0;
    uint32_t last_press_dec = 0;
    uint32_t current_time = HAL_GetTick();

    if (GPIO_Pin == GPIO_PIN_0) // increase button
    {
        if (current_time - last_press_inc > 300) //debounce
        {
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
            {
                current_num = current_num + 1;
                if (current_num > 9999)
                    current_num = 0;
                SSEG_Disp_Num(current_num);
                last_press_inc = current_time;
            }
        }
    }
    else if (GPIO_Pin == GPIO_PIN_1) // decrease button
    {
        if (current_time - last_press_dec > 300)
        {
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
            {
                current_num = current_num - 1;
                if (current_num < 0)
                    current_num = 9999;
                SSEG_Disp_Num(current_num);
                last_press_dec = current_time;
            }
        }
    }
}

void SSEG_Disp_Num(int num)
{
    if (num < 0) num = 0;
    if (num > 9999) num = 9999;

    digits[0] = num % 10;          // Ones
    digits[1] = (num / 10) % 10;   // Tens
    digits[2] = (num / 100) % 10;  // Hundreds
    digits[3] = (num / 1000) % 10; // Thousands
}
