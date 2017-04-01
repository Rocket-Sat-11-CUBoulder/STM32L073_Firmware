#include "User_Functions.h"
#include "stm32l0xx_hal.h"
#include "usart.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
}



int8_t* my_itoa(int8_t* str, int32_t data, int32_t base)
{
    const int8_t* digits = (int8_t *) ("0123456789abcdefghijklmnopqrstuvwxyz");
    uint8_t i = 0;
    uint32_t u_data;

    if(!str || base > 36 || base < 2) return 0;

    if(data < 0 && base == 10)
    {
        *(str + i++) = '-';
        u_data = ((uint32_t)-data);
        if(data == 0)
        {// overflow. not very elegant solution but faster than do-while loop
            *(str + i++) = '2';
            *(str + i++) = '1';
            *(str + i++) = '4';
            *(str + i++) = '7';
            *(str + i++) = '4';
            *(str + i++) = '8';
            *(str + i++) = '3';
            *(str + i++) = '6';
            *(str + i++) = '4';
            *(str + i++) = '8';
            *(str + i++) = '\0';
            return str;
        }
    }
    else u_data = (uint32_t)data;

    do
    {
        *(str + i++) = digits[u_data % base];
        u_data /= base;
    }while(u_data);

    if(str[0] == '-')
        my_reverse((uint8_t *)(str + 1), i - 1);
    else
        my_reverse((uint8_t *)str, i);

    *(str + i) = '\0';
    return str;
}


int8_t my_reverse(uint8_t* src, uint32_t length)
{
    if( !src ) return -1;
	uint32_t i;
    uint8_t temp;

    for(i = 0; i < length >> 1; ++i)
    {
        temp = *(src + i);
        *(src + i)= *(src + length - 1 - i);
        *(src + length -1 - i) = temp;
    }
    return 0;
}


void itoa(uint32_t value){
	uint8_t place1, place2, place3, place4, place5;
	if(value<10){
		place1 = value +48;
		HAL_UART_Transmit(&huart2, &place1, sizeof(uint8_t), 0x20);
	}
	if(value>=10 && value<100){
		place1 = (value % 10)+48;
		place2 = (value / 10)+48;
		HAL_UART_Transmit(&huart2, &place2, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place1, sizeof(uint8_t), 0x20);
	}
	if(value>=100 && value <1000){
		place1 = (value % 10)+48;
		place2 = ((value/10)%10)+48;
		place3 = (value / 100)+48;
		HAL_UART_Transmit(&huart2, &place3, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place2, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place1, sizeof(uint8_t), 0x20);
	}
	if(value >= 1000 && value < 10000){
		place1 = (value % 10)+48;
		place2 = ((value/10)%10)+48;
		place3 = ((value/100)%10)+48;
		place4 = (value/1000)+48;
		HAL_UART_Transmit(&huart2, &place4, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place3, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place2, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place1, sizeof(uint8_t), 0x20);
	}
	if(value >= 10000 && value < 100000){
		place1 = (value % 10)+48;
		place2 = ((value/10)%10)+48;
		place3 = ((value/100)%10)+48;
		place4 = ((value/1000)%10)+48;
		place5 = (value/10000)+48;
		HAL_UART_Transmit(&huart2, &place5, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place4, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place3, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place2, sizeof(uint8_t), 0x20);
		HAL_UART_Transmit(&huart2, &place1, sizeof(uint8_t), 0x20);
	}
}
