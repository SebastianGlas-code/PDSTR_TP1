//#############################################################################
//
// FILE:   device.c
//
// TITLE:  Device setup for examples.
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "device.h"
#include "board.h"
#include "clocktree.h"
#include "driverlib.h"
#ifdef __cplusplus
using std::memcpy;
#endif
#ifdef CMDTOOL
#include "device_cmd.h"
#endif


#ifdef _FLASH
#if (!defined(__CPU2__))
    //
    //  Dummy certificate section which is updated when actual certitifcate is generated
    //  as part of the post build steps
    //
    __attribute__((retain, section("cert"))) const uint8_t certificate[4096U] = {0U};
#endif
#endif





//*****************************************************************************
//
// Function to initialize the device. Primarily initializes system control to a
// known state by disabling the watchdog, setting up the SYSCLKOUT frequency,
// and enabling the clocks to the peripherals.
// To configure these pins as analog pins, use the function GPIO_setAnalogMode
//
// Note : In case XTAL is used as the PLL source, it is recommended to invoke
// the Device_verifyXTAL() before configuring PLL
//
//
//*****************************************************************************
void Device_init(void)
{
    //
    // Disable the watchdog
    //
    SysCtl_disableWatchdog();

    //
    // Errata workaround
    //
    Device_errataWorkaroundNMIVectorFetch();

#ifdef _FLASH
    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    Flash_initModule(DEVICE_FLASH_WAITSTATES);
#endif

    //
    // Initialize system clock
    //
    CLOCK_init();

    //
    // Turn on all peripherals
    //
    Device_enableAllPeripherals();

    //
    // Initialize PIPE and clear PIPE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIPE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
}

//*****************************************************************************
//
// CLOCK Configurations
//
//*****************************************************************************
void CLOCK_init()
{
	bool clkConfigStatus = false;

	//
    // From ClockTree Configurations
	//

	//
    // Set up PLL control and clock dividers
    //
	clkConfigStatus = SysCtl_setClock(SYSCTL_OSCSRC_OSC2, SYSCTL_PLL_ENABLE, SYSCTL_REFDIV_1,
					  SYSCTL_IMULT_40, SYSCTL_ODIV_2, SYSCTL_SYSDIV_1, DCC1_BASE);

    //
    // Check if the clocking of the device is configured correctly.
    // This fails if a missing clock error is detected or if the PLLRAWCLK
    // is not running at its expected rate
    //
    ASSERT(clkConfigStatus);

	//
	// Initialize peripheral clocks
	//
    SysCtl_setEPWMClock(SYSCTL_EPWMCLK_DIV_1);
    if(SYSCTL_MCUCNF1_EMIF1 == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF1) & SYSCTL_MCUCNF1_EMIF1))
    {
        SysCtl_setEMIF1Clock(SYSCTL_EMIFCLK_DIV_2);
    }
    if(SYSCTL_MCUCNF19_LIN_A == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) & SYSCTL_MCUCNF19_LIN_A))
    {
        SysCtl_setLINAClock(SYSCTL_LINCLK_DIV_2);
    }
    if(SYSCTL_MCUCNF19_LIN_B == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF19) & SYSCTL_MCUCNF19_LIN_B))
    {
        SysCtl_setLINBClock(SYSCTL_LINCLK_DIV_2);
    }
    if(SYSCTL_MCUCNF23_ETHERCAT == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF23) & SYSCTL_MCUCNF23_ETHERCAT))
    {
        SysCtl_setECatClock(SYSCTL_ECATCLKOUT_DIV_8, SYSCTL_ECAT_PHYCLK_ENABLE);
    }
    SysCtl_setHSMClock(SYSCTL_HSMCLK_DIV_2);

    if(SYSCTL_MCUCNF10_MCAN_A == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_A))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_A, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }
    if(SYSCTL_MCUCNF10_MCAN_B == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_B))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_B, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }
    if(SYSCTL_MCUCNF10_MCAN_C == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_C))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_C, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }
    if(SYSCTL_MCUCNF10_MCAN_D == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_D))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_D, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }
    if(SYSCTL_MCUCNF10_MCAN_E == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_E))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_E, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }
    if(SYSCTL_MCUCNF10_MCAN_F == (HWREG(DEVCFG_BASE + SYSCTL_O_MCUCNF10) & SYSCTL_MCUCNF10_MCAN_F))
    {
        SysCtl_setMCANClock(SYSCTL_MCAN_F, SYSCTL_MCANCLK_SOURCE_SYS, SYSCTL_MCANCLK_DIV_20);
    }

	//
    // These asserts will check that the #defines for the clock rates in
    // device.h match the actual rates that have been configured. If they do
    // not match, check that the calculations of DEVICE_SYSCLK_FREQ are accurate
    // Some examples will not perform as expected if these are not correct.
    //
	ASSERT(SysCtl_getClock(DEVICE_OSCSRC_FREQ) == DEVICE_SYSCLK_FREQ);
}

