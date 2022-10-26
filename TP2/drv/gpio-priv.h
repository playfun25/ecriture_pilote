/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: gpio-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   STM32 GPIO driver data and prototype that shall be accessed only by basic 
   software.
   Note : See STM32F100xx reference manual ID16188 rev.5 page 111

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_GPIO_PRIV_H
#define D_GPIO_PRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "gpio.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */

/** see reference manual page 37 */

#ifndef C_GPIO_NB
#define C_GPIO_NB            7
#endif

#ifndef NB_CHANNEL
#define NB_CHANNEL           16
#endif


/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */

/** see reference manual page 111 */

typedef struct
{
  reg32_t   CRL;        /* Port configuration register low */
  reg32_t   CRH;        /* Port configuration register high */
  reg32_t   IDR;        /* Port input data register */
  reg32_t   ODR;        /* Port ouput data register */ 
  reg32_t   BSRR;       /* bit set/reset register */
  reg32_t   BRR;        /* Port bit reset register */
  reg32_t   LCKR;       /* Port configuration lock register */
} gpio_t;       /* GPIO registers description */

    /** ------------------------------------------------------------------ */

typedef struct
{
  gpio_t *  regs;
} gpio_dev_t;   /* GPIO device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int32_t  gpio_init      ( uint32_t i_id, addr_t base_address );
int32_t  gpio_setconfig ( uint32_t i_id, uint32_t i_channel_id, gpio_cnf_t i_cnf, gpio_mode_t i_mode );
int32_t  gpio_write     ( uint32_t i_id, uint32_t i_channel_id, uint32_t value );
int32_t  gpio_read      ( uint32_t i_id, uint32_t i_channel_id );    


#endif /* D_GPIO_PRIV_H */
