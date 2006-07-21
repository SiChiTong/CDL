//========================================================================
/** @type     C/C++ Header File
 *  @file     sha512.h
 *  @author   acornejo
 *  @date
 *   Created:       12:54:30 21/07/2006
 *   Last Update:   13:14:58 21/07/2006
 */
//========================================================================

#ifndef __SHA512_H__
#define __SHA512_H__

#include <stdint.h>
#include <string.h>
#include <linux/types.h>
#include <asm/byteorder.h>

struct sha512_ctx
{
    uint64_t state[8];
    uint32_t count[4];
    uint8_t buf[128];
    uint64_t W[80];
};

#ifdef __cplusplus	//added by Jim Howard so that these functions can be called from c++
extern "C"
{
#endif

void sha512_init(void *ctx);
void sha512_update(void *ctx, const uint8_t *data, unsigned int len);
void sha512_final(void *ctx, uint8_t *hash);

#ifdef __cplusplus
}
#endif

#endif//__SHA512_H__
