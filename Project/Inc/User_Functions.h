#ifndef __User_Functions_H
#define __User_Functions_H

#include "stm32l0xx_hal.h"
#include "main.h"
/****************************************************************
* int8_t* my_itoa(int8_t* str, int32_t data, int32_t base);
*        
*    Description: Converts signed 32-bit integer data to null terminated
*    ascii character string representation with radix given by parameter
*    base. Base 2 - Base 36 are supported (who the hell is using Base 36?).
*    Alphabetic and numeric characters are used to give 36 unique characters.
*    Verifies str is valid (!= NULL). It is up to the user to ensure that str
*    points at a buffer large enough to hold the resulting character string.
*    The size of the buffer pointed at by str should generally be at least
*    ceiling(logb(data)/log10(data)), where logb() is the logarithm whose
*    base is base. The return value is the same as str.
*
*    Parameters:
*        - int8_t* str: Pointer to buffer used to store ascii character string.
*          It is up to the user to ensure the size of the buffer is large enough.
*          The buffer must be large enough to hold numerical data in addition to 1
*          sign byte (only if base == 10 and data < 0) and a null-terminator byte.
*        - int32_t data: Value to be converted into string representation.  
*        - int32_t base: Radix of resultant character string. Can range from 2-36.
*
*    Return value: int8_t*. The return value points at the same address as str.
*        In case of NULL string being passed in for str or illegal base values used,
*        return value will be NULL (0).
*
*****************************************************************/
 int8_t* my_itoa(int8_t* str, int32_t data, int32_t base);
 int8_t my_reverse(uint8_t* src, uint32_t length);





#endif
