#ifndef __CDL_FFT_H__
#define __CDL_FFT_H__

#include <CDL/Math/Complex.h>

namespace CDL
{
    typedef enum {FFT_LOWPASS=0, FFT_HIGHPASS, FFT_1OVERF} FFT_filter;


    DLL_API void DLL_CALLCONV     FFT(Complex *, const unsigned long&);
    DLL_API void DLL_CALLCONV    iFFT(Complex *, const unsigned long&);
    DLL_API void DLL_CALLCONV   FFT2D(Complex *, const int&, const int&);
    DLL_API void DLL_CALLCONV  iFFT2D(Complex *, const int&, const int&);
    DLL_API void DLL_CALLCONV filter2D(Complex *, const int&, const int&, const FFT_filter &, const DefType&);
}

#endif//__CDL_FFT_H__
