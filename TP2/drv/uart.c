/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: uart.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide functions to manage the STM32 UART device.
   Note : See STM32F100xx reference manual ID16188 rev.5 page 640

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 28.11.2014 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "drv/uart-priv.h"


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
uart_dev_t    G_uart[C_UART_NB];

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
   uart_init

   --------------------------------------------------------------------------
   Purpose:
   Initialize STM32 UART device

   --------------------------------------------------------------------------
   Description:
   This function initializes the UART 'i_id' in function of parameters.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'

-- -------------------------------------------------------------------------- */
int32_t  uart_init
(
    uint32_t    i_id            /* device identifier  */
   ,addr_t      i_base_address  /* base address of UART registers */
   ,uint32_t    i_clock_freq    /* clock external / internal */
   ,uint32_t    i_blocking      /* blocking / not blocking function */
)
{
    /* Local variables */
    /** without object */

    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
    G_uart[i_id].regs = (uart_t *)i_base_address;
    G_uart[i_id].clock_freq = i_clock_freq;
    G_uart[i_id].blocking = (blocking_t)i_blocking;
    
    /* Return success code */
    return 0;
}

/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_setconfig

   --------------------------------------------------------------------------
   Purpose:
   Configure STM32 UART device

   --------------------------------------------------------------------------
   Description:
   This function configures the UART 'i_id' with the config 'i_config'.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'

-- -------------------------------------------------------------------------- */
int32_t  uart_setconfig  ( uint32_t i_id, uart_config_t * i_config )
{
    /* Local variables */
    uint16_t uartdiv;
    
    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
    /* usart enable */
    G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_UE, 1);
    
    /* transmit enable */
    G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_TE, 1);
    
    /* receive enable */
    G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_RE, 1);
    
    /* data width configuration */
    G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_M, i_config->data_width);
    
    /* parity configuration */
    if( i_config->parity == PARITY_NONE )
    {
        G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_PCE, 0);
    }
    else
    {
        G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_PCE, 1);
        G_uart[i_id].regs->CR1 = M_bupdate(G_uart[i_id].regs->CR1, FIELD_CR1_PS, i_config->parity);
    }
    
    /* stop bit configuration */
    G_uart[i_id].regs->CR2 = M_bupdate(G_uart[i_id].regs->CR2, FIELD_CR2_STOP, i_config->stop_bit);
    
    /* mantis and division configuration */
    uartdiv = G_uart[i_id].clock_freq / i_config->rate;
    G_uart[i_id].regs->BRR = M_bupdate(G_uart[i_id].regs->BRR, FIELD_BRR_DIV_MANTIS, ( uartdiv / 16 ));
    G_uart[i_id].regs->BRR = M_bupdate(G_uart[i_id].regs->BRR, FIELD_BRR_DIV_FRACTION, ( uartdiv % 16 ));
    
    /* Return success code */
    return 0;   
}

/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_putc

   --------------------------------------------------------------------------
   Purpose:
   Sends a character

   --------------------------------------------------------------------------
   Description:
   This function sends 'value' on UART 'i_id'.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'
   -2, the data register is not empty
   -3, transmission not complete
   

-- -------------------------------------------------------------------------- */
int32_t  uart_putc ( uint32_t i_id, uint32_t value )
{
    /* Local variables */
    uint32_t sr;
    
    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
        /** ------------------------------------------------------------------ */
    
    sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
    
        /** ------------------------------------------------------------------ */
   
    if(G_uart[i_id].blocking == BLOCKING)
    {
        while ( M_bget(sr, FIELD_SR_TXE) == 0 )
        {
            sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
        }
    }
    else
    {
         if( M_bget(sr, FIELD_SR_TXE) == 0 )
        {
            return -2;
        }
    }
    
        /** ------------------------------------------------------------------ */
        
    G_uart[i_id].regs->DR = M_bupdate(G_uart[i_id].regs->DR, FIELD_DR_DR, value);
        
        /** ------------------------------------------------------------------ */
    
    if(G_uart[i_id].blocking == BLOCKING)
    {
        while ( M_bget(sr, FIELD_SR_TC) == 0 )
        {
            sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
        }
    }
    else
    {
         if( M_bget(sr, FIELD_SR_TC) == 0 )
        {
            return -3;
        }
    }
    
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_getc

   --------------------------------------------------------------------------
   Purpose:
   Reads a character

   --------------------------------------------------------------------------
   Description:
   This function read the input of UART 'i_id'.
     
   --------------------------------------------------------------------------
   Return value:
   read value
   -1, device 'i_id' >= 'C_UART_NB'
   -2, no datareceived
   -3, parity error
   -4, over run error

-- -------------------------------------------------------------------------- */
int32_t  uart_getc ( uint32_t i_id )
{
    /* Local variables */
    uint32_t sr;
    
    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
        /** ------------------------------------------------------------------ */
    
    sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
    
        /** ------------------------------------------------------------------ */
    
    
    if(G_uart[i_id].blocking == BLOCKING)
    {
        while ( M_bget(sr, FIELD_SR_RXNE) == 0 )
        {
            sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
        }
    }
    else
    {
         if( M_bget(sr, FIELD_SR_RXNE) == 0 )
        {
            return -2;
        }
    }
    
    if(G_uart[i_id].blocking == BLOCKING)
    {
        while ( M_bget(sr, FIELD_SR_PE) == 1 )
        {
            sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
        }
    }
    else
    {
         if( M_bget(sr, FIELD_SR_PE) == 1 )
        {
            return -3;
        }
    }
    
    if(G_uart[i_id].blocking == BLOCKING)
    {
        while ( M_bget(sr, FIELD_SR_ORE) == 1 )
        {
            sr = M_field_get(G_uart[i_id].regs->SR, 9, 0);
        }
    }
    else
    {
         if( M_bget(sr, FIELD_SR_ORE) == 1 )
        {
            return -4;
        }
    }
    
    return M_bget(G_uart[i_id].regs->DR, FIELD_DR_DR);
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_write

   --------------------------------------------------------------------------
   Purpose:
   Writes a data

   --------------------------------------------------------------------------
   Description:
   This function writes 'i_data' on the UART 'i_id'.
     
   --------------------------------------------------------------------------
   Return value:
   0, in nominal case
   -1, device 'i_id' >= 'C_UART_NB'
   'status', putc status error

-- -------------------------------------------------------------------------- */
int32_t  uart_write ( uint32_t i_id, uint8_t* i_data, uint32_t i_size )
{
    /* Local variables */
    uint8_t i = 0;
    int32_t status = -1;
    
    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
    for(i = 0; i < i_size; i++)
    {
        status = uart_putc(i_id, i_data[i]);
        
        if( status != 0 )
        {
            return status;
        }
    }
    
    return 0;
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   uart_read

   --------------------------------------------------------------------------
   Purpose:
   Reads a data

   --------------------------------------------------------------------------
   Description:
   This function read the 'i_data' of size 'i_size' from the UART 'i_id'.
     
   --------------------------------------------------------------------------
   Return value:
   read value
   -1, device 'i_id' >= 'C_UART_NB'
   'status', getc status error

-- -------------------------------------------------------------------------- */
int32_t  uart_read ( uint32_t i_id, uint8_t* i_data, uint32_t i_size )
{
    /* Local variables */
    uint8_t i = 0;
    int32_t status = -1;
    
    if(i_id >= C_UART_NB)
    {
        return -1;
    }
    
    for(i = 0; i < i_size; i++)
    {
        status = uart_getc(i_id);
        
        if( status < 0 )
        {
            return status;
        }
        else
        {
            i_data[i] = status;
        }
    }
    
    return 0;
}
