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
   Main file of timebase and GPIO drivers

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 26.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"
#include "drv/timebase-priv.h"
#include "drv/rcc-priv.h"
#include "drv/timebase-priv.h"
#include "drv/gpio-priv.h"


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

typedef enum 
{
    GPIO_A = 0,
    GPIO_B = 1,
    GPIO_C = 2,
    GPIO_D = 3,
    GPIO_E = 4
} gpio_enum_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
rcc_dev_t	G_rcc;

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
   timebase_test

   --------------------------------------------------------------------------
   Purpose:
   Test timebase driver

   --------------------------------------------------------------------------
   Description:
   This function checks timebase driver.

-- -------------------------------------------------------------------------- */
void  timebase_test  ( void )
{
    /* Local variables */
    uint32_t status = 0;
    timebase_t config;
    uint32_t count = 0;
    int i =0;
    (void)status;

    /**------------------------------------------------------------------ */
    
    /* Initilize timebase */
    timebase_init(0xe000e010, 1,8);
    
        /**------------------------------------------------------------------ */
    
    /* get test */
    status = timebase_get();
    while( count < 1000)
    {
        count++;
    }
    status = timebase_get();
    
        /**------------------------------------------------------------------ */

    /* wait test */
    status = timebase_get();
    wait(100);
    status = timebase_get();
        
        /**------------------------------------------------------------------ */

    /* gpio blinking test */
    for(i = 0; i < 10; i++)
    {
        wait(1000000);
        gpio_write(GPIO_B, 0, 1);        
        wait(1000000);
        gpio_write(GPIO_B, 0, 0);  
    
    }
   
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
    G_rcc.base_address  = (rcc_t *)0x40021000;
    
    /* Power & Backup clock enable, set PWREN & BKPEN bits */
    G_rcc.base_address->APB1ENR |= 0x18000000;             
    
    /* Enable write access to Backup domain, set DBP bit in PWR register*/
    *(reg32_t *)0x40007000 = 0x0100;
    
    /* Reset Backup domain to change source */
    G_rcc.base_address->BDCR |= 0x00010000;
    G_rcc.base_address->BDCR &= 0xFFFEFFFF;
    
    /* Select the RTC Clock */
    G_rcc.base_address->BDCR |= 0x00000300; // HSE oscillator clock divided by 128 used as RTC clock
    // 8 MHZ / 128
    
    /* Set RTCEN bit */
    G_rcc.base_address->BDCR |= 0x00008000;  
    
    gpio_init(GPIO_B, 0x40010C00);
    gpio_setconfig(GPIO_B, 0, GENERAL_OUTPUT_PUSHPULL, OUTPUT_50);

    /* Check timebase */
    timebase_test();
    
    while(1)
        ;
}
