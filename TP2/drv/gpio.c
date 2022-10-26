/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide functions to manage the STM32 GPIO device.
   Note : See STM32F100xx reference manual ID16188 rev.5 page 111

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
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
/** without object */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
gpio_dev_t    G_gpio[C_GPIO_NB];


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
/** without object */


/**========================================================================== --
   Public functions
-- ========================================================================== */

/* -------------------------------------------------------------------------- --
   FUNCTION:
   gpio_init

   --------------------------------------------------------------------------
   Purpose:
   Initialize STM32 GPIO device

   --------------------------------------------------------------------------
   Description:
   This function initializes the GPIO 'i_id' in function of parameters.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'

-- -------------------------------------------------------------------------- */
int32_t  gpio_init
(
    uint32_t    i_id            /* device identifier  */
   ,addr_t      i_base_address  /* base address of GPIO registers */
)
{   
    if(i_id >= C_GPIO_NB)
    {
        return -1;
    }

    G_gpio[i_id].regs = (gpio_t *)i_base_address;
    
    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   gpio_setconfig

   --------------------------------------------------------------------------
   Purpose:
   Configure STM32 GPIO device

   --------------------------------------------------------------------------
   Description:
   This function configures the channel 'i_channel_id' of GPIO 'i_id' in 
   function of 'i_cnd' and 'i_mode' parameters.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'
   -2, 'i_channel_id' > nb_channel 

-- -------------------------------------------------------------------------- */
int32_t  gpio_setconfig
(
    uint32_t    i_id            /* device identifier  */
   ,uint32_t    i_channel_id    /* channel identifier */
   ,gpio_cnf_t  i_cnf           /* IO configuration */
   ,gpio_mode_t i_mode          /* IO mode */
)
{
    if(i_id >= C_GPIO_NB)
    {
        return -1;
    }
    
    if( i_channel_id < (NB_CHANNEL/2) )
    {
        G_gpio[i_id].regs->CRL = (reg32_t)M_field_update(G_gpio[i_id].regs->CRL, (i_channel_id*4)+3, (i_channel_id*4)+2, i_cnf);
        G_gpio[i_id].regs->CRL = (reg32_t)M_field_update(G_gpio[i_id].regs->CRL, (i_channel_id*4)+1, (i_channel_id*4)+0, i_mode);
    }
    else if( i_channel_id < NB_CHANNEL )
    {
        i_channel_id -= 8;
        G_gpio[i_id].regs->CRH = (reg32_t)M_field_update(G_gpio[i_id].regs->CRH, i_channel_id*4+3, i_channel_id*4+2, i_cnf);
        G_gpio[i_id].regs->CRH = (reg32_t)M_field_update(G_gpio[i_id].regs->CRH, i_channel_id*4+1, i_channel_id*4+0, i_mode);
    }
    else
    {
        return -2;
    }
    
    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   gpio_write

   --------------------------------------------------------------------------
   Purpose:
   Set discrete state

   --------------------------------------------------------------------------
   Description:
   This function sets the output 'i_channel' of GPIO 'i_id' to 'i_state'.
     
   --------------------------------------------------------------------------
   Return value:
   Résultat de l'ecriture,
   -1, device 'i_id' >= 'C_UART_NB'
   -2, 'i_channel_id' > nb_channel
   -3 the channel is not configure on OUTPUT mode

-- -------------------------------------------------------------------------- */
int32_t gpio_write
(
    uint32_t    i_id                /* device identifier  */
   ,uint32_t    i_channel_id        /* channel identifier */
   ,uint32_t    i_state             /* value to set on output channel */
)
{
    /* Local variables */
    gpio_mode_t mode;
    
    if(i_id >= C_GPIO_NB)
    {
        return -1;
    }
    
    // Si le nb de channel est inférieur ou égale au nombre de channel disponible
    if( i_channel_id < (NB_CHANNEL/2) )
    {
        mode = (gpio_mode_t)M_field_get( G_gpio[i_id].regs->CRL, (i_channel_id*4)+1, (i_channel_id*4)+0 );
    }
    else if( i_channel_id < NB_CHANNEL )
    {
        mode = (gpio_mode_t)M_field_get( G_gpio[i_id].regs->CRH, ((i_channel_id-8)*4)+1, ((i_channel_id-8)*4)+0 );
    }
    else
    {
        return -2;
    }
    
    // Si on est en OUTPUT
    if( (mode == OUTPUT_10) || (mode == OUTPUT_2) || (mode == OUTPUT_50) )
    {
        G_gpio[i_id].regs->ODR = (reg32_t)M_field_update(G_gpio[i_id].regs->ODR, i_channel_id, i_channel_id, i_state);
    }
    else
    {
        return -3;
    }

    /* Return success code */
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   gpio_read

   --------------------------------------------------------------------------
   Purpose:
   Get discrete state

   --------------------------------------------------------------------------
   Description:
   This function returns the state of channel 'i_channel_id' of GPIO 'i_id'.

   --------------------------------------------------------------------------
   Return value:
     'status', discrete state
     -1, device 'i_id' >= 'C_UART_NB'
     -2, 'i_channel_id' > nb_channel
     -3, 'mode' is not readable

-- -------------------------------------------------------------------------- */
int32_t  gpio_read
(
    uint32_t    i_id            /* device identifier  */
   ,uint32_t    i_channel_id    /* channel identifier */
)
{
    /* Local variables */
    uint32_t state = 0;
    gpio_mode_t mode;
    
    if(i_id >= C_GPIO_NB)
    {
        return -1;
    }
    
    // if 'i_channel_id' <= 'NB_CHANNEL'
    if( i_channel_id < (NB_CHANNEL/2) )
    {
        mode = (gpio_mode_t)M_field_get( G_gpio[i_id].regs->CRL, (i_channel_id*4)+1, (i_channel_id*4)+0 );
    }
    else if( i_channel_id < NB_CHANNEL )
    {
        mode = (gpio_mode_t)M_field_get( G_gpio[i_id].regs->CRH, ((i_channel_id-8)*4)+1, ((i_channel_id-8)*4)+0 );
    }
    else
    {
        return -2;
    }
    
    // if 'mode' is an OUTPUT mode
    if( (mode == OUTPUT_10) || (mode == OUTPUT_2) || (mode == OUTPUT_50) )
    {
        state = (reg32_t)M_field_get(G_gpio[i_id].regs->ODR, i_channel_id, i_channel_id);
    }
    else if( mode == INPUT )
    {
        state = (reg32_t)M_field_get(G_gpio[i_id].regs->IDR, i_channel_id, i_channel_id);
    }
    else
    {
        return -3;
    }

    /* Return state of channel */
    return state;
}
