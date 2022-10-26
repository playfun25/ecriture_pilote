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
   Note : See STM32F100xx reference manual ID16188 rev.5 page 640

   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 19.10.2022 - Authors: Teddy NIEMEZYK / Guillaume ROPION
   + first version

-- ========================================================================== */

#ifndef D_UART_PRIV_H
#define D_UART_PRIV_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
#include "uart.h"


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
/** see reference manual page 640 */

#ifndef C_UART_NB
#define C_UART_NB           6
#endif

    /** ------------------------------------------------------------------ */

/** see reference manual page 640-642 */
#define FIELD_SR_CTS    9,9
#define FIELD_SR_LBD    8,8
#define FIELD_SR_TXE    7,7
#define FIELD_SR_TC     6,6
#define FIELD_SR_RXNE   5,5
#define FIELD_SR_IDLE   4,4
#define FIELD_SR_ORE    3,3
#define FIELD_SR_NF     2,2
#define FIELD_SR_FE     1,1
#define FIELD_SR_PE     0,0

    /** ------------------------------------------------------------------ */
    
/** see reference manual page 643 */
#define FIELD_DR_DR     8,0


    /** ------------------------------------------------------------------ */
    
/** see reference manual page 643 */
#define FIELD_BRR_DIV_MANTIS        15,4
#define FIELD_BRR_DIV_FRACTION       3,0


    /** ------------------------------------------------------------------ */
    
/** see reference manual page 643-645 */
#define FIELD_CR1_OVER8     15,15
#define FIELD_CR1_UE        13,13
#define FIELD_CR1_M         12,12
#define FIELD_CR1_WAKE      11,11
#define FIELD_CR1_PCE       10,10
#define FIELD_CR1_PS        9,9
#define FIELD_CR1_PEIE      8,8
#define FIELD_CR1_TXEIE     7,7
#define FIELD_CR1_TCIE      6,6
#define FIELD_CR1_RXNEIE    5,5
#define FIELD_CR1_IDLEIE    4,4
#define FIELD_CR1_TE        3,3
#define FIELD_CR1_RE        2,2
#define FIELD_CR1_RWU       1,1
#define FIELD_CR1_SBK       0,0

    /** ------------------------------------------------------------------ */
    
/** see reference manual page 646-647 */
#define FIELD_CR2_LINEN     14,14
#define FIELD_CR2_STOP      13,12
#define FIELD_CR2_CLKEN     11,11
#define FIELD_CR2_CPOL      10,10
#define FIELD_CR2_CPHA      9,9
#define FIELD_CR2_LBCL      8,8
#define FIELD_CR2_LBDIE     6,6
#define FIELD_CR2_LBDL      5,5
#define FIELD_CR2_ADD       3,0

    /** ------------------------------------------------------------------ */
    
/** see reference manual page 647-648 */
#define FIELD_CR3_ONEBTIT   11,11
#define FIELD_CR3_CTSIE     10,10
#define FIELD_CR3_CTSE      9,9
#define FIELD_CR3_RTSE      8,8
#define FIELD_CR3_DMAT      7,7
#define FIELD_CR3_DMAR      6,6
#define FIELD_CR3_SCEN      5,5
#define FIELD_CR3_NACK      4,4
#define FIELD_CR3_HDSEL     3,3
#define FIELD_CR3_IRLP      2,2
#define FIELD_CR3_IREN      1,1
#define FIELD_CR3_EIE       0,0

    /** ------------------------------------------------------------------ */
    
/** see reference manual page 649 */
#define FIELD_GTPR_GT       16,8
#define FIELD_GTPR_PSC      7,0



/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */
/** see reference manual page 650 */
typedef struct
{
  reg32_t   SR;         /* Status register */
  reg32_t   DR;         /* Data register */
  reg32_t   BRR;        /* Baud rate register */
  reg32_t   CR1;        /* Control register 1 */ 
  reg32_t   CR2;        /* Control register 2 */
  reg32_t   CR3;        /* Control register 3 */
  reg32_t   GTPR;       /* Guard time and prescaler register */
} uart_t;   /* UART registers description */

    /** ------------------------------------------------------------------ */

typedef enum
{
     NOT_BLOCKING = 0         /* Not blocking communication */
    ,BLOCKING = 1             /* Blocking communication */
} blocking_t; /* UART function blocking / not blocking */

    /** ------------------------------------------------------------------ */

typedef struct
{
  uart_t *  regs;               /* base adress of registers */
  uint32_t  clock_freq;         /* Clock in hz */
  blocking_t      blocking;     /* default : 0 not blocking communication, > 0 blocking communication  */
} uart_dev_t;   /* UART device data */


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/* -------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
int32_t  uart_init       ( uint32_t i_id, addr_t base_address, uint32_t clock, uint32_t i_blocking );
int32_t  uart_setconfig  ( uint32_t i_id, uart_config_t * i_config );
int32_t  uart_putc       ( uint32_t i_id, uint32_t value );
int32_t  uart_getc       ( uint32_t i_id );
int32_t  uart_write      ( uint32_t i_id, uint8_t* i_data, uint32_t i_size );
int32_t  uart_read       ( uint32_t i_id, uint8_t* i_data, uint32_t i_size );


#endif /* D_UART_PRIV_H */
