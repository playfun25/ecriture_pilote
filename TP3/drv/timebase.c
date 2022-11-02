/* ========================================================================== --
                     copyright, Polytech'Tours, 2014-2014

      Ce logiciel est la propriété de Polytech'Tours. Il ne peut etre ni 
   communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                Polytech'Tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of Polytech'Tours and shall 
       not be disclosed or reproduced without the prior authorization of 
                                Polytech'Tours.

   ==========================================================================
   File: timebase.c

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide functions to manage the timebase of Cortex-M3.
   Note : See ddi0337e_cortex_m3_r1p1 reference manual DDI 0337E page 152 (systick)

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 26.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "drv/timebase-priv.h"
#include <math.h>


/**-------------------------------------------------------------------------- --
   Local constants
-- -------------------------------------------------------------------------- */
#define C_MAX_SYSTICK_VALUE 16777216


/**-------------------------------------------------------------------------- --
   Local macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Local types
-- -------------------------------------------------------------------------- */
uint32_t G_OLD_VALUE = 0; /* old value of timebase_get */
uint32_t G_CPT       = 0; /* absolute time value since the last wait */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Static variables
-- -------------------------------------------------------------------------- */
timebase_dev_t    G_timebase;


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Private functions prototypes
-- -------------------------------------------------------------------------- */

int8_t getPowerOfTwo(int n);


/**========================================================================== --
   Private functions
-- ========================================================================== */

/* -------------------------------------------------------------------------- --
   FUNCTION:
   getPowerOfTwo

   --------------------------------------------------------------------------
   Purpose:
   Find the number of power of two.

   --------------------------------------------------------------------------
   Description:
   This function return 'i' the number of power of two.
     
   --------------------------------------------------------------------------
   Return value:
   'i', the numberof power of two
   -1, the number is not a power of two

-- -------------------------------------------------------------------------- */
int8_t getPowerOfTwo(int n)
{
    /* Local variables */
    uint8_t i = 0;
    
    if( n == 0)
    {
        return 0;
    }
    
    while(n != 1)
    {
        if(n % 2 != 0)
        {
            return -1;
        }
        i++;
        n = n >> 1;
    }
    
    return i;
}


/**========================================================================== --
   Public functions
-- ========================================================================== */

/* -------------------------------------------------------------------------- --
   FUNCTION:
   timebase_init

   --------------------------------------------------------------------------
   Purpose:
   Initialize Cortex-M3 timebase device

   --------------------------------------------------------------------------
   Description:
   This function initializes the timebase 'i_id' in function of parameters.

-- -------------------------------------------------------------------------- */
void timebase_init  
( 
    addr_t i_base_address
   ,uint32_t i_mult
   ,uint32_t i_div 
)
{
    /* Local variables */
    int power_of_two = 0;
    
        /**------------------------------------------------------------------ */
    
    G_timebase.regs = (timebase_t *)i_base_address;
    G_timebase.mult = i_mult;
    G_timebase.div = i_div;
    G_timebase.poweroftwo = 0;
        
        /**------------------------------------------------------------------ */    
    
    power_of_two = getPowerOfTwo(i_div);
    if( (power_of_two > 0) )
    {        
        G_timebase.bitshift = power_of_two;
        G_timebase.poweroftwo = 1;
    }
    else if(i_div == 0)
    {
        G_timebase.div = 1;
    }
    
        /**------------------------------------------------------------------ */
    
    G_timebase.regs->CSR = M_bupdate(G_timebase.regs->CSR, FIELD_CSR_ENABLE, 1);
    G_timebase.regs->CSR = M_bupdate(G_timebase.regs->CSR, FIELD_CSR_CLKSOURCE, 1);
    G_timebase.regs->CSR = M_bupdate(G_timebase.regs->CSR, FIELD_CSR_TICKINT, 0);
    G_timebase.regs->RVR = M_bupdate(G_timebase.regs->RVR, FIELD_RVR_RELOAD, C_MAX_SYSTICK_VALUE-1);
    
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   timebase_wait

   --------------------------------------------------------------------------
   Purpose:
   Initialize Cortex-M3 timebase device

   --------------------------------------------------------------------------
   Description:
   This function wait 'i_udelay' useconds.

-- -------------------------------------------------------------------------- */
void wait 
( 
    uint32_t i_udelay 
)
{
    /* Local variables */
    uint32_t ref = 0;
    uint32_t aim = 0;
    
        /**------------------------------------------------------------------ */
    
    G_CPT   = 0;
    ref     = timebase_get();
    aim     = ref + i_udelay;
    
    while( aim > timebase_get() )
    {
        ;
    }
}


/* -------------------------------------------------------------------------- --
   FUNCTION:
   timebase_wait

   --------------------------------------------------------------------------
   Purpose:
   Initialize Cortex-M3 timebase device

   --------------------------------------------------------------------------
   Description:
   This function wait 'i_udelay' useconds.
   
    --------------------------------------------------------------------------
   Return:
   Current value of systick

-- -------------------------------------------------------------------------- */
uint32_t timebase_get 
( 
    void 
)
{
    /* Local variables */
    uint32_t new_value = 0;
    uint32_t temp = 0;
    
        /**------------------------------------------------------------------ */
    
    new_value = M_bget(G_timebase.regs->CVR, FIELD_CVR_CURRENT); 
    new_value = C_MAX_SYSTICK_VALUE - new_value;
    
    if( G_OLD_VALUE < new_value )
    {
        temp = new_value - G_OLD_VALUE;
    }
    else
    {
        temp = (C_MAX_SYSTICK_VALUE - G_OLD_VALUE) + new_value;
    }
    
        /**------------------------------------------------------------------ */

    if(G_timebase.poweroftwo)
    {
        G_CPT += temp >> G_timebase.bitshift;
    }
    else
    {
        G_CPT += (temp * G_timebase.mult) / G_timebase.div;
    }
     G_OLD_VALUE = new_value;
    
    return G_CPT;
}
