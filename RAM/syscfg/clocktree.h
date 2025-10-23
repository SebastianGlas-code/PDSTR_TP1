//#############################################################################
//
// FILE:   clockTree.h
//
// TITLE:  Setups device clocking for examples.
//
//#############################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef CLOCKTREE_H
#define CLOCKTREE_H

//*****************************************************************************
//
// Summary of SYSPLL related clock configuration
//
//*****************************************************************************
//
#define DEVICE_INTOSC2_FREQ  	10000000
#define DEVICE_INTOSC1_FREQ  	10000000
#define DEVICE_AUXCLKIN_FREQ	20000000
#define DEVICE_PLLRAW_FREQ   	200000000

// SYSPLL ENABLED
#define DEVICE_SYSCLK_FREQ		200000000
#define DEVICE_OSCSRC_FREQ		10000000

#define DEVICE_EPWM_FREQ     	200000000
#define DEVICE_EMIF1_FREQ     	100000000
#define DEVICE_LINA_FREQ     	100000000
#define DEVICE_LINB_FREQ     	100000000
#define DEVICE_ECAT_FREQ     	25000000
#define DEVICE_HSM_FREQ     	100000000

#define DEVICE_MCANA_FREQ		10000000
#define DEVICE_MCANB_FREQ		10000000
#define DEVICE_MCANC_FREQ		10000000
#define DEVICE_MCAND_FREQ		10000000
#define DEVICE_MCANE_FREQ		10000000
#define DEVICE_MCANF_FREQ		10000000



															 		


//*****************************************************************************
//
// CPU1 CPUCLK Domain (200 MHz)
//
//*****************************************************************************
// in
//

//*****************************************************************************
//
// CPU2 CPUCLK Domain (200 MHz)
//
//*****************************************************************************
// in
//

//*****************************************************************************
//
// CPU3 CPUCLK Domain (200 MHz)
//
//*****************************************************************************
// in
//
//*****************************************************************************
//
// PLLSYSCLK Domain (200 MHz) 
//
//*****************************************************************************
// GPIOs
// IPC
// ESM
// XBAR
// RTDMAx
// FRIx
// LCM
// PeripheralBridges
// LPxRAMs
// M0RAM
// LDxRAMs
// CPxRAMs
// CDxRAMs
// SystemControl
// PIPEx
// SSU
// HRCAL
// HRPWM
// CPUTIMERx
// DLT
// FLC1
// FLC2
// ERAD
// XINT
//
//*****************************************************************************
//
// Gated Peripheral SYSCLK Domain (200 MHz) 
//
//*****************************************************************************
// ECAP
// EQEP
// EPG
// SDFM
// SENT
// WADI
// CLB
// CMPSS
// ADC
// DAC
// SPI
// PMBUS
// UART
// FSI
// I2C
//
//*****************************************************************************
//
// HSM Domain (100 MHz) 
//
//*****************************************************************************
// FLC0
// HSM
//
//*****************************************************************************
//
// EPWM Domain (200 MHz) 
//
//*****************************************************************************
// EPWM
//
//*****************************************************************************
//
// MCANA Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// MCANB Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// MCANC Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// MCAND Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// MCANE Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// MCANF Domain (10 MHz) 
//
//*****************************************************************************
// MCAN
//
//*****************************************************************************
//
//*****************************************************************************
//
// LINA Domain (100 MHz) 
//
//*****************************************************************************
// LIN
//
//*****************************************************************************
//
// LINB Domain (100 MHz) 
//
//*****************************************************************************
// LIN
//
//*****************************************************************************
//
// Ethercat Domain (25 MHz) 
//
//*****************************************************************************
// EtherCAT
//
//*****************************************************************************
//
// EMIF Domain (100 MHz) 
//
//*****************************************************************************
// EMIF1
//
//*****************************************************************************
//
// Watchdog Domain (10 MHz) 
//
//*****************************************************************************
// WDCLK
#endif // CLOCKTREE_H
