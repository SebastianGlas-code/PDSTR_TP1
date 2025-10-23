/**
TP_dds.c

 */

/* Import system headers and application specific headers: */
#include "driverlib.h"
#include "device.h"
#include "TP_sine_table.h"
#include "strings.h"

/* Including my own header for checking by compiler: */
#define _TP_DDS_H_IMPORT
#include "TP_dds.h"



void TP_dds_init(TP_dds_t * p)
{
    bzero((void *)p, sizeof(TP_dds_t));

    p->multiplier = (float)DDS_2_TO_32 / (float)DDS_FREQ;

    TP_dds_setFreq(p, 50.0f);
    TP_dds_setDC(p, 0.5f);
    TP_dds_setMax(p, 0.5f);
    TP_dds_setPhase(p, 0.0f);
}


void TP_dds_setFreq(TP_dds_t * p, float f)
{
    p->frequency = f;
    p->increment = (unsigned long) (f*p->multiplier);
}

void TP_dds_setPhase(TP_dds_t * p, float phase)
{
    p->phase = phase;
    p->phase_shift = phase * (float)DDS_2_TO_32 / 360.0f;
}

void TP_dds_setDC(TP_dds_t * p, float dc)
{
    p->dc = dc;
    p->dc_int = (int32_t)(dc*IQ30_MULT);
}

void TP_dds_setMax(TP_dds_t *p, float max)
{
    p->max = max;
    p->max_int = (int32_t)(max*IQ30_MULT);
}

void TP_dds_resetCount(TP_dds_t * p)
{
    p->counter = 0;
}

int32_t TP_dds_process(TP_dds_t * p)
{
    p->counter += p->increment;
    const unsigned long index = (p->counter + p->phase_shift) >> SINE_TABLE_SHIFT;
    const int32_t ref = iq_sine_table[index];
    p->raw_reference = ref;
    int32_t scaled_ref = IQ30_mpy( ref, p->max_int);
    const int32_t shifted_ref = ((int32_t)scaled_ref + p->dc_int);
    p->reference = shifted_ref;

    return shifted_ref;

}