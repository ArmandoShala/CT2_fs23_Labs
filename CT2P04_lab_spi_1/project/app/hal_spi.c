
/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Module      : SPI Library
 * -- Description :
 * --
 * -- $Id: hal_spi.c 4707 2019-02-26 09:32:59Z ruan $
 * ------------------------------------------------------------------
 */
#include <reg_stm32f4xx.h>
#include "hal_spi.h"

#define BIT_TXE  (uint32_t)0x00000002
#define BIT_RXNE (uint32_t)0x00000001
#define BIT_BSY  (uint32_t)0x00000080

static void set_ss_pin_low(void);
static void set_ss_pin_high(void);
static void wait_10_us(void);

/*
 * according to description in header file
 */
void hal_spi_init(void)
{
    RCC->APB2ENR |= 0x00001000;       // enable SPI clock
    RCC->AHB1ENR |= 0x00000001;       // start clock on GPIO A
    
    
    // configure GPIOs
    // P5.5 --> PA4 (NSS)       --> output
    // P5.6 --> PA5 (SCLK)      --> AF5 (see datasheet)
    // P5.7 --> PA6 (MISO)      --> AF5 (see datasheet)
    // P5.8 --> PA7 (MOSI)      --> AF5 (see datasheet)
    // P5.9 --> PA8 (NSBUF)     --> input

    GPIOA->OSPEEDR &= 0xFFFF00FF;   // clear PA4-PA7
    GPIOA->OSPEEDR |= 0x0000FF00;   // set PA4-PA7 to very high speed
    
    GPIOA->MODER &= 0xFFFC00FF;     // clear mode on PA4-PA8 --> PA8 = input
        
    GPIOA->MODER |= 0x0000A800;     // set alternate function on PA5-PA7
    GPIOA->MODER |= 0x00000100;     // set PA4 to output
    
    GPIOA->AFRL &= 0x000FFFFF;      // clear alternate function
    GPIOA->AFRL |= 0x55500000;      // Set SPI1 (AF5) alternate function PA5-PA7
    
    // configure SPI
    SPI1->CR2 = 0x0000;             // set spi to default state
    SPI1->CR1 = 0x0000;             // set spi to default state

    // add your SPI configs below (based on reference manual)
    
    /// STUDENTS: To be programmed

    // Konfiguration von SPI1->CR1
/*    SPI1->CR1 |= (0 << 15)   // BIDIMODE = 0
                 | (0 << 14)   // BIDIOE = 0
                 | (0 << 13)   // CRCEN = 0
                 | (0 << 12)   // CRCNEXT = 0
                 | (1 << 9)    // SSM = 1
                 | (1 << 8)    // SSI = 1
                 | (1 << 6);   // SPE = 1
*/


		// SPI CR1 (Reference Manual 896pp)
		// 15 bidimode = 0 (2-line unidirectional data mode selected)
		// 14 bidioe = 0 (Not used in this mode)
		// 13 crcen = 0 (CRC calculation disabled)
		// 12 crcnext = 0 (Data phase (no CRC phase))
		// 11 dff = 0 (8-bit data frame format is selected for transmission/reception)
		// 10 rxonly = 0 (Full-duplex mode)
		// 9 ssm = 1 (Software slave management enabled)
		// 8 ssi = 1 (Internal slave select enabled)
		// 7 lsbfirst = 0 (MSB transmitted first)
		// 6 spe = 1 (Set to 1 once all bits are configured)
		// 5 br[2] = 0
		// 4 br[1] = 1 // 42'000'000 / x <= 200'000: x = 256
		// 3 br[0] = 1
		// 2 mstr = 1 (Master configuration)
		// 1 cpol = 0 or 1 (Depends on the specific SPI display's requirements)
		// 0 cpha = 0 or 1 (Depends on the specific SPI display's requirements)


		// CR1 configuration is based on the above determined values
		SPI1->CR1 = 0x033C;
		
		//activate setting by changing SPE to 1
		SPI1->CR1 |= (1 << 6); //changing bit 6 to one // turn SPI on by setting SPE flag to 1

    /// END: To be programmed
    
    set_ss_pin_high();
}


uint8_t hal_spi_read_write(uint8_t send_byte)
{


    set_ss_pin_low(); // Set SS pin low

    // Wait until TXE is set (transmit buffer empty)
    while (!(SPI1->SR & BIT_TXE))
    {
    }

    // Send the byte
    SPI1->DR = send_byte;

    // Wait until RXNE is set (receive buffer not empty)
    while (!(SPI1->SR & BIT_RXNE))
    {
    }

    wait_10_us(); // Wait for 10us
    set_ss_pin_high(); // Set SS pin high

			    // Read the received byte
    volatile uint32_t received_byte = SPI1->DR;
		
		
		return (uint8_t)received_byte;
}


/**
 * \brief  Set Slave-Select Pin (P5.5 --> PA4) low
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_low(void)
{
    GPIOA->BSRR = 0x00100000;          // Set P5.5 --> PA4 low
}

/**
 * \brief  Set Slave-Select Pin (P5.5 --> PA4) high
 *
 * No parameters
 *
 * No returns
 */
static void set_ss_pin_high(void)
{
    GPIOA->BSRR = 0x00000010;          // Set P5.5 --> PA4 high
}

/**
 * \brief  Wait for approximately 10us
 *
 * No parameters
 *
 * No returns
 */
static void wait_10_us(void)
{
    uint8_t counter = 0;
    while (counter < 160) {
        counter++;
    }
}