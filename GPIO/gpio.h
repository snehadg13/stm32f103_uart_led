#define PERIPH_BASE         ((unsigned int)0x40000000)
#define APB1PERIPH_BASE   PERIPH_BASE
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x10000)
#define RCC_BASE	0x40021000  // RCC base address
#define USART1_BASE   (APB2PERIPH_BASE + 0x3800)
#define USART2_BASE   (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE   (APB1PERIPH_BASE + 0x4800)		


/// GPIO Register Structure
typedef struct {
    volatile unsigned int CRL;   // Configuration Register Low
    volatile unsigned int CRH;   // Configuration Register High
    volatile unsigned int IDR;   // Input Data Register
    volatile unsigned int ODR;   // Output Data Register
    volatile unsigned int BSRR;  // Bit Set/Reset Register
    volatile unsigned int BRR;   // Bit Reset Register
    volatile unsigned int LCKR;  // Lock Register
} GPIO_config;


// RCC Register Structure
typedef struct {
    volatile unsigned int CR;        // Control Register
    volatile unsigned int CFGR;      // Clock Configuration Register
    volatile unsigned int CIR;       // Clock Interrupt Register
    volatile unsigned int APB2RSTR;  // APB2 Reset Register
    volatile unsigned int APB1RSTR;  // APB1 Reset Register
    volatile unsigned int AHBENR;    // AHB Clock Enable Register
    volatile unsigned int APB2ENR;   // APB2 Clock Enable Register
    volatile unsigned int APB1ENR;   // APB1 Clock Enable Register
    volatile unsigned int BDCR;      // Backup Domain Control Register
    volatile unsigned int CSR;       // Control/Status Register
} RCC_config;

// Base Addresses
#define GPIOA ((GPIO_config *)0x40010800)  // GPIO Port A Base Address
#define GPIOB ((GPIO_config *)0x40010C00)  // GPIO Port B Base Address
#define GPIOC ((GPIO_config *)0x40011000)  // GPIO Port C Base Address
#define RCC   ((RCC_config *)0x40021000)   // RCC Base Address

// GPIO Pin Definitions
#define GPIO_PIN_0   0x0001
#define GPIO_PIN_1   0x0002
#define GPIO_PIN_2   0x0004
#define GPIO_PIN_3   0x0008
#define GPIO_PIN_4   0x0010
#define GPIO_PIN_5   0x0020
#define GPIO_PIN_6   0x0040
#define GPIO_PIN_7   0x0080
#define GPIO_PIN_8   0x0100
#define GPIO_PIN_9   0x0200
#define GPIO_PIN_10  0x0400
#define GPIO_PIN_11  0x0800
#define GPIO_PIN_12  0x1000
#define GPIO_PIN_13  0x2000
#define GPIO_PIN_14  0x4000
#define GPIO_PIN_15  0x8000

// GPIO Modes
#define GPIO_MODE_INPUT      0x00
#define GPIO_MODE_OUTPUT_PP  0x01  // Push-Pull Output
#define GPIO_MODE_OUTPUT_OD  0x02  // Open-Drain Output
#define GPIO_MODE_AF_PP      0x03  // Alternate Function Push-Pull
#define GPIO_MODE_AF_OD      0x04  // Alternate Function Open-Drain

// GPIO Speeds
#define GPIO_SPEED_LOW   0x00  // Default Low Speed
#define GPIO_SPEED_MED   0x01  // Medium Speed (10 MHz)
#define GPIO_SPEED_HIGH  0x02  // High Speed (50 MHz)

// Function Prototypes
void RCC_Enable_GPIO(GPIO_config *GPIOx);
void GPIO_Init(GPIO_config *GPIOx, unsigned short int pin, unsigned int mode, unsigned int speed);
void GPIO_Write(GPIO_config *GPIOx, unsigned short int pin, unsigned char value);
unsigned char GPIO_Read(GPIO_config *GPIOx, unsigned short int pin);
void GPIO_Set(GPIO_config *GPIOx, unsigned short int pin);
void GPIO_Clear(GPIO_config *GPIOx, unsigned short int pin);
