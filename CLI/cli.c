#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.h"
#include "uart.h"
#include "led.h"

// Get GPIO port pointer from string
GPIO_config* Resolve_GPIO_Port(const char* PortName) {
    if (strcmp(PortName, "GPIOA") == 0) {
        return GPIOA;
    } else if (strcmp(PortName, "GPIOB") == 0) {
        return GPIOB;
    } else if (strcmp(PortName, "GPIOC") == 0) {
        return GPIOC;
    }
    return NULL; // Invalid port
}

// Process command to control GPIO
void Process_GPIO_Command(const char* Command) {
    char PortBuffer[6];   // For storing port name (e.g., "GPIOA")
    unsigned short int PinNumber;   // For pin number
    char ActionBuffer[4]; // For action (e.g., "ON" or "OFF")

    // Parse command in the format: "GPIOx,pin ACTION"
    if (sscanf(Command, "%5[^,],%hu %3s", PortBuffer, &PinNumber, ActionBuffer) == 3) {
        GPIO_config* GPIO_Port = Resolve_GPIO_Port(PortBuffer);

        if (GPIO_Port == NULL || PinNumber > 15) {
            tx_string(USART1, "Error: Invalid Port or Pin.\r\n");
            return;
        }

        // Execute the action
        if (strcmp(ActionBuffer, "ON") == 0) {
            LED_ON(GPIO_Port, PinNumber); // Turn on the LED
            tx_string(USART1, "Success: LED turned ON.\r\n");
        } else if (strcmp(ActionBuffer, "OFF") == 0) {
            LED_OFF(GPIO_Port, PinNumber); // Turn off the LED
            tx_string(USART1, "Success: LED turned OFF.\r\n");
        } else {
            tx_string(USART1, "Error: Invalid action. Use ON or OFF.\r\n");
        }
    } else {
        tx_string(USART1, "Error: Invalid command format. Use GPIOx,pin ACTION.\r\n");
    }
}
