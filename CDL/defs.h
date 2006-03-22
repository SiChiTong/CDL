#ifndef __DEFS_H__
#define __DEFS_H__

#ifdef HAVE_CONFIG_H
	#include <config.h>
    #include <CDL/endian.h>
#endif

#ifdef WIN32
    #ifdef CDL_EXPORTS
        #define DLL_API __declspec(dllexport)
    #else
        #define DLL_API __declspec(dllimport)
    #endif
    #define DLL_CALLCONV __stdcall
#else
    #define DLL_API
    #define DLL_CALLCONV
#endif

#if !defined(LOWORD) && !defined(HIWORD)
#define MAKEDWORD(a,b)   ((size_t)(((unsigned short)(a))|(((size_t)((unsigned short)(b)))<<16)))
#define LOWORD(l)   ((unsigned short)((size_t)(l)))
#define HIWORD(l)   ((unsigned short)(((size_t)(l)>>16)&0xFFFF))
#endif

#define DEBUGCDL
#define DEFCLASS(name)      static const char *__class__=name

// Math definitions
typedef float DefType;       // What type to use for Math.*

#define Error_send printf("Error at %s.%s defined in %s:%d\n\t",__class__,__func__,__FILE__,__LINE__);printf

#define MM_EPSILON           0.0001                     // near zero value
//#define MM_EPSILON           __FLT_EPSILON__             // near zero value
#define MM_PI                3.14159265358979323846      // PI

#define M2_ij(i,j)   (j*2+i)     // column major (like opengl)
#define M3_ij(i,j)   (j*3+i)
#define M4_ij(i,j)   (j*4+i)

#define NOTZERO(x)           ((x) > MM_EPSILON || (x) < -MM_EPSILON)
#define ZERO(x)              ((x) < MM_EPSILON && (x) > -MM_EPSILON)

#ifndef ABS
    #define ABS(x)           (((x) >= 0) ? (x) : -(x))
#endif//ABS
#ifndef MAX
	#define MAX(a,b)         ((a) > (b) ? (a) : (b))
#endif//MAX
#ifndef MIN
	#define MIN(a,b)         ((a) < (b) ? (a) : (b))
#endif//MIN
#ifndef MAX3
    #define MAX3(a,b,c)      MAX(a,MAX(b,c))
#endif//MAX3
#ifndef MIN3
    #define MIN3(a,b,c)      MIN(a,MIN(b,c))
#endif//MIN3
#ifndef MID
    #define MID(a,b,c)      ((a)>(b)?(((a)<(c))?(a):(((b)>(c))?(b):(c))):(((b)<(c))?(b):(((a)>(c))?(a):(c))))
#endif//MID
#ifndef CLAMP
	#define CLAMP(a,x,b)     MIN(b,MAX(a,x))
#endif//CLAMP
#ifndef POW2
	#define POW2(x)          ((x)*(x))
#endif//POW2
#ifndef POW3
	#define POW3(x)          ((x)*(x)*(x))
#endif//POW3
#ifndef POW4
	#define POW4(x)          ((x)*(x)*(x)*(x))
#endif//POW4

#define DEG2RAD(x)       ((x)*MM_PI/180.0)
#define RAD2DEG(x)       ((x)*180.0/MM_PI)

#include <math.h>         // Used for Math.*
#include <time.h>         // Used for Random.randomize(-1)
#include <stdio.h>        // File.*
#include <string.h>       // memcpy, strlen, strcpy

#endif//__DEFS_H__
