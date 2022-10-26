/* ========================================================================== --
                       copyright, MBDA France, 2015-2015

       Ce code source est la propriété de polytech'tours. Il ne peut être ni 
    communiqué à des tiers ni utilisé sans autorisation préalable écrite de 
                  polytech'tours. Son contenu ne peut être divulgué.

   This source code contained herein is property of polytech'tours and shall not 
   be disclosed or reproduced without the prior authorization of polytech'tours.

   ==========================================================================
   File: types.h

   ==========================================================================
   Functional description:
   --------------------------------------------------------------------------
   Provide the atomic type and the macros to manage bitfield but also the
   macros M_abs, M_fabs, M_min, M_max.
  
   ==========================================================================
   History:
   --------------------------------------------------------------------------
   Date: 07.09.2015 - Author: Philippe Lamaty / Christopher Brossier
   + first version

-- ========================================================================== */

#ifndef D_TYPES_H
#define D_TYPES_H

/**-------------------------------------------------------------------------- --
   Include header files
-- -------------------------------------------------------------------------- */
/* without object */


/**-------------------------------------------------------------------------- --
   Constants
-- -------------------------------------------------------------------------- */
#define C_NULL  0
#define NULL    0

#define TRUE    1
#define FALSE   0


/**-------------------------------------------------------------------------- --
   Macros
-- -------------------------------------------------------------------------- */

/* Return the 64-bits value at address 'a' coded in big-endian */
#define M_get64be(a)        ( (TYP_U64)(((uint8_t *)a)[0]) << 56 \
                            | (TYP_U64)(((uint8_t *)a)[1]) << 48 \
                            | (TYP_U64)(((uint8_t *)a)[2]) << 40 \
                            | (TYP_U64)(((uint8_t *)a)[3]) << 32 \
                            | (TYP_U64)(((uint8_t *)a)[4]) << 24 \
                            | (TYP_U64)(((uint8_t *)a)[5]) << 16 \
                            | (TYP_U64)(((uint8_t *)a)[6]) <<  8 \
                            | (TYP_U64)(((uint8_t *)a)[7])       \
                            )

/* Return the 64-bits value at address 'a' coded in big-endian */
#define M_set64be(a,v)      ((uint8_t *)a)[0] = (uint8_t)((v) >> 56); \
                            ((uint8_t *)a)[1] = (uint8_t)((v) >> 48); \
                            ((uint8_t *)a)[2] = (uint8_t)((v) >> 40); \
                            ((uint8_t *)a)[3] = (uint8_t)((v) >> 32); \
                            ((uint8_t *)a)[4] = (uint8_t)((v) >> 24); \
                            ((uint8_t *)a)[5] = (uint8_t)((v) >> 16); \
                            ((uint8_t *)a)[6] = (uint8_t)((v) >> 8); \
                            ((uint8_t *)a)[7] = (uint8_t)(v)
						  
/* Return the 32-bits value at address 'a' coded in big-endian */
#define M_get32be(a)        ( (uint32_t)(((uint8_t *)a)[0]) << 24 \
                            | (uint32_t)(((uint8_t *)a)[1]) << 16 \
                            | (uint32_t)(((uint8_t *)a)[2]) <<  8 \
                            | (uint32_t)(((uint8_t *)a)[3])       \
                            )

/* Return the 16-bits value at address 'a' coded in big-endian */
#define M_get16be(a)        ( (uint16_t)(((uint8_t *)a)[0]) << 8 \
                            | (uint16_t)(((uint8_t *)a)[1])      \
                            )

/* Return the 32-bits value at address 'a' coded in big-endian */
#define M_set32be(a,v)      ((uint8_t *)a)[0] = (uint8_t)((v) >> 24); \
                            ((uint8_t *)a)[1] = (uint8_t)((v) >> 16); \
                            ((uint8_t *)a)[2] = (uint8_t)((v) >> 8); \
                            ((uint8_t *)a)[3] = (uint8_t)(v)

/* Set the 16-bits value at address 'a' coded in big-endian */
#define M_set16be(a,v)      ((uint8_t *)a)[0] = (uint8_t)((v) >> 8); \
                            ((uint8_t *)a)[1] = (uint8_t)(v)

    /**------------------------------------------------------------------ */

/* return the byte swapping of a 16-bit data */
#define M_swap16(a)         (uint16_t)( (((uint32_t)(a) >> 8) & 0x00ff) | (((uint32_t)(a) << 8) & 0xff00) )

/* return the byte swapping of a 32-bit data */
#define M_swap32(a)         ( ((a) >> 24) \
                            |(((a) >> 8) & 0x0000ff00) \
                            |(((a) << 8) & 0x00ff0000) \
                            | ((a) << 24) \
                            )

    /**------------------------------------------------------------------ */

/* return absolute value of integer */
#define M_abs(a)            ((a) < 0   ? -(a) : (a))

/* return absolute value of real */
#define M_fabs(a)           ((a) < 0.0 ? -(a) : (a))

/* return maximal value */
#define M_max(a,b)          ((a) > (b) ?  (a) : (b))

/* return minimal value */
#define M_min(a,b)          ((a) > (b) ?  (b) : (a))

    /**------------------------------------------------------------------ */

