#include "Link_Func.h"
#include "board.h"
#include "driverlib.h"
#include "device.h"
#include "TP_globals.h"

unsigned int data100 [3] ;

unsigned int LINK_Dispatch(const LINK_Msg* msg)
{
    unsigned int error = LINK_OK;

    switch (msg->id)
    {
        case 100:
            return LINK_F_100(msg);
        case 101:
            return LINK_F_101(msg);
        case 102:
            return LINK_F_102(msg);
        case 103:
            return LINK_F_103(msg);
        case 104:
            return LINK_F_104(msg);

        default:
            return LINK_ERR_RANGE; // unknown ID
    }
}

// LEDs function
unsigned int LINK_F_100(const LINK_Msg* msg)
{
    if (msg->type == LINK_WRITE)
    {
        const unsigned int tbprd = LINK_HexToInt((char*)msg->data_ptr);
        const unsigned int compa = LINK_HexToInt((char*)msg->data_ptr+9);
        const unsigned int compb = LINK_HexToInt((char*)msg->data_ptr+18);
        if ((tbprd > 0xFFFF) || (compa > 0xFFFF) || (compb > 0xFFFF))
            return LINK_ERR_MAX_LIM;
        EPWM_setTimeBasePeriod(ePWM_OUT_BASE, tbprd);
        EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_A, compa);
        EPWM_setCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_B, compb);
    } else 
    {
        LINK_IntToHex(EPWM_getTimeBasePeriod(ePWM_OUT_BASE), (char*)msg->data_ptr);
        LINK_IntToHex(EPWM_getCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_A), (char*)msg->data_ptr+9);
        LINK_IntToHex(EPWM_getCounterCompareValue(ePWM_OUT_BASE, EPWM_COUNTER_COMPARE_B), (char*)msg->data_ptr+18);
    }
    return LINK_OK;
}

unsigned int LINK_F_101(const LINK_Msg* msg)
{
    if (msg->type == LINK_WRITE)
    {
        return LINK_ERR_TYPE;
    } else 
    {
        LINK_FloatToHex(ADC_vars.var0.mean, (char*)msg->data_ptr);
        LINK_FloatToHex(ADC_vars.var0.variance, (char*)msg->data_ptr + 9);
        LINK_FloatToHex(ADC_vars.var1.mean, (char*)msg->data_ptr + 18);
        LINK_FloatToHex(ADC_vars.var1.variance, (char*)msg->data_ptr + 27);

    }
    return LINK_OK;
}

unsigned int LINK_F_102(const LINK_Msg* msg)
{
    if (msg->type == LINK_WRITE)
    {
        const float freq = LINK_HexToFloat((char*)msg->data_ptr);
        const float phase = LINK_HexToFloat((char*)msg->data_ptr + 9);
        const float dc = LINK_HexToFloat((char*)msg->data_ptr + 18);
        const float max = LINK_HexToFloat((char*)msg->data_ptr + 27);

        TP_dds_setFreq(&(EPWM_vars.DDS1), freq);
        TP_dds_setPhase(&(EPWM_vars.DDS1), phase);
        TP_dds_setDC(&(EPWM_vars.DDS1), dc);
        TP_dds_setMax(&(EPWM_vars.DDS1), max);
        
    } else 
    {
        LINK_FloatToHex(EPWM_vars.DDS1.frequency, (char*)msg->data_ptr);
        LINK_FloatToHex(EPWM_vars.DDS1.phase, (char*)msg->data_ptr + 9);
        LINK_FloatToHex(EPWM_vars.DDS1.dc, (char*)msg->data_ptr + 18);
        LINK_FloatToHex(EPWM_vars.DDS1.max, (char*)msg->data_ptr + 27);
    }
    return LINK_OK;
}

unsigned int LINK_F_103(const LINK_Msg* msg)
{
    if (msg->type == LINK_WRITE)
    {
        const float freq = LINK_HexToFloat((char*)msg->data_ptr);
        const float phase = LINK_HexToFloat((char*)msg->data_ptr + 9);
        const float dc = LINK_HexToFloat((char*)msg->data_ptr + 18);
        const float max = LINK_HexToFloat((char*)msg->data_ptr + 27);

        TP_dds_setFreq(&(EPWM_vars.DDS2), freq);
        TP_dds_setPhase(&(EPWM_vars.DDS2), phase);
        TP_dds_setDC(&(EPWM_vars.DDS2), dc);
        TP_dds_setMax(&(EPWM_vars.DDS2), max);
        
    } else 
    {
        LINK_FloatToHex(EPWM_vars.DDS2.frequency, (char*)msg->data_ptr);
        LINK_FloatToHex(EPWM_vars.DDS2.phase, (char*)msg->data_ptr + 9);
        LINK_FloatToHex(EPWM_vars.DDS2.dc, (char*)msg->data_ptr + 18);
        LINK_FloatToHex(EPWM_vars.DDS2.max, (char*)msg->data_ptr + 27);
    }
    return LINK_OK;
}


unsigned int LINK_F_104(const LINK_Msg* msg)
{
    if (msg->type == LINK_WRITE)
    {
        const unsigned int button = LINK_HexToInt((char*)msg->data_ptr);
        EPWM_vars.DDS_enable = button;

        TP_dds_resetCount(&(EPWM_vars.DDS1));
        TP_dds_resetCount(&(EPWM_vars.DDS2));

    } else
    {

    }
    return LINK_OK;
}

