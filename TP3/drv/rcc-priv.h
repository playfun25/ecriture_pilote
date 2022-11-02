/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: uart-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Private data and prototype of STM32 UART driver.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 28.11.2014 - Authors: Name / Name
   + first version

-- ========================================================================== */

#ifndef D_RCC_PRIV_H
#define D_RCC_PRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */

/** CR [Clock control Register] */
#define FIELD_RCC_CR_PLLRDY     25, 0x1     /* PLL clock ready flag
                                               Set by hardware to indicate that the PLL is locked.
                                               =0: PLL unlocked
                                               =1: PLL locked */
#define FIELD_RCC_CR_PLLON      24, 0x1     /* PLL enable
                                               Set and cleared by software to enable PLL.
                                               Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
                                               PLL clock is used as system clock or is selected to become the system clock.
                                               =0: PLL OFF
                                               =1: PLL ON */
#define FIELD_RCC_CR_CSSON      19, 0x1     /* Clock security system enable
                                               Set and cleared by software to enable the clock security system. When CSSON is set, the
                                               clock detector is enabled by hardware when the HSE oscillator is ready, and disabled by
                                               hardware if an HSE clock failure is detected.
                                               =0: Clock detector OFF
                                               =1: Clock detector ON (Clock detector ON if the HSE oscillator is ready , OFF if not). */
#define FIELD_RCC_CR_HSEBYP     18, 0x1     /* External high-speed clock bypass
                                               Set and cleared by software to bypass the oscillator with an external clock. The external
                                               clock must be enabled with the HSEON bit set, to be used by the device. The HSEBYP bit
                                               can be written only if the HSE oscillator is disabled.
                                               =0: HSE oscillator not bypassed
                                               =1: HSE oscillator oscillator bypassed with external clock */
#define FIELD_RCC_CR_HSERDY     18, 0x1     /* External high-speed clock ready flag
                                               Set by hardware to indicate that the HSE oscillator is stable. This bit needs 6 cycles of the
                                               HSE oscillator clock to go to zero after HSEON is reset.
                                               =0: HSE oscillator not ready
                                               =1: HSE oscillator ready */

/* TO BE CONTINUED */

/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** see reference manual page 77 */
typedef struct
{
  reg32_t   CR;         /* Clock control register */
  reg32_t   CFGR;
  reg32_t   CIR;
  reg32_t   APB2RSTR;
  reg32_t   APB1RSTR;
  reg32_t   AHBENR;
  reg32_t   APB2ENR;
  reg32_t   APB1ENR;
  reg32_t   BDCR;
  reg32_t   CSR;

} rcc_t;        /* RCC registers */

typedef struct
{
     rcc_t * base_address;   
     
} rcc_dev_t;    /* RCC device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int32_t  F_rcc_init     (void);
int32_t  F_rcc_setconfig   (void);


#endif /** D_RCC_PRIV_H */
