#ifndef LINK_H
#define LINK_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LINK_OK         (0)
#define LINK_ERR_PARSE  (1)
#define LINK_ERR_RANGE  (2)
#define LINK_ERR_TYPE   (3)
#define LINK_ERR_MAX_LIM (4)
#define LINK_ERR_MIN_LIM (5)


#define LINK_READ       (0)
#define LINK_WRITE      (1)

// type: 0 = 'r', 1 = 'w'
typedef struct {
    unsigned int type;        // 0=read, 1=write
    unsigned int id;          // decimal ID
    unsigned int err;         // initialized to 0 by parser
    const char*  data_ptr;    // -> first HEX8 token inside [...]
    unsigned int data_count;  // number of tokens in data array
    const char* error_ptr;    // error data pointer
} LINK_Msg;

__attribute__((interrupt("INT"))) void INT_UI_UART_ISR(void);


// Pointer to the library's private RX buffer
uint8_t* LINK_RxBufferPtr(void);

// Capacity of the private RX buffer
size_t   LINK_RxBufferCapacity(void);

// Parse compact frame currently in RX buffer: t,id,[HEX8(,HEX8)*],err
// 'len' = frame length (no NUL). Fills 'out' and returns LINK_OK or error.
int LINK_ProcessFrame(size_t len, LINK_Msg* out);


// Convert 8-character hex string (little-endian bytes) to float (IEEE-754).
// Example: "3F800000" -> 1.0f
float LINK_HexToFloat(const char* hex_str);
// Convert 8-character hex string (little-endian bytes) to signed 32-bit int.
// Example: "01000000" -> 1
int32_t LINK_HexToInt(const char* hex_str);
// ---- Value encoding helpers (wire LE) ----
// Writes 8 uppercase hex chars + NUL into hex_str[8]. Returns hex_str.
char*   LINK_FloatToHex(float value, char hex_str[8]);
char*   LINK_IntToHex(int32_t value, char hex_str[8]);

// Convert unsigned error code (e.g. 0x000A) into 4-char hex string "000A".
// err_str must have space for at least 5 chars (4 digits + '\0').
// Returns err_str.
char* LINK_ErrToHex(uint32_t err_code, char* err_str);

#ifdef __cplusplus
}
#endif

#endif // LINK_H