//*****************************************************************************
//
// Peripheral Clocks
//
//*****************************************************************************
void PERCLOCK_init(){
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
}

#if (defined(__CPU2__) || defined(__CPU3__))
__attribute__((interrupt("RTINT"), section("nmivector")))
void nmi_vector(void)
{
    Interrupt_NmiStatus nmiStatus;
    //
    //  Clear ESM and EA error flags
    //
    Interrupt_clearEsmEaFlags(&nmiStatus);

    //
    //  Spin forever
    //
    for(;;)
    {
        ;
    }
}
#endif

//*****************************************************************************
//
// Function to turn on all peripherals, enabling reads and writes to the
// peripherals' registers.
//
// Note that to reduce power, unused peripherals should be disabled.
// Use function Sysctl_enablePeripheral function to selectively enable
// peripherals. Eg: Sysctl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER0)
//
//*****************************************************************************


void Device_enableAllPeripherals(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_RTDMA1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_RTDMA2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUTIMER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUXERAD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CPUXDLT);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EMIF1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM11);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM12);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM13);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM14);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM15);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM16);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM17);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM18);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ECAP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EQEP6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SD4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTE);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_UARTF);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPID);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIE);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_I2CB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCAND);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANE);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_MCANF);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCE);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS11);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS12);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DACB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSITXA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSITXB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSITXC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSITXD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSIRXA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSIRXB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSIRXC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_FSIRXD);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_LINB);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_PMBUSA);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ETHERCAT);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL0);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_HRCAL2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPG1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER7);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER8);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER9);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCCHECKER10);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCSEAGGRCPU1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCSEAGGRCPU2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_ADCSEAGGRCPU3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT4);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT5);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SENT6);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_WADI1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_WADI2);
}

//*****************************************************************************
//
// Function to disable pin locks and enable pullups on GPIOs.
//
//*****************************************************************************
void Device_initGPIO(void)
{
    //
    // Disable pin locks.
    //
    GPIO_unlockPortConfig(GPIO_PORT_A, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_B, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_C, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_D, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_F, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_G, 0xFFFFFFFF);
    GPIO_unlockPortConfig(GPIO_PORT_H, 0xFFFFFFFF);
}

//*****************************************************************************
//
// Function to verify the XTAL frequency
// freq is the XTAL frequency in MHz
// The function return true if the the actual XTAL frequency matches with the
// input value
//
// Note that this function assumes that the PLL is not already configured and
// hence uses SysClk freq = 10MHz for DCC calculation
//
//*****************************************************************************
bool Device_verifyXTAL(float freq)
{
    //
    // Use DCC to verify the XTAL frequency using INTOSC2 as reference clock
    //

    //
    // Turn on XTAL and wait for it to power up using X1CNT
    //
    SysCtl_turnOnXTAL();
    SysCtl_clearExternalOscCounterValue();
    while(SysCtl_getExternalOscCounterValue() != SYSCTL_X1CNT_X1CNT_M);

    //
    // Enable DCC1 clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_DCC1);

    //
    // Insert atleast 5 cycles delay after enabling the peripheral clock
    //
    NOP;
    NOP; 
    NOP;     
    NOP;    
    NOP;
    
    //
    // Configures XTAL as CLKSRC0 and INTOSC2 as CLKSRC1
    // Fclk0 = XTAL frequency (input parameter)
    // Fclk1 = INTOSC2 frequency = 10MHz
    //
    // Configuring DCC error tolerance of +/-1%
    // INTOSC2 can have a variance in frequency of +/-10%
    //
    // Assuming PLL is not already configured, SysClk freq = 10MHz
    //
    // Note : Update the tolerance and INTOSC2 frequency variance as necessary.
    //
    return (DCC_verifyClockFrequency(DCC1_BASE,
                                     DCC_COUNT1SRC_INTOSC2, 10.0F,
                                     DCC_COUNT0SRC_XTAL, freq,
                                     1.0F, 10.0F, 10.0F));

}

//*****************************************************************************
//
// An equivalent function of copy_in (temporary)
//
//*****************************************************************************
void Device_copy_in(COPY_TABLE *tp)
{
   unsigned short i;

   for (i = 0; i < tp->num_recs; i++)
   {
      COPY_RECORD crp = tp->recs[i];
      char *load_addr = (char*)crp.load_addr;
      char *run_addr = (char *)crp.run_addr;

      if (crp.size)
      {
         /*------------------------------------------------------------------*/
         /* Copy record has a non-zero size so the data is not compressed.   */
         /* Just copy the data.                                              */
         /*------------------------------------------------------------------*/
         memcpy(run_addr, load_addr, crp.size);
      }
   }
}

