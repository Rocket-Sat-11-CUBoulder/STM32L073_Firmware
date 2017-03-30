#include "User_Functions.h"
#include "stm32l0xx_hal.h"

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
