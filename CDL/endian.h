//========================================================================
/** @type     C/C++ Header File
 *  @file     endian.h
 *  @author   acornejo
 *  @date
 *   Created:       02:32:06 19/06/2005
 *   Last Update:   08:47:06 08/09/2006
 */
//========================================================================

#ifdef HAVE_CONFIG_H
    #include <config.h>
    #ifdef HAVE_BYTESWAP_H
        #include <byteswap.h>
    #endif
#endif
#ifndef HAVE_BYTESWAP_H
static unsigned short bswap_16 (const unsigned short &x)
{
    return ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8));
}

static unsigned int bswap_32(const unsigned int &x)
{
    return ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) | \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24));
}

static unsigned long long bswap_64(const unsigned long long &x)
{
     return ((((x) & 0xff00000000000000ull) >> 56)				  \
      | (((x) & 0x00ff000000000000ull) >> 40)				      \
      | (((x) & 0x0000ff0000000000ull) >> 24)				      \
      | (((x) & 0x000000ff00000000ull) >> 8)				      \
      | (((x) & 0x00000000ff000000ull) << 8)				      \
      | (((x) & 0x0000000000ff0000ull) << 24)				      \
      | (((x) & 0x000000000000ff00ull) << 40)				      \
      | (((x) & 0x00000000000000ffull) << 56));
}
#endif

#ifdef WORDS_BIGENDIAN
    #define LE16_TO_CPU(x) (*((unsigned short *)&x)=bswap_16(*(unsigned short *)&x))
    #define LE32_TO_CPU(x) (*((unsigned int *)&x)=bswap_32(*(unsigned int *)&x))
    #define LE64_TO_CPU(x) (*((unsigned long long *)&x)=bswap_64(*(unsigned long long *)&x))
    #define BE16_TO_CPU(x) (x)
    #define BE32_TO_CPU(x) (x)
    #define BE64_TO_CPU(x) (x)
#else
    #define LE16_TO_CPU(x) (x)
    #define LE32_TO_CPU(x) (x)
    #define LE64_TO_CPU(x) (x)
    #define BE16_TO_CPU(x) (*((unsigned short *)&x)=bswap_16(*(unsigned short *)&x))
    #define BE32_TO_CPU(x) (*((unsigned int *)&x)=bswap_32(*(unsigned int *)&x))
    #define BE64_TO_CPU(x) (*((unsigned long long *)&x)=bswap_64(*(unsigned long long *)&x))
#endif

