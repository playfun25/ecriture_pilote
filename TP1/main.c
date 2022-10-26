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

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 22.11.2013 - Authors: Brouillard Cédric & Martin Valentin
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"
#include "drv/gpio-priv.h"
#include <stdio.h>


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
/** without object */


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
   gpio_test

   --------------------------------------------------------------------------
   Purpose:
   Test GPIO driver

   --------------------------------------------------------------------------
   Description:
   This function checks GPIO driver.

   --------------------------------------------------------------------------
   Return value:
     0, in nominal case
     -1, otherwise

-- -------------------------------------------------------------------------- */
int  gpio_test  ( void )
{
    /* Local variables */
    int32_t status      = -1;
    uint8_t pa_0         = 0;
    uint8_t pa_13        = 0;
    uint8_t new_pa_0    = 0;
    uint8_t new_pa_13   = 0;
    uint8_t position    = 0;
    uint8_t i           = 0;

//  /* see reference manual page 36 for GPIO mapping */
    
    status = gpio_init(GPIO_A, 0x40010800);
    status = gpio_init(GPIO_B, 0x40010C00);
    
    status = gpio_setconfig(GPIO_A, 0, INPUT_WITH_PULLUP, INPUT);
    status = gpio_setconfig(GPIO_A, 13, INPUT_WITH_PULLUP, INPUT);
    
    for(i = 0; i < 16; i++)
    {
        status = gpio_setconfig(GPIO_B, i, GENERAL_OUTPUT_OPENDRAIN, OUTPUT_50);
        status = gpio_write(GPIO_B, i, 0);
    }    
    
    status = gpio_write(GPIO_B, 0, 1);
    
    (void)status;

    while(1)
    {
        new_pa_0 = gpio_read(GPIO_A, 0);
        new_pa_13 = gpio_read(GPIO_A, 13);
        
        // front descendant sur pa_0
        if( (pa_0 == 1) && (new_pa_0 == 0) )
        {
            for(i = 0; i < NB_CHANNEL; i++)
            {
                if( gpio_read(GPIO_B, i) )
                {
                    position = i;
                }
            }
            
            status = gpio_write(GPIO_B, position, 0);
            
            if(position < (NB_CHANNEL-1))
            {
                position++;
            }
            else
            {
                position = 0;
            }
            
            status = gpio_write(GPIO_B, position, 1);
        }
        
        // front descendant sur pa_13
        if( (pa_13 == 1) && (new_pa_13 == 0) )
        {
            for(i = 0; i < NB_CHANNEL; i++)
            {
                if( gpio_read(GPIO_B, i) )
                {
                    position = i;
                }
            }
            
            status = gpio_write(GPIO_B, position, 0);
            
            if(position > 0)
            {
                position--;
            }
            else
            {
                position = (NB_CHANNEL - 1);
            }
            
            status = gpio_write(GPIO_B, position, 1);
        }
        
        pa_0 = new_pa_0;
        pa_13 = new_pa_13;
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
    /* Local variables */
    /** without object */


    /* check GPIO */
    gpio_test();
}
