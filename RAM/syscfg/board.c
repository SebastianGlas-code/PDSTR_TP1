/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules.
// Call this function in your application if you wish to do all module
// initialization.
// If you wish to not use some of the initializations, instead of the
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	PinMux_init();
	PERCONFIG_init();
	ASYSCTL_init();
	INPUTXBAR_init();
	AIO_init();
	GPIO_init();
	CMPSS_init();
	RTDMA1_init();
	RTDMA2_init();
	ADC_init();
	CPUTIMER_init();
	EPWM_init();
	UART_init();
	INTERRUPT_init();
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//

	//
	// ANALOG -> myANALOGPinMux0 Pinmux
	//
	// Analog PinMux for A0/C24/DACA_OUT
	//GPIO_setPinConfig(GPIO_160_AIO160);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(160, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A1/C25
	//GPIO_setPinConfig(GPIO_161_AIO161);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(161, GPIO_ANALOG_ENABLED);
	//
	// EPWM1 -> ePWM_ADC Pinmux
	//
	//
	// EPWM2 -> ePWM_OUT Pinmux
	//
	GPIO_setPinConfig(ePWM_OUT_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_OUT_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_OUT_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(ePWM_OUT_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(ePWM_OUT_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ePWM_OUT_EPWMB_GPIO, GPIO_QUAL_SYNC);


	// GPIO19 -> myBoardLED1_GPIO Pinmux
	GPIO_setPinConfig(GPIO_19_GPIO19);

	// GPIO62 -> myBoardLED2_GPIO Pinmux
	GPIO_setPinConfig(GPIO_62_GPIO62);
	//
	// UARTA -> UI_UART Pinmux
	//
	GPIO_setPinConfig(UI_UART_UARTTX_PIN_CONFIG);
	GPIO_setPadConfig(UI_UART_UARTTX_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(UI_UART_UARTTX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(UI_UART_UARTRX_PIN_CONFIG);
	GPIO_setPadConfig(UI_UART_UARTRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(UI_UART_UARTRX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// Peripheral Configurations
//
//*****************************************************************************
void PERCONFIG_init()
{
	//
	// Configuration for modules assigned to CPU1
	//
    SysCtl_selectCPUForPeripheral(SYSCTL_PERIPH_CONFIG_ADCA, SYSCTL_CPUSEL_CPU1);
    SysCtl_selectFrameForPeripheral(SYSCTL_PERIPH_CONFIG_ADCA, SYSCTL_FRAMESEL_0);
    SysCtl_disableStandbyForPeripheral(SYSCTL_PERIPH_CONFIG_ADCA);
    SysCtl_disableDebugHaltForPeripheral(SYSCTL_PERIPH_CONFIG_ADCA);
    SysCtl_selectCPUForPeripheral(SYSCTL_PERIPH_CONFIG_EPWM1, SYSCTL_CPUSEL_CPU1);
    SysCtl_selectFrameForPeripheral(SYSCTL_PERIPH_CONFIG_EPWM1, SYSCTL_FRAMESEL_0);
    SysCtl_selectCPUForPeripheral(SYSCTL_PERIPH_CONFIG_EPWM2, SYSCTL_CPUSEL_CPU1);
    SysCtl_selectFrameForPeripheral(SYSCTL_PERIPH_CONFIG_EPWM2, SYSCTL_FRAMESEL_0);
    SysCtl_selectCPUForPeripheral(SYSCTL_PERIPH_CONFIG_UARTA, SYSCTL_CPUSEL_CPU1);
    SysCtl_selectFrameForPeripheral(SYSCTL_PERIPH_CONFIG_UARTA, SYSCTL_FRAMESEL_0);

	//
	// Inserting some delay for frame updates to take effect
	//
    SysCtl_delay(100);
}


//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
}



//*****************************************************************************
//
// RTDMA1 MPU Configurations
//
//*****************************************************************************
void RTDMA1_MPU_init(){
}

//*****************************************************************************
//
// RTDMA2 MPU Configurations
//
//*****************************************************************************
void RTDMA2_MPU_init(){
}

//*****************************************************************************
//
// CMPSS Configurations
//
//*****************************************************************************
void CMPSS_init(){
    CMPSS_MUX_config();
}

void CMPSS_MUX_config(){
}


//*****************************************************************************
//
// RTDMA1 Configurations
//
//*****************************************************************************
void RTDMA1_init(){
    RTDMA1_global_init();
    RTDMA1_MPU_init();
}

void RTDMA1_global_init(){
}


//*****************************************************************************
//
// RTDMA2 Configurations
//
//*****************************************************************************
void RTDMA2_init(){
    RTDMA2_global_init();
    RTDMA2_MPU_init();
}

void RTDMA2_global_init(){
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	myBoardLED1_GPIO_init();
	myBoardLED2_GPIO_init();
}

void myBoardLED1_GPIO_init(){
	GPIO_setPadConfig(myBoardLED1_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myBoardLED1_GPIO, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(myBoardLED1_GPIO, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(myBoardLED1_GPIO, GPIO_DIR_MODE_OUT);
}

void myBoardLED2_GPIO_init(){
	GPIO_setPadConfig(myBoardLED2_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myBoardLED2_GPIO, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(myBoardLED2_GPIO, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(myBoardLED2_GPIO, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// AIO Configurations
//
//*****************************************************************************
void AIO_init(){
}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	ADC_SAMPLE_init();
}

void ADC_SAMPLE_init(){
 	// delay depends on analog reference
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the ADC module's offset trim
	//
	// ADC_setOffsetTrimAll(,);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(ADC_SAMPLE_BASE, ADC_CLK_DIV_3_5);
		
	//
	// Configures the analog-to-digital converter resolution and signal mode.
	//
	ADC_setMode(ADC_SAMPLE_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(ADC_SAMPLE_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(ADC_SAMPLE_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(ADC_SAMPLE_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// Disables alternate timings for DMA trigger
	//
	ADC_disableAltDMATiming(ADC_SAMPLE_BASE);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(ADC_SAMPLE_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(ADC_SAMPLE_BASE, ADC_PRI_THRU_SOC1_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 15 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADC_SAMPLE_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 15U);
	ADC_setInterruptSOCTrigger(ADC_SAMPLE_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 15 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(ADC_SAMPLE_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN1, 15U);
	ADC_setInterruptSOCTrigger(ADC_SAMPLE_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_INT_TRIGGER_EOC1
	// 		Interrupt Source: enabled
	//		Continuous Mode	: enabled
	//
	//
	ADC_setInterruptSource(ADC_SAMPLE_BASE, ADC_INT_NUMBER1, ADC_INT_TRIGGER_EOC1);
	ADC_clearInterruptStatus(ADC_SAMPLE_BASE, ADC_INT_NUMBER1);
	ADC_enableContinuousMode(ADC_SAMPLE_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(ADC_SAMPLE_BASE, ADC_INT_NUMBER1);
}


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
	//
	// asysctl initialization
	//
	// Disables the temperature sensor output to the ADC.
	//
	ASysCtl_disableTemperatureSensor();

	//
	// Set the analog voltage reference
	//
	ASysCtl_setVREF(ASYSCTL_VREFHIAB, ASYSCTL_VREF_EXTERNAL);
	ASysCtl_setVREF(ASYSCTL_VREFHICDE, ASYSCTL_VREF_EXTERNAL);
	ASysCtl_selectInternalTestNode(ASYSCTL_TEST_NODE_NO_CONN);


}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	Timer_1ms_init();
}

void Timer_1ms_init(){
	CPUTimer_setEmulationMode(Timer_1ms_BASE, CPUTIMER_EMULATIONMODE_RUNFREE);
	CPUTimer_setPreScaler(Timer_1ms_BASE, 0U);
	CPUTimer_setPeriod(Timer_1ms_BASE, 200000U);
	CPUTimer_enableInterrupt(Timer_1ms_BASE);
	CPUTimer_stopTimer(Timer_1ms_BASE);

	CPUTimer_reloadTimerCounter(Timer_1ms_BASE);
	CPUTimer_startTimer(Timer_1ms_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(ePWM_ADC_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBaseCounterMode(ePWM_ADC_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_setTimeBasePeriod(ePWM_ADC_BASE, 19999);	
    EPWM_setTimeBaseCounter(ePWM_ADC_BASE, 0);	
    EPWM_disablePhaseShiftLoad(ePWM_ADC_BASE);	
    EPWM_setPhaseShift(ePWM_ADC_BASE, 0);	
    EPWM_setCounterCompareValue(ePWM_ADC_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_ADC_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(ePWM_ADC_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_ADC_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_ADC_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_ADC_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_ADC_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_ADC_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_ADC_BASE);	
    EPWM_enableADCTrigger(ePWM_ADC_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(ePWM_ADC_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(ePWM_ADC_BASE, EPWM_SOC_A, 1);	
    EPWM_setEmulationMode(ePWM_OUT_BASE, EPWM_EMULATION_FREE_RUN);	
    EPWM_setClockPrescaler(ePWM_OUT_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBaseCounterMode(ePWM_OUT_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_setTimeBasePeriod(ePWM_OUT_BASE, 255);	
    EPWM_setTimeBaseCounter(ePWM_OUT_BASE, 0);	
    EPWM_disablePhaseShiftLoad(ePWM_OUT_BASE);	
    EPWM_setPhaseShift(ePWM_OUT_BASE, 0);	
    EPWM_setSyncInPulseSource(ePWM_OUT_BASE, EPWM_SYNC_IN_PULSE_SRC_DISABLE);	
    EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_A, 100);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_B, 50);	
    EPWM_setCounterCompareShadowLoadMode(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(ePWM_OUT_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(ePWM_OUT_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(ePWM_OUT_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(ePWM_OUT_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(ePWM_OUT_BASE);	
    EPWM_enableInterrupt(ePWM_OUT_BASE);	
    EPWM_setInterruptSource(ePWM_OUT_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(ePWM_OUT_BASE, 10);	
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	Interrupt_setThreshold(0);
    Interrupt_setGroupMask(0xFF);
    Interrupt_setRTINTSPWarning(15, 0);

	// Interrupt Settings for ADC_SAMPLE1_INT -> INT_ADCA1
	Interrupt_register(ADC_SAMPLE1_INT, &INT_ADC_SAMPLE_1_ISR);
	Interrupt_enable(ADC_SAMPLE1_INT);
	Interrupt_setPriority(ADC_SAMPLE1_INT, 255);
	Interrupt_setContextID(ADC_SAMPLE1_INT, INTERRUPT_CONTEXTID_0);

	// Interrupt Settings for Timer_1ms_INT -> INT_TIMER0
	Interrupt_register(Timer_1ms_INT, &INT_Timer_1ms_ISR);
	Interrupt_enable(Timer_1ms_INT);
	Interrupt_setPriority(Timer_1ms_INT, 255);
	Interrupt_setContextID(Timer_1ms_INT, INTERRUPT_CONTEXTID_0);

	// Interrupt Settings for ePWM_OUT_ET_INT -> INT_EPWM2
	Interrupt_register(ePWM_OUT_ET_INT, &INT_ePWM_OUT_ISR);
	Interrupt_enable(ePWM_OUT_ET_INT);
	Interrupt_setPriority(ePWM_OUT_ET_INT, 255);
	Interrupt_setContextID(ePWM_OUT_ET_INT, INTERRUPT_CONTEXTID_0);

	// Interrupt Settings for UI_UART_UART_INT -> INT_UARTA
	Interrupt_register(UI_UART_UART_INT, &INT_UI_UART_ISR);
	Interrupt_enable(UI_UART_UART_INT);
	Interrupt_setPriority(UI_UART_UART_INT, 255);
	Interrupt_setContextID(UI_UART_UART_INT, INTERRUPT_CONTEXTID_0);
}

//*****************************************************************************
//
// UART Configurations
//
//*****************************************************************************
void UART_init(){
    UI_UART_init();
}

void UI_UART_init(){
        //
        // Set UI_UART baud rate and configuration
        //
        UART_setConfig(
            UI_UART_BASE, // base address
            DEVICE_SYSCLK_FREQ, // UART source clock
            15000000, // baud rate
            (UART_CONFIG_WLEN_8 | // word length
             UART_CONFIG_STOP_ONE) // stop bits
        );
        
        //
        // FIFO enable
        //
        UART_enableFIFO(UI_UART_BASE);

        //
        // FIFO trigger levels
        //
        UART_setFIFOLevel(UI_UART_BASE, UART_FIFO_TX4_8, UART_FIFO_RX7_8);
        
        //
        // Configure interrupts
        //
        UART_clearInterruptStatus(UI_UART_BASE, 0xFFFF);
        UART_enableInterrupt(UI_UART_BASE,
            (UART_INT_RX)
        );
            
        UART_disableLoopback(UI_UART_BASE);
        
        //
        // Enable RX, TX, and the UART.
        //
        UART_enableModuleNonFIFO(UI_UART_BASE);
}