#if ((!defined(__CPU2__)) && (!defined(__CPU3__)))
//*****************************************************************************
//
// Function to boot CPU2
//
//*****************************************************************************
void Device_bootCPU2(COPY_TABLE *copyTable, uint32_t reset_vector,
                     SSU_Link link)
{
#ifdef _FLASH
    //
    // Copy the CPU2 application code from FLASH to CPU2 RAM
    // The copyTable is created by the linker. Please see the CPU2 linker
    // command file for its definition.
    //
    Device_copy_in(copyTable);
#endif //FLASH

    //
    // Set the address and link to which CPU2 Boots
    //
    SSU_configBootAddress(SSU_CPU2, reset_vector, link);

    //
    // Bring CPU2 out of reset. Wait for CPU2 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU2, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU2Reset() == 0x1U);
}

//*****************************************************************************
//
// Function to boot CPU3
//
//*****************************************************************************
void Device_bootCPU3(COPY_TABLE *copyTable, uint32_t reset_vector,
                     SSU_Link link)
{
#ifdef _FLASH
    //
    // When CPU3 does not have dedicated FLASH region, copy the CPU3
    // application code from CPU1 FLASH to CPU3 RAM.
    // The copyTable is created by the linker. Please see the CPU3 linker
    // command file for its definition.
    //
    if(copyTable != 0U)
    {
        Device_copy_in(copyTable);
    }
#endif //FLASH

    //
    // Set the address and link to which CPU3 Boots
    //
    SSU_configBootAddress(SSU_CPU3, reset_vector, link);

    //
    // Bring CPU3 out of reset. Wait for CPU3 to go out of reset.
    //
    SSU_controlCPUReset(SSU_CPU3, SSU_CORE_RESET_DEACTIVE);
    while(SysCtl_isCPU3Reset() == 0x1U);
}
#endif


//*****************************************************************************
//!
//! Errata Workaround for System: Pending Misaligned Reads in the
//! Pipeline After CPU Goes to Fault State Preventing NMI Vector Fetch.
//!
//*****************************************************************************
void Device_errataWorkaroundNMIVectorFetch()
{
    ESM_triggerSoftReset(ESMCPU1_BASE);
    ESM_triggerSoftReset(ESMSYSTEM_BASE);

    // Enable the global interrupt for SYSESM
    ESM_enableGlobal(ESMSYSTEM_BASE);

    // Enable group 0 errors to generate low priority Interrupt (GEN EVT)
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_INTR_EN_SET(0U)) |= 0x3FU;
    HWREG(ESMSYSTEM_BASE + ESM_SYS_O_INT_PRIO(0U)) &= ~(0x3FU);

    // Route ESM SYS GEN EVENT to EPWMXBAR TRIP signal
    XBAR_selectEpwmXbarInputSource(XBAR_TRIP1, XBAR_EPWM_ESM_GEN_EVENT);

    // Configuring SEC3 in START STOP mode, counting SYSCLK. StartInp = EPWMXBAR1 event, StopInp = SEC3 event
    ERAD_Counter_Config counter_params;
    ERAD_setCounterOwnership(ERAD_COUNTER3, ERAD_OWNER_APPLICATION);
    ERAD_disableCounterModule(ERAD_COUNTER3);
    counter_params.enable_stop = false;
    counter_params.enable_int = true;
    counter_params.enable_nmi = true;
    counter_params.event = ERAD_EVENT_NO_EVENT;
	counter_params.event_mode = ERAD_COUNTER_MODE_RISING_EDGE;
    counter_params.rst_on_match = true;
    counter_params.reference = 0x32U;
    ERAD_configCounterInStartStopMode(ERAD_COUNTER3, &counter_params, ERAD_EVENT_EPWMXBAR_OUT1, ERAD_EVENT_COUNTER3_EVENT);
	ERAD_enableCounterModule(ERAD_COUNTER3);

    // Configure CPU1_ESM to generate an NMI on CPU1_ERAD_NMI event
    ESM_enableGlobal(ESMCPU1_BASE);
    ESM_setInterruptPriorityLevel(ESMCPU1_BASE, ESM_EVENT_CPU1_ERAD_NMI, ESM_INTERRUPT_PRIORITY_LEVEL_HIGH);
    ESM_enableInterrupt(ESMCPU1_BASE, ESM_EVENT_CPU1_ERAD_NMI);

    // Disable group 0 NMI generation in CPU1 ESM
    HWREG(ESMCPU1_BASE + ESM_CPU_O_INTR_EN_CLR(0U)) |= 0x3FU;
}

//*****************************************************************************
//
// Error handling function to be called when an ASSERT is violated
// Declared as weak, user may redefine the function in the application.
//
//*****************************************************************************
__attribute((weak, section(".text.error")))
void __error__(const char *filename, uint32_t line)
{
    //
    // An ASSERT condition was evaluated as false. You can use the filename and
    // line parameters to determine what went wrong.
    //
    ESTOP0;
}