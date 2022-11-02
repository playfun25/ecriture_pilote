/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: timebase-priv.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Timebase data and prototypes that shall be accessed only by basic software.

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 26.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_TIMEBASE_PRIV_H
#define D_TIMEBASE_PRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "types.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */

#define FIELD_CSR_COUNT     16,16  
#define FIELD_CSR_CLKSOURCE 2,2
#define FIELD_CSR_TICKINT   1,1
#define FIELD_CSR_ENABLE    0,0

    /** ------------------------------------------------------------------ */

#define FIELD_RVR_RELOAD    23,0


    /** ------------------------------------------------------------------ */

#define FIELD_CVR_CURRENT  23,0

    /** ------------------------------------------------------------------ */

#define FIELD_CALVR_NOREF   31,31
#define FIELD_CALVR_SKEW    30,30
#define FIELD_CALVR_TENMS   23,0


/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** see reference manual page 152 */

typedef struct
{
  reg32_t   CSR;        /* Control status register */
  reg32_t   RVR;        /* Reload value register*/
  reg32_t   CVR;        /* Current value register */
  reg32_t   CALVR;      /* Calibration value register */
} timebase_t;   /* timebase registers description */
    
    /** ------------------------------------------------------------------ */    

typedef struct
{
  timebase_t *  regs;        /* base adress of registers */
  uint32_t      mult;
  uint32_t      div;
  uint32_t      bitshift;
  uint32_t      poweroftwo;
} timebase_dev_t;   /* timebase device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
void      timebase_init  ( addr_t i_base_address, uint32_t i_mult, uint32_t i_div );
uint32_t  timebase_get   ( void );
void      wait           ( uint32_t i_udelay );


#endif /* D_TIMEBASE_PRIV_H */
