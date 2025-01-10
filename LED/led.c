#include "led.h"

void LED_INIT(GPIO_config* Port, unsigned short int Pin) 
{
    GPIO_Init(Port, Pin, GPIO_MODE_AF_PP, GPIO_SPEED_MED);
}

void LED_ON(GPIO_config* Port, unsigned short int Pin) 
{
    GPIO_Set(Port, Pin);
}

void LED_OFF(GPIO_config* Port, unsigned short int Pin) 
{
    GPIO_Clear(Port, Pin);
}
