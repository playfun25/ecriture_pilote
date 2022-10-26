/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Public data and prototype of STM32 UART driver.
   Note : See STM32F100xx reference manual ID16188 rev.5 page 640

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_UART_H
#define D_UART_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
typedef enum
{
     PARITY_NONE = 2    /* Parity none */
    ,PARITY_EVEN = 0    /* Parity even */
    ,PARITY_ODD = 1     /* Parity odd */
} uart_parity_t;

    /** ------------------------------------------------------------------ */

typedef enum
{
     DATA_WITDH_8N1 = 0      /* 1 start bit, 8 data bits, n stop bits */
    ,DATA_WITDH_9N = 1       /* 1 start bit, 9 data bits, n stop bits */
} data_width_t;

    /** ------------------------------------------------------------------ */

typedef enum
{
     STOP_BIT_1 = 0         /* 1 stop bit */
    ,STOP_BIT_0_5 = 1       /* 0.5 stop bit */
    ,STOP_BIT_2 = 2         /* 2 stop bit */
    ,STOP_BIT_1_5 = 3       /* 1.5 stop bit */
} nb_stop_t;

    /** ------------------------------------------------------------------ */

typedef struct
{
    uint32_t        rate;           /* Data rate in baud */
    data_width_t    data_width;     /* Data width */
    uart_parity_t   parity;         /* Parity */
    nb_stop_t       stop_bit;       /* stop bit */
} uart_config_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
/** without object */


#endif /* D_UART_H */
