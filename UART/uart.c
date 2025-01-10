#include "uart.h"
#include "gpio.h"

//USART selection
void RCC_Enable_USART(USART_config* USARTx)
{
    if (USARTx == USART1)
    {
        RCC->APB2ENR |= (1 << 14);  // Enable clock for USART1
    }
    else if (USARTx == USART2)
    {
        RCC->APB1ENR |= (1 << 17);  // Enable clock for USART2
    }
    else if (USARTx == USART3)
    {
        RCC->APB1ENR |= (1 << 18);  // Enable clock for USART3
    }
}


void USART_init(USART_config* USARTx, unsigned int Baud_rate)
{
    // Step 1: Enable USART clock
    RCC_Enable_USART(USARTx);

    // Step 2: Configure GPIO pins for USART
    // PA9 (Tx) as Alternate Function Push-Pull, High Speed
    GPIO_Init(GPIOA, 9, GPIO_MODE_AF_PP, GPIO_SPEED_HIGH);
    // PA10 (Rx) as Input Floating, Low Speed
    GPIO_Init(GPIOA, 10, GPIO_MODE_INPUT, GPIO_SPEED_LOW);

    // Step 3: Set Baud Rate
    USARTx->BRR = (72000000 / Baud_rate);  // Assuming 72 MHz system clock

    // Step 4: Configure USART for 8 data bits, 1 stop bit
    USARTx->CR1 |= (1 << 13) | (1 << 3) | (1 << 2);  // Enable USART, Transmitter, and Receiver
    USARTx->CR2 = 0x0000;  // Default: 1 stop bit
    // USARTx->CR3 = 0x0000;  // No hardware flow control (optional, already default)
}


void tx_data(USART_config* USARTx, char c) 
{
		while (!(USARTx->SR & (1 << 7))); // Wait until TXE=1 (Transmit Data Register Empty)
		USARTx->DR=c;  
}

char rx_data(USART_config* USARTx) {
		while (!(USARTx->SR & (1 << 5))); // Wait until RXNE (Receive Data Register Not Empty)
		return (USARTx->DR); 
}

//Fucntion to transmit string
void tx_string(USART_config * USARTx, const char *str)
{
	while(*str)
	{
		tx_data(USARTx,*str++);
	}
}

void USART_Receive_string(USART_config* USARTx, char *buffer, unsigned short int Max_length)
{
	unsigned short int i=0;
	char c;
	
	while(i<Max_length-1)
	{
		c= rx_data(USARTx);
		tx_data(USARTx,c);
		
		if(c == '\n')
		{
			break;
		}
		buffer[i++]=c;
	}
	buffer[i]='\0';
}
