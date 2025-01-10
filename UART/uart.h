#define System_clock	72000000			//for stm32f103 s/y clock is 72Mhz
#define baud_rate			9600					//for UART 

typedef struct {
    volatile unsigned int SR;
    volatile unsigned int DR;
    volatile unsigned int BRR;
    volatile unsigned int CR1;
    volatile unsigned int CR2;
    volatile unsigned int CR3;
    volatile unsigned int GTPR;
} USART_config;

#define USART1 ((USART_config *) USART1_BASE)
#define USART2 ((USART_config*) USART2_BASE) // Base address of USART2
#define USART3 ((USART_config*) USART3_BASE) // Base address of USART3

void USART_init(USART_config* USARTx, unsigned int Baud_rate);
void tx_data(USART_config* USARTx, char c);
char rx_data(USART_config* USARTx);
void tx_string(USART_config * USARTx, const char *str);
void USART_Receive_string(USART_config* USARTx, char *buffer, unsigned short int Max_length);
