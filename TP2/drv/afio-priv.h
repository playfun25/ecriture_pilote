/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: afio-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Private data and prototype of STM32 AFIO driver.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_AFIO_PRIV_H
#define D_AFIO_PRIV_H

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
/** see reference manual page 119 */
typedef struct
{
  reg32_t   EVCR;         
  reg32_t   MAPR;
  reg32_t   EXTICR1;
  reg32_t   EXTICR2;
  reg32_t   EXTICR3;
  reg32_t   EXTICR4;
  reg32_t   MAPR2;

} afio_t;        /* AFIO registers */

typedef struct
{
     afio_t * base_address;   
     
} afio_dev_t;    /* AFIO device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
/* without object */

#endif /** D_RCC_PRIV_H */
