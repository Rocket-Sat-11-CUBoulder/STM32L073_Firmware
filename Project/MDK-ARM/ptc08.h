/***** Commands ******/
#define PTC08_RESET  0x26
#define PTC08_GEN_VERSION 0x11
#define PTC08_SET_PORT 0x24
#define PTC08_READ_FBUF 0x32
#define PTC08_GET_FBUF_LEN 0x34
#define PTC08_FBUF_CTRL 0x36
#define PTC08_DOWNSIZE_CTRL 0x54
#define PTC08_DOWNSIZE_STATUS 0x55
#define PTC08_READ_DATA 0x30
#define PTC08_WRITE_DATA 0x31
#define PTC08_COMM_MOTION_CTRL 0x37
#define PTC08_COMM_MOTION_STATUS 0x38
#define PTC08_COMM_MOTION_DETECTED 0x39
#define PTC08_MOTION_CTRL 0x42
#define PTC08_MOTION_STATUS 0x43
#define PTC08_TVOUT_CTRL 0x44
#define PTC08_OSD_ADD_CHAR 0x45

#define PTC08_STOPCURRENTFRAME 0x0
#define PTC08_STOPNEXTFRAME 0x1
#define PTC08_RESUMEFRAME 0x3
#define PTC08_STEPFRAME 0x2

#define PTC08_640x480 0x00
#define PTC08_320x240 0x11
#define PTC08_160x120 0x22

#define PTC08_MOTIONCONTROL 0x0
#define PTC08_UARTMOTION 0x01
#define PTC08_ACTIVATEMOTION 0x01

#define PTC08_SET_ZOOM 0x52
#define PTC08_GET_ZOOM 0x53

#define CAMERABUFFSIZ 100
#define CAMERADELAY 10

void setCompressionPTC08(UART_HandleTypeDef huart, uint8_t comp);

void setImgSizePTC08(UART_HandleTypeDef huart, uint8_t size);

void initPTC08(UART_HandleTypeDef huart, uint16_t baud);

void resetPTC08(UART_HandleTypeDef huart);

// low level transmit message
void sendMessagePTC08(UART_HandleTypeDef huart, uint8_t cmd, uint8_t args[], uint16_t argn);