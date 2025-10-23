#include "Link.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Link_Func.h"
#include "board.h"
#include "driverlib.h"
#include "device.h"

// ===== Private RX buffer =====
#ifndef LINK_RX_BUF_SIZE
#define LINK_RX_BUF_SIZE  127u
#endif
#define LINK_ERROR_LEN 14u

uint8_t s_rx_buf[LINK_RX_BUF_SIZE];
unsigned char tx_error[LINK_ERROR_LEN] = "r,000,[],0001";

// ===== Public accessors =====
uint8_t* LINK_RxBufferPtr(void)      { return s_rx_buf; }
size_t   LINK_RxBufferCapacity(void) { return (size_t)LINK_RX_BUF_SIZE; }

// ===== Internal helpers =====

// Convert 8-character hex string to bytes, interpreting as little-endian float/int32.
static inline void hex8_from_u32_be(uint32_t v, char out_hex8[9]) 
{
    static const char H[] = "0123456789ABCDEF";
    uint8_t b3 = (uint8_t)((v >> 24) & 0xFF); // MSB first
    uint8_t b2 = (uint8_t)((v >> 16) & 0xFF);
    uint8_t b1 = (uint8_t)((v >>  8) & 0xFF);
    uint8_t b0 = (uint8_t)((v >>  0) & 0xFF);
    out_hex8[0]=H[b3>>4]; out_hex8[1]=H[b3&0xF];
    out_hex8[2]=H[b2>>4]; out_hex8[3]=H[b2&0xF];
    out_hex8[4]=H[b1>>4]; out_hex8[5]=H[b1&0xF];
    out_hex8[6]=H[b0>>4]; out_hex8[7]=H[b0&0xF];
}

static inline uint32_t hex_to_u32_be(const char* s) 
{
    uint8_t bytes[4];
    for (int i=0;i<4;i++){
        uint8_t hi, lo;
        if (!((s[2*i]>='0'&&s[2*i]<='9')||(s[2*i]>='A'&&s[2*i]<='F')||(s[2*i]>='a'&&s[2*i]<='f'))) return 0;
        if (!((s[2*i+1]>='0'&&s[2*i+1]<='9')||(s[2*i+1]>='A'&&s[2*i+1]<='F')||(s[2*i+1]>='a'&&s[2*i+1]<='f'))) return 0;
        hi = (uint8_t)((s[2*i]  <= '9'? s[2*i]-'0'  : (s[2*i]&~0x20)-'A'+10));
        lo = (uint8_t)((s[2*i+1]<= '9'? s[2*i+1]-'0': (s[2*i+1]&~0x20)-'A'+10));
        bytes[i] = (uint8_t)((hi<<4)|lo);
    }
    uint32_t ret = ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) |
             ((uint32_t)bytes[2] << 8)  | ((uint32_t)bytes[3] << 0);
    return ret;
}

float LINK_HexToFloat(const char* hex_str)
{
    if (!hex_str) return 0.0f;
    uint32_t raw = hex_to_u32_be(hex_str);
    float f;
    memcpy(&f, &raw, sizeof(float));
    return f;
}

int32_t LINK_HexToInt(const char* hex_str)
{
    if (!hex_str) return 0;
    uint32_t raw = hex_to_u32_be(hex_str);
    int32_t i;
    memcpy(&i, &raw, sizeof(int32_t));
    return i;
}

char* LINK_FloatToHex(float value, char hex_str[8])
{
    uint32_t raw;
    memcpy(&raw, &value, sizeof(uint32_t));
    hex8_from_u32_be(raw, hex_str);
    return hex_str;
}

char* LINK_IntToHex(int32_t value, char hex_str[8])
{
    uint32_t raw;
    memcpy(&raw, &value, sizeof(uint32_t));   // two's complement bit copy
    hex8_from_u32_be(raw, hex_str);
    return hex_str;
}

char* LINK_ErrToHex(uint32_t err_code, char* err_str)
{
    if (!err_str) return NULL;
    // Keep only lower 16 bits to stay within 4 hex digits
    unsigned val = (unsigned)(err_code & 0xFFFFu);
    // Format as zero-padded uppercase 4-digit hex
    sprintf(err_str, "%04X", val);
    return err_str;
}

