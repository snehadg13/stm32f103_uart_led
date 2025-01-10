#include "gpio.h"
#include <stdint.h>
#include <string.h>

// Map a port name (e.g., "GPIOA") to the GPIO_config*
GPIO_config* Get_GPIO_Port(const char* port_name) {
    if (strcmp(port_name, "GPIOA") == 0) {
        return GPIOA;
    } else if (strcmp(port_name, "GPIOB") == 0) {
        return GPIOB;
    } else if (strcmp(port_name, "GPIOC") == 0) {
        return GPIOC;
    }
    return NULL; // Invalid port
}

// Enable clock for a GPIO port
void RCC_Enable_GPIO(GPIO_config *GPIOx) {
    if (GPIOx == GPIOA) {
        RCC->APB2ENR |= (1 << 2);  // Enable clock for GPIOA
    } else if (GPIOx == GPIOB) {
        RCC->APB2ENR |= (1 << 3);  // Enable clock for GPIOB
    } else if (GPIOx == GPIOC) {
        RCC->APB2ENR |= (1 << 4);  // Enable clock for GPIOC
    }
}

// Initialize GPIO pin
void GPIO_Init(GPIO_config *GPIOx, uint16_t pin, uint32_t mode, uint32_t speed) {
    RCC_Enable_GPIO(GPIOx);
    uint32_t shift = (pin % 8) * 4;
    if (pin < 8) {
        GPIOx->CRL = (GPIOx->CRL & ~(0xF << shift)) | (((mode << 2) | speed) << shift);
    } else {
        GPIOx->CRH = (GPIOx->CRH & ~(0xF << shift)) | (((mode << 2) | speed) << shift);
    }
}

// Write to GPIO pin
void GPIO_Write(GPIO_config *GPIOx, uint16_t pin, uint8_t value) {
    if(value) 
		{
			GPIOx->BSRR = (1 << pin);
		}
    else 
		{
			GPIOx->BRR = (1 << pin);
		}
}

// Read GPIO pin value
uint8_t GPIO_Read(GPIO_config *GPIOx, uint16_t pin) {
    return (GPIOx->IDR & (1 << pin)) ? 1 : 0;
}

// Set GPIO pin
void GPIO_Set(GPIO_config *GPIOx, uint16_t pin) {
    GPIOx->ODR |= (1 << pin);
}

// Clear GPIO pin
void GPIO_Clear(GPIO_config *GPIOx, uint16_t pin) {
    GPIOx->ODR &= ~(1 << pin);
}
