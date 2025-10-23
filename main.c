//#############################################################################
//
// FILE:   empty_driverlib_project.c
//
//! \addtogroup driver_example_list/-
//! <h1>Empty Project Example</h1> 
//!
//! This example is an empty project setup for Driverlib development.
//!
//
//#############################################################################
//
//
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//

//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED Tp[]k;O, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//#############################################################################

//
// Included Files
//
#include "board.h"
#include <strings.h>
#include "TP_globals.h"
#include "TP_sine_table.h"
#include "TP_dds.h"


epwm_t EPWM_vars;
cpuTimer1ms_t cpuTimer1ms_Struct;
adc_t ADC_vars;
uint16_t vector_0[VECTOR_LENGTH * VECTOR_COUNT];
uint16_t vector_1[VECTOR_LENGTH * VECTOR_COUNT];


__attribute__((interrupt("INT"))) void INT_ADC_SAMPLE_1_ISR (void);
__attribute__((interrupt("INT"))) void INT_Timer_1ms_ISR(void);
__attribute__((interrupt("INT"))) void INT_ePWM_OUT_ISR(void);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    //
    // Init structures
    //
    bzero((void *) &cpuTimer1ms_Struct, sizeof(cpuTimer1ms_Struct));
    bzero((void *) &ADC_vars, sizeof(ADC_vars));
    ADC_vars.var0.vector = vector_0;
    ADC_vars.var1.vector = vector_1;

    TP_dds_init(&(EPWM_vars.DDS1));
    TP_dds_init(&(EPWM_vars.DDS2));

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();


    while(1)
    {

        if (ADC_vars.var0.ready)
        {
            ADC_vars.var0.ready = 0;
            ADC_vars.var1.ready = 0;

            unsigned long acum0 = 0;
            unsigned long acum1 = 0;
            uint16_t i;

            for(i=ADC_vars.var0.offset; i < (VECTOR_LENGTH + ADC_vars.var0.offset); i++)
            {
                acum0 += ADC_vars.var0.vector[i];
                acum1 += ADC_vars.var1.vector[i];
            }


            const float mean0 = (float)acum0 / (float)VECTOR_LENGTH;
            const float mean1 = (float)acum1 / (float)VECTOR_LENGTH;
            ADC_vars.var0.mean = mean0;
            ADC_vars.var1.mean = mean1;

            acum0 = 0;
            acum1 = 0;

            for(i=ADC_vars.var0.offset; i < (VECTOR_LENGTH + ADC_vars.var0.offset); i++)
            {
                const uint16_t adc0 = ADC_vars.var0.vector[i];
                acum0 += (adc0 - mean0) * (adc0 - mean0);
                const uint16_t adc1 = ADC_vars.var1.vector[i];
                acum1 += (adc1 - mean1) * (adc1 - mean1);
            }

            ADC_vars.var0.variance = (float)acum0 / (float)VECTOR_LENGTH;
            ADC_vars.var1.variance = (float)acum1 / (float)VECTOR_LENGTH;
        }
        
    }
}


void INT_ADC_SAMPLE_1_ISR(void)
{
    ADC_vars.adc_int_counter ++;

    ADC_vars.var0.vector[ADC_vars.var0.index] = ADC_readResult(ADC_SAMPLE_RESULT_BASE, ADC_SOC_NUMBER0);
    ADC_vars.var1.vector[ADC_vars.var1.index] = ADC_readResult(ADC_SAMPLE_RESULT_BASE, ADC_SOC_NUMBER1);

    ADC_vars.var0.index ++;
    ADC_vars.var1.index ++;

    if ( !(ADC_vars.var0.index % VECTOR_LENGTH) )
    {
        ADC_vars.var0.ready = 1;
        ADC_vars.var1.ready = 1;
        ADC_vars.var0.offset = ADC_vars.var0.index - VECTOR_LENGTH;
        ADC_vars.var1.offset = ADC_vars.var1.index - VECTOR_LENGTH;
    }

    ADC_vars.var0.index %= (VECTOR_LENGTH*VECTOR_COUNT);
    ADC_vars.var1.index %= (VECTOR_LENGTH*VECTOR_COUNT);

}

void INT_ePWM_OUT_ISR(void)
{
    EPWM_vars.epwm_int_counter ++;
    const int32_t tbprd = (int32_t)EPWM_getTimeBasePeriod(ePWM_OUT_BASE);
    int32_t var1 = TP_dds_process(&(EPWM_vars.DDS1));
    int32_t var2 = TP_dds_process(&(EPWM_vars.DDS2));

    var1 >>= 14; // convert to IQ16
    var1 *= tbprd; // scale to tbprd
    var1 >>= 16; // convert to integer
    var1 = (var1 > tbprd) ? tbprd : var1;
    var1 = (var1 < 0) ? 0 : var1;

    var2 >>= 14; // convert to IQ16
    var2 *= tbprd; // scale to tbprd
    var2 >>= 16; // convert to integer
    var2 = (var2 > tbprd) ? tbprd : var2;
    var2 = (var2 < 0) ? 0 : var2;

    if(EPWM_vars.DDS_enable)
    {
        EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_A, (uint16_t)var1);
        EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_B, (uint16_t)var2);
    }

    EPWM_clearEventTriggerInterruptFlag(ePWM_OUT_BASE);
}

void INT_Timer_1ms_ISR(void)
{
    cpuTimer1ms_Struct.count++;
    cpuTimer1ms_Struct.led_count ++;

    if(!(cpuTimer1ms_Struct.led_count % 1000))
    {
        cpuTimer1ms_Struct.led_count = 0;
        GPIO_togglePin(myBoardLED1_GPIO);
    }

}

//
// End of File
//