static int is_hex8(const char* s) {
    int ret = isxdigit((unsigned char)s[0]);
    ret += isxdigit((unsigned char)s[1]);
    ret += isxdigit((unsigned char)s[2]);
    ret += isxdigit((unsigned char)s[3]);
    ret += isxdigit((unsigned char)s[4]);
    ret += isxdigit((unsigned char)s[5]);
    ret += isxdigit((unsigned char)s[6]);
    ret += isxdigit((unsigned char)s[7]);
    return ret;
}

static int is_hex4(const char* s) {
    int ret = isxdigit((unsigned char)s[0]);
    ret += isxdigit((unsigned char)s[1]);
    ret += isxdigit((unsigned char)s[2]);
    ret += isxdigit((unsigned char)s[3]);
    ret += isxdigit((unsigned char)s[4]);
    return ret;
}

static const char* parse_uint_dec(const char* p, const char* end, unsigned int* out) {
    if (p >= end || !isdigit((unsigned char)*p)) return NULL;
    unsigned long acc = 0;
    do {
        acc = acc * 10ul + (unsigned long)(*p - '0');
        if (acc > 0xFFFFFFFFul) return NULL;
        ++p;
    } while (p < end && isdigit((unsigned char)*p));
    *out = (unsigned int)acc;
    return p;
}

// ===== Parser =====
// Format:  t,id,[HEX8(,HEX8)*],err
int LINK_ProcessFrame(size_t len, LINK_Msg* out) {
    if (!out) return LINK_ERR_PARSE;
    out->type       = 0u;
    out->id         = 0u;
    out->err        = 0u;       // always 0 initially
    out->data_ptr   = NULL;
    out->data_count = 0u;

    if (len < 21 || len > LINK_RX_BUF_SIZE) return LINK_ERR_PARSE;

    const char* p   = (const char*)s_rx_buf;
    const char* end = (const char*)s_rx_buf + len;

    // 1) t = 'r' | 'w'
    char t = *p++;
    if (!(t == 'r' || t == 'w')) return LINK_ERR_PARSE;
    out->type = (t == 'w') ? LINK_WRITE : LINK_READ;

    // 2) comma
    if (*p != ',') return LINK_ERR_PARSE;
    p++;

    // 3) id (decimal)
    unsigned int id = 0;
    p = parse_uint_dec(p, end, &id); if (!p) return LINK_ERR_PARSE;
    out->id = id;

    // 4) comma
    if (*p != ',') return LINK_ERR_PARSE;
    p++;

    // 5) data: '[' items ']'
    if (*p != '[') return LINK_ERR_PARSE;
    p++;
    out->data_ptr = p;

    while (*p != ']')
    {
        if (!is_hex8(p)) return LINK_ERR_PARSE;
        out->data_count += 1u;
        p += 8;
        if (*p == ']') break;
        if (*p != ',') return LINK_ERR_PARSE;
        p++;
    }
    p++;

    // 6) comma
    if (*p != ',') return LINK_ERR_PARSE;
    p++;
    out->error_ptr = p;

    // 7) err: 4 hex chars (ignored content)
    if (!is_hex4(p)) return LINK_ERR_PARSE;
    p += 4;

    // 8) End of frame
    if (p != end) return LINK_ERR_PARSE;

    return LINK_OK;
}

void INT_UI_UART_ISR(void)
{
    char c = 1;
    unsigned int length = 0;
    uint8_t * buf_ptr = LINK_RxBufferPtr();
    const size_t max_size = LINK_RxBufferCapacity();
    LINK_Msg rx_msg;

    
    while ((c != 0x00) && (length != max_size))
    {
        c = UART_readChar(UI_UART_BASE);
        buf_ptr[length] = c;
        length ++;
    }

    int pr = LINK_ProcessFrame(length-1, &rx_msg);
    
    if (pr != LINK_OK)
    {
        // Parser Error
        UART_writeCharArray(UI_UART_BASE, tx_error, LINK_ERROR_LEN);
    }else 
    {
        // Process packet
        unsigned int error = LINK_Dispatch(&rx_msg);
        LINK_ErrToHex(error, (char*)rx_msg.error_ptr);
        UART_writeCharArray(UI_UART_BASE, buf_ptr, length);
    }

    // Clear UART global interrupt flag
    UART_clearGlobalInterruptFlag(UI_UART_BASE);
}
