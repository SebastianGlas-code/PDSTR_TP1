/**

    TP_dds.h

 */

#ifndef _TP_DDS_H_
#define _TP_DDS_H_


#ifdef __cplusplus
extern "C" {
#endif


// Includes
#include <stdint.h>
#include <limits.h>

/* Set EXTERN macro: */
#ifdef _TP_DDS_H_IMPORT
	#define EXTERN
#else
	#define EXTERN extern
#endif


// Macros
#define DDS_2_TO_32 (0x100000000)
#define DDS_FREQ (78125)

#define IQ30_MULT 1073741824
#define IQ30_DIV 9.313225746154785e-10

// Types

typedef struct {
    float max;
    float dc;
    float frequency;
    float phase;

    unsigned long increment;
    float multiplier;
    unsigned long phase_shift;

    unsigned long counter;

    int32_t raw_reference;
    int32_t reference;
    int32_t dc_int;
    int32_t max_int;

} TP_dds_t;

// Global variables


// Function prototypes
EXTERN void TP_dds_init(TP_dds_t * p);

EXTERN void TP_dds_setFreq(TP_dds_t * p, float f);
EXTERN void TP_dds_setPhase(TP_dds_t * p, float phase);
EXTERN void TP_dds_setDC(TP_dds_t * p, float dc);
EXTERN void TP_dds_setMax(TP_dds_t *p, float max);
EXTERN void TP_dds_resetCount(TP_dds_t * p);
EXTERN int32_t TP_dds_process(TP_dds_t * p);


static inline int32_t IQ30_mpy( int32_t a, int32_t b)
{
    int64_t p = (int64_t)a * (int64_t)b;
    p >>= 30;
    return p;
}
static inline int32_t IQ30_from_flt(float x)
{
    if(x>=1.9999999990686774) return INT32_MAX;
    if(x<= -2.0) return INT32_MIN;
    return (int32_t) (x * (float)(1<<30));
}
static inline float IQ30_to_flt(int32_t x)
{
    return (float)x / (float)(1<<30);
}


#undef _TP_DDS_H_IMPORT
#undef EXTERN


#ifdef __cplusplus
}
#endif // extern "C"

#endif //_TP_DDS_H_

//
// End of File
//