#include <stdint.h>
#include "uart.h"
#include "cli.h"
#include "led.h"

#define CMD_BUFFER_SIZE 50

// Command buffer and index
char cmd_buffer[CMD_BUFFER_SIZE];
uint8_t cmd_idx = 0;

// Function to handle received characters and process commands
void Handle_Command_Input(void) {
    char recv_char = rx_data(USART1);

    if (recv_char == '\r' || recv_char == '\n') {
        // Null-terminate the string
        cmd_buffer[cmd_idx] = '\0';

        // Process the command using CLI functionality
        Process_GPIO_Command(cmd_buffer);

        // Reset the buffer for the next command
        cmd_idx = 0;

        // Send a prompt back to the terminal
        tx_string(USART1, "\r\n> ");
    } else if (cmd_idx < CMD_BUFFER_SIZE - 1) {
        // Add the character to the buffer
        cmd_buffer[cmd_idx++] = recv_char;

        // Echo the character back to the terminal
        tx_data(USART1, recv_char);
    }
}

int main(void) {
    // Initialize USART for communication
    USART_init(USART1, 9600);

    // Introductory messages
    tx_string(USART1, "WELCOME TO USART CLI!\r\n");
    tx_string(USART1, "Type your command:\r\n> ");

    // Main loop
    while (1) {
        Handle_Command_Input();
    }
}
