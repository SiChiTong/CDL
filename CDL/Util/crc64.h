//========================================================================
/** @type     C/C++ Header File
 *  @file     crc64.h
 *  @author   alcoco
 *  @date     
 *   Created:       13:26:26 05/04/2005
 *   Last Update:   01:15:52 06/04/2005
 */
//========================================================================

#ifndef __CRC64_H__
#define __CRC64_H__

typedef struct CRC64Context
{
    unsigned long long crc; 
} CRC64Context;

#ifdef __cplusplus
extern "C" 
{
#endif

void CRC64Reset(CRC64Context *);
void CRC64Input(CRC64Context *, const void *, const int);
void CRC64Result(CRC64Context *, void *);

#ifdef __cplusplus
}
#endif

#endif//__CRC64_H__
