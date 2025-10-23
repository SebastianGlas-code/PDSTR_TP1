/**

    TP_sine_table.h

 */



#ifndef _TP_SINE_TABLE_H_
#define _TP_SINE_TABLE_H_


#ifdef __cplusplus
extern "C" {
#endif

// Includes


/* Set EXTERN macro: */
#ifdef _TP_SINE_TABLE_H_IMPORT
	#define EXTERN
#else
	#define EXTERN extern
#endif


// Macros
#define SINE_TABLE_LENGTH 512
#define COSINE_TABLE_SHIFT (SINE_TABLE_LENGTH >> 2)
#define SINE_TABLE_SHIFT 23u

// Types


// Global variables
extern int32_t iq_sine_table [SINE_TABLE_LENGTH];

// Function prototypes




#undef _TP_SINE_TABLE_H_IMPORT
#undef EXTERN


#ifdef __cplusplus
}
#endif // extern "C"

#endif //_TP_SINE_TABLE_H_

//
// End of File
//