/* Set to 'value' the field defined by 'lsb' and 'msb' */
#define M_field_set(msb, lsb, value)            (((value) << (lsb)) & ((1u << ((msb) + 1u)) - 1u))

/* Return the field defined from 'lsb' to 'msb' of 'value' */
#define M_field_get(value, msb, lsb)            (((value) & ((1u << ((msb) + 1u)) - 1u)) >> (lsb))

/* Clear the field define by 'offset' and 'msk' of 'value' */
#define M_field_clear(value, msb, lsb)          ((value) & (((~0u) << (msb+1)) | ((1<<(lsb))-1) ))

/* Update in 'reg' the field défined by 'offset' and 'msk' to 'value' */
#define M_field_update(reg, msb, lsb, value)    (M_field_clear(reg, msb, lsb) | M_field_set(msb, lsb, value))

    /**------------------------------------------------------------------ */

/**Note: The following macros, prefixed by a 'b', are intermediate macros
         that call the previous macros with a paramter field, where 
         field = (offset, msk). */
/**Note: This redefinition of bit fields avoids the problems related to 
         little/big endian, and insure the portability. */

/**The bitfields can be defined with "define" keyword with a syntax a similar
   to C standard bitfield.

   example:

        typedef struct
        {
          TYP_FIELD32 Day   :  5;
          TYP_FIELD32 Month :  4;
          TYP_FIELD32 Year  : 23;

        } TYP_DATE;  // calendar date

   becomes:
        #define FIELD_DATE_DAY       31,27
        #define FIELD_DATE_MONTH     26,23
        #define FIELD_DATE_YEAR      22,0
*/

/* Set to 'value' the field 'field' [=(offset, mask)] */
#define M_bset(field, value)            M_field_set(field, value)

/* Return the value of field 'field' [=(offset, mask)] of 'reg' */
#define M_bget(value, field)            M_field_get(value, field)

/* Update to 'value' the field 'field' of 'reg' */
#define M_bupdate(reg, field, value)    M_field_update(reg, field, value)

/* Update to 'value' the field 'field' of 'reg' with cast on 1 byte */
#define M_bupdate8(reg, field, value)   (reg) = (uint8_t)M_field_update(reg, field, value)

/* Update to 'value' the field 'field' of 'reg' with cast on 2 bytes */
#define M_bupdate16(reg, field, value)  (reg) = (uint16_t)M_field_update(reg, field, value)

/* Update to 'value' the field 'field' of 'reg' with cast on 4 bytes */
#define M_bupdate32(reg, field, value)  (reg) = (uint32_t)M_field_update(reg, field, value)

    /**------------------------------------------------------------------ */

#define M_errno(error)

#define M_bool2int(v)                   ( (v) == FALSE ?     0 : 1    )
#define M_int2bool(v)                   ( (v) == 0     ? FALSE : TRUE )

#ifndef D_RTRT
#define M_loop()                        for(;;)
#define M_forceVariableUse(v)           if((v))
#else
#define M_loop()
#define M_forceVariableUse(v)
#endif


/**-------------------------------------------------------------------------- --
   Types
-- -------------------------------------------------------------------------- */

/* define a signed integer value on 1 byte */
typedef signed char         int8_t;

/* define a unsigned integer value on 1 byte */
typedef unsigned char       uint8_t;

/* define a signed integer value on 2 bytes */
typedef signed short        int16_t;

/* define a unsigned integer value on 2 bytes */
typedef unsigned short      uint16_t;

/* define a signed integer value on 4 bytes */
typedef signed long         int32_t;

/* define a unsigned integer value on 4 bytes */
typedef unsigned long       uint32_t;

/* define a signed integer value on 8 bytes */
typedef signed long long    int64_t;

/* define a unsigned integer value on 8 bytes */
typedef unsigned long long  uint64_t;

    /**------------------------------------------------------------------ */

/* define a float value on 4 bytes (simple precision) */
typedef float               float32_t;

/* define a float value on 8 bytes (double precision) */
typedef double              float64_t;

    /**------------------------------------------------------------------ */

/* define a register value on 8 bits */
typedef volatile uint8_t    reg8_t;

/* define a register value on 16 bits */
typedef volatile uint16_t   reg16_t;

/* define a register value on 32 bits */
typedef volatile uint32_t   reg32_t;

    /**------------------------------------------------------------------ */

typedef void                (*pfct_t)( int32_t );   /* pointer on function */

    /**------------------------------------------------------------------ */

typedef uint32_t            addr_t;                 /* type address of 32 bits */

    /**------------------------------------------------------------------ */

typedef uint8_t             bool_t;

    /**------------------------------------------------------------------ */

typedef enum
{
  BIT_UNEXECUTED = 0
 ,BIT_FAILED     = 1
 ,BIT_SUCCESSFUL = 3
  
} bit_t;

    /**------------------------------------------------------------------ */

typedef enum
{
  NONE  = 0
 ,ODD   = 1
 ,EVEN  = 2
  
} parity_t;


/**-------------------------------------------------------------------------- --
   External variables (globals)
-- -------------------------------------------------------------------------- */
/** without object */


/**-------------------------------------------------------------------------- --
   Function prototypes
-- -------------------------------------------------------------------------- */
/** without object */


#endif /** D_TYPES_H */

