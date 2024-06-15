#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <time.h>
#include "stdio.h"

void GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PA1, PA3, PA5 as output
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA0 as input joystick button
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Toggle_LED(uint16_t GPIO_Pin) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_Pin);
}

void Turn_Off_LED(uint16_t GPIO_Pin) {
    HAL_GPIO_WritePin(GPIOA, GPIO_Pin, GPIO_PIN_RESET);
}
void intro(void) {
    for (int i = 0; i < 3; i++) {
        // Blink red LED
        Toggle_LED(GPIO_PIN_1);
        HAL_Delay(150);
        Toggle_LED(GPIO_PIN_1);

        // Blink yellow LED
        HAL_Delay(150);
        Toggle_LED(GPIO_PIN_3);
        HAL_Delay(150);
        Toggle_LED(GPIO_PIN_3);

        // Blink green LED
        HAL_Delay(150);
        Toggle_LED(GPIO_PIN_5);
        HAL_Delay(150);
        Toggle_LED(GPIO_PIN_5);

        HAL_Delay(150);
    }
}
void Blink_LED(uint16_t GPIO_Pin, int times, int delay) {
    for (int i = 0; i < times; i++) {
        Toggle_LED(GPIO_Pin);
        HAL_Delay(delay);
        Toggle_LED(GPIO_Pin);
        HAL_Delay(delay);
    }
}

int main(void) {
    HAL_Init();
    GPIO_Init();

    uint32_t start_time, end_time, elapsed_time;

    srand(time(NULL));

    while (1) {
    	intro();

        // Red LED
        HAL_Delay(1000);
        Toggle_LED(GPIO_PIN_1);
        HAL_Delay(2000);

        // Yellow LED
        Toggle_LED(GPIO_PIN_3);

        //Random delay between 1 and 6 seconds for green
        int random_delay = (rand() % 6 + 1) * 1000;
        HAL_Delay(random_delay);

        //Green LED
        Toggle_LED(GPIO_PIN_5);

        start_time = HAL_GetTick();

        // Wait for joystick button press
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);

        // Debounce Control
        HAL_Delay(50);

        // Wait until button is released
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);

        end_time = HAL_GetTick();

        //Subtract Debounce delay
        elapsed_time = end_time - start_time - 50;
        printf("Your Reaction Time: %lu ms\n", elapsed_time);

        Turn_Off_LED(GPIO_PIN_1);
        Turn_Off_LED(GPIO_PIN_3);
        Turn_Off_LED(GPIO_PIN_5);

        HAL_Delay(500);

        if (elapsed_time < 110) {
            printf("Reaction: Insane\n");
            Blink_LED(GPIO_PIN_5, 10, 200);
        } else if (elapsed_time < 180) {
            printf("Reaction: Fast\n");
            Blink_LED(GPIO_PIN_5, 5, 300);
        } else if (elapsed_time < 300) {
            printf("Reaction: Average\n");
            Blink_LED(GPIO_PIN_3, 5, 400);
        } else if (elapsed_time < 400) {
            printf("Reaction: Slow\n");
            Blink_LED(GPIO_PIN_1, 5, 300);
        } else {
            printf("Reaction: Turtle\n");
            Blink_LED(GPIO_PIN_1, 10, 200);
        }
        HAL_Delay(1000);
    }
}
