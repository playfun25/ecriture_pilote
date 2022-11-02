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
   STM32 GPIO driver data that can be shared by application and basic software.
   Note : See STM32F100xx reference manual ID16188 rev.5 page 111

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_GPIO_H
#define D_GPIO_H

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
  ANALOG_MODE = 0,                  /* 0: Analog mode */
  FLOATING_INPUT = 1,               /* 01: Floating input (reset state) */
  INPUT_WITH_PULLUP = 2,            /* 10: Input with pull-up / pull-down */
  GENERAL_OUTPUT_PUSHPULL = 0,      /* 00: General purpose output push-pull */
  GENERAL_OUTPUT_OPENDRAIN = 1,     /* 01: General purpose output Open-drain */
  ALTERNATE_OUTPUT_PUSHPULL = 2,    /* 10: Alternate function output Push-pull */
  ALTERNATE_OUTPUT_OPENDRAIN = 3    /* 11: Alternate function output Open-drain */
} gpio_cnf_t;

    /**------------------------------------------------------------------ */

/** see reference manual page 111 - CRL - MODEy */

typedef enum
{
  INPUT     = 0,    /* INPUT */
  OUTPUT_10 = 1,    /* OUTPUT 10 Mhz */
  OUTPUT_2  = 2,    /* OUTPUT 2 Mhz */
  OUTPUT_50 = 3,    /* OUTPUT 50 Mhz */
} gpio_mode_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
/** without object */


#endif /* D_GPIO_H */
