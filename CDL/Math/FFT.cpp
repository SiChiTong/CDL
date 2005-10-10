#include <CDL/Math/FFT.h>

namespace CDL
{
    /**
      powerOfTwo calulates a number m so that
      when elevating 2 to the m you obtain n
      (the first paramter).
      If there is no such number m that satisfies
      the described properties it returns -1.
      */
    int powerOfTwo(const int &n)
    {
        int m=0, p=1;
        while (p<n)
        {
            p*=2;
            m++;
        }
        if (p != n)
            return -1;
        return m;
    }

    /**
      Calculate the FFT (Fast Fourier Transform)
      of the array given as first parameter and
      of length n (second parameter).
      The result will be stored replacing the old
      data array.
      */
    DLL_API void DLL_CALLCONV FFT(Complex *c, const unsigned long &n)
    {
        unsigned long i, i1, i2, j, k, l1, l2;
        int m, l;
        Complex t, u, r;

        /* Check if length is a power of 2 */
        if ((m=powerOfTwo(n)) == -1)
            return;

        /* Do the bit reversal */
        i2 = n >> 1;
        for (i=0, j=0; i<n-1; i++)
        {
            if (i < j)
            {
                t=c[i];
                c[i]=c[j];
                c[j]=t;
            }
            k = i2;
            while (k <= j)
            {
                j -= k;
                k >>= 1;
            }
            j += k;
        }

        /* Compute the FFT */
        r=Complex(-1.0, 0.0);
        l2 = 1;
        for (l=0; l<m; l++)
        {
            l1 = l2;
            l2 <<= 1;
            u=Complex(1.0, 0.0);
            for (j=0; j<l1; j++)
            {
                for (i=j; i<n; i+=l2)
                {
                    i1=i+l1;
                    t=u*c[i1];
                    c[i1]=c[i]-t;
                    c[i]+=t;
                }
                u*=r;
            }
            r=Complex(sqrt((1.0+r.getReal())/2.0), -sqrt((1.0-r.getReal())/2.0));
        }

        /* Scale result by n */
        for (i=0; i<n; i++)
            c[i]/=n;
    }

    /**
      Calculate the iFFT (Inverse Fast Fourier Transform)
      of the array given as first parameter and
      of length n (second parameter).
      The result will be stored replacing the old
      data array.
      */

    DLL_API void DLL_CALLCONV iFFT(Complex *c, const unsigned long &n)
    {
        unsigned long m, i, i1, i2, j, k, l, l1, l2;
        Complex t, u, r;

        /* Check if length is a power of 2 */
        m=powerOfTwo(n);

        /* Do the bit reversal */
        i2 = n >> 1;
        for (i=0, j=0; i<n-1; i++)
        {
            if (i < j)
            {
                t=c[i];
                c[i]=c[j];
                c[j]=t;
            }
            k = i2;
            while (k <= j)
            {
                j -= k;
                k >>= 1;
            }
            j += k;
        }

        /* Compute the iFFT */
        r=Complex(-1.0, 0.0);
        l2 = 1;
        for (l=0; l<m; l++)
        {
            l1 = l2;
            l2 <<= 1;
            u=Complex(1.0, 0.0);
            for (j=0; j<l1; j++)
            {
                for (i=j; i<n; i+=l2)
                {
                    i1=i+l1;
                    t=u*c[i1];
                    c[i1]=c[i]-t;
                    c[i]+=t;
                }
                u*=r;
            }
            r=Complex(sqrt((1.0+r.getReal())/2.0), sqrt((1.0-r.getReal())/2.0));
        }
    }

    /**
      Using the previous defined function FFT
      FFT2D calculates de two dimensional FFT
      of a given array of size nx*ny; and as
      in FFT it stores the result in the same
      array.
      */
    DLL_API void DLL_CALLCONV FFT2D(Complex *c, const int &nx, const int &ny)
    {
        Complex *t;

        /* Check if dimensions are a power of 2 */
        if (powerOfTwo(nx) == -1 || powerOfTwo(ny) == -1)
            return;

        /* Calculate the FFT for rows */
        t=new Complex[nx];
        for (int j=0; j<ny; j++)
        {
            for (int i=0; i<nx; i++)
                t[i]=c[j*nx+i];

            FFT(t, nx);

            for (int i=0; i<nx; i++)
                c[j*nx+i]=t[i];

        }
        delete t;

        /* Calculate the FFT for columns */
        t=new Complex[ny];
        for (int i=0; i<nx; i++)
        {
            for (int j=0; j<ny; j++)
                t[j]=c[j*nx+i];

            FFT(t, ny);

            for (int j=0; j<ny; j++)
                c[j*nx+i]=t[j];
        }
        delete t;
    }

    /**
      Using the previous defined function iFFT
      iFFT2D calculates de two dimensional iFFT
      of a given array of size nx*ny; and as
      in FFT it stores the result in the same
      array.
      */
    DLL_API void DLL_CALLCONV iFFT2D(Complex *c, const int &nx, const int &ny)
    {
        Complex *t;

        /* Check if dimensions are a power of 2 */
        if (powerOfTwo(nx) == -1 || powerOfTwo(ny) == -1)
            return;

        /* Calculate the FFT for rows */
        t=new Complex[nx];
        for (int j=0; j<ny; j++)
        {
            for (int i=0; i<nx; i++)
                t[i]=c[j*nx+i];

            iFFT(t, nx);

            for (int i=0; i<nx; i++)
                c[j*nx+i]=t[i];

        }
        delete t;

        /* Calculate the FFT for columns */
        t=new Complex[ny];
        for (int i=0; i<nx; i++)
        {
            for (int j=0; j<ny; j++)
                t[j]=c[j*nx+i];

            iFFT(t, ny);

            for (int j=0; j<ny; j++)
                c[j*nx+i]=t[j];
        }
        delete t;
    }

    DLL_API void DLL_CALLCONV filter2D(Complex *c, const int &nx, const int &ny, const FFT_filter &flt, const DefType &p)
    {
        DefType r, r1, r2, r3, r4;

        for (int i=0; i<nx; i++)
            for (int j=0; j<ny; j++)
            {
                r1=i*i+j*j;
                r2=(i-nx)*(i-nx)+j*j;
                r3=i*i+(j-ny)*(j-ny);
                r4=(i-nx)*(i-nx)+(j-ny)*(j-ny);
                r=MIN(MIN(MIN(r1,r2),r3),r4);

                switch(flt)
                {
                    case FFT_LOWPASS:
                        if (r>p*p)
                            c[i+j*nx]=Complex(0,0);
                        break;
                    case FFT_HIGHPASS:
                        if (r<p*p)
                            c[i+j*nx]=Complex(0,0);
                        break;
                    case FFT_1OVERF:
                        if (r>0)
                            c[i+j*nx]*=pow(1/r, p);
                }
            }

    }
}
