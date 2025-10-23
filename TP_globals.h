


#ifndef TP_GLOBALS_H
#define TP_GLOBALS_H

#include "TP_dds.h"

#define VECTOR_LENGTH 256
#define VECTOR_COUNT 2


typedef struct {
    unsigned long long count;
    unsigned long led_count;
} cpuTimer1ms_t;

typedef struct {
    uint16_t * vector;
    uint16_t index;
    uint16_t offset;
    uint16_t ready;
    float mean;
    float variance;
} measVar_t;

typedef struct {
    unsigned long long adc_int_counter;
    volatile measVar_t var0;
    volatile measVar_t var1;
} adc_t;

typedef struct {
    unsigned long epwm_int_counter;
    unsigned int DDS_enable;
    TP_dds_t DDS1;
    TP_dds_t DDS2;

} epwm_t;




extern cpuTimer1ms_t cpuTimer1ms_Struct;
extern adc_t ADC_vars;
extern epwm_t EPWM_vars;
extern uint16_t vector_0[VECTOR_LENGTH * VECTOR_COUNT];
extern uint16_t vector_1[VECTOR_LENGTH * VECTOR_COUNT];

#endif