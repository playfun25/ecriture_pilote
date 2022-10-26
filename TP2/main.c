/* ========================================================================== --
                     copyright, Polytech'Tours, 2013-2013

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: main.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Main file of UART and GPIO drivers
   Note : See STM32F100xx reference manual ID16188 rev.5 page 640

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"
#include "drv/uart-priv.h"
#include "drv/gpio-priv.h"
#include "drv/rcc-priv.h"
#include "drv/afio-priv.h"


/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local types
-- -------------------------------------------------------------------------- */
/* see reference manual page 640 */
typedef enum 
{
    USART_1 = 0,
    USART_2 = 1,
    USART_3 = 2,
    USART_4 = 3,
    USART_5 = 4,
    USART_6 = 5,
} uart_enum_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
rcc_dev_t	G_rcc;
afio_dev_t  G_afio;


/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */


/**========================================================================== --
   Private functions
-- ========================================================================== */

/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_test

   --------------------------------------------------------------------------
   Purpose:
   Test UART driver

   --------------------------------------------------------------------------
   Description:
   This function checks UART driver.

   --------------------------------------------------------------------------
   Return value:
   *  0, in nominal case
   * -1, otherwise

-- -------------------------------------------------------------------------- */
int  uart_test  ( void )
{
    /* Local variables */
    int32_t status = -1;
    uart_config_t config;
    uint8_t data[6];

    /* Initilize 'USART_1' */
    status = uart_init(USART_1, 0x40013800, 8000000, BLOCKING);
    
    /* Create configuration */
    config.rate = 115200;
    config.parity = PARITY_EVEN;
    config.data_width = DATA_WITDH_8N1;
    config.stop_bit = STOP_BIT_1;
    
    /* apply configuration */
    status = uart_setconfig(USART_1, &config);
    
    /* Test 'UART_1' primary functions */
    status = uart_getc(USART_1);
    status = uart_putc(USART_1, 'A');
    
    /* Test 'UART_1' functions */
    status = uart_read(USART_1, data, 6);
    status = uart_write(USART_1, data, 6);
    
    /* Return status code */
    return status;
}



/**========================================================================== --
   Public functions
-- ========================================================================== */


/* -------------------------------------------------------------------------- --
   FUNCTION:
   main

   --------------------------------------------------------------------------
   Purpose:
   Main function

   --------------------------------------------------------------------------
   Description:
   This function is the entry point of the software.

   --------------------------------------------------------------------------
   Return value:
     0

-- -------------------------------------------------------------------------- */
 int  main  ( void )
 {
    /* Local variables */
    int32_t status = -1;
    (void)status;

    G_rcc.base_address  = (rcc_t *)0x40021000;
    G_afio.base_address = (afio_t *)0x40010000;
    
    /* Enable clock for Alternate function I/O */
    G_rcc.base_address->APB2ENR |= 0x01;        /* RCC_APB2ENR_AFIOEN */

    /* Disable USART1 remap */
    /* It controls the mapping of USART1 TX and RX alternate functions on the GPIO ports */
    /* USART1.TX = PA.9, USART1.RX = PA.10 */
    G_afio.base_address->MAPR   &= ~(1 << 2);    
    status = status = gpio_init(0, 0x40010800);
    status = gpio_setconfig(0, 9, GENERAL_OUTPUT_PUSHPULL, OUTPUT_50);
    
    /* Enable clock for USART1 */
    G_rcc.base_address->APB2ENR |= 0x01 << 14; /* RCC_APB2ENR_USART1EN; */

    /* Check UART */
    uart_test();
}
