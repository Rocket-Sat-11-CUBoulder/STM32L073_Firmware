#include "stm32l0xx_hal.h"
#include "usart.h"
#include "ptc08.h"

void initPTC08(UART_HandleTypeDef huart, uint16_t baud) {
	// wait 2.5 seconds?, reset, set baud rate?
}

void resetPTC08(UART_HandleTypeDef huart) {
	uint8_t arg = 0x00;
	sendMessagePTC08(huart, PTC08_RESET, &arg, 1);
}

void setImgSizePTC08(UART_HandleTypeDef huart, uint8_t size) {
	uint8_t args[] = {0x05, 0x04, 0x01, 0x00, 0x19, size};
	sendMessagePTC08(huart, PTC08_WRITE_DATA, args, 6*sizeof(uint8_t));
}

void setCompressionPTC08(UART_HandleTypeDef huart, uint8_t comp) {
	uint8_t args[] = {0x5, 0x1, 0x1, 0x12, 0x04, comp};
	sendMessagePTC08(huart, PTC08_WRITE_DATA, args, 6);
}

// low level send message
void sendMessagePTC08(UART_HandleTypeDef huart, uint8_t cmd, uint8_t args[], uint16_t argn) {
	uint8_t first_msg[] = {0x76, 0x00, cmd};
	HAL_UART_Transmit(&huart, first_msg, 3*sizeof(uint8_t), 0x20);
	HAL_UART_Transmit(&huart, args, argn*sizeof(uint8_t), 0x20);
}