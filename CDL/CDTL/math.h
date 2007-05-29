//========================================================================
/** @type     C/C++ Header File
 *  @file     math.h
 *  @author   acornejo
 *  @date
 *   Created:       10:32:04 09/03/2007
 *   Last Update:   23:08:02 28/05/2007
 */
//========================================================================
template <size_t M, size_t N> // log_M (N)
struct Log
{
    enum {value=1+Log<M,N/M>::value};
};

template <size_t M>
struct Log<M,1>
{
    enum {value=1};
};

template <size_t M,size_t N>
struct Pow
{
    enum {value=M*Pow<M,N-1>::value};
};

template <size_t M>
struct Pow<M,0>
{
    enum {value=1};
};

template <size_t N>
struct Factorial
{
    enum {value=N*Factorial<N-1>::value};
};

template <>
struct Factorial<0>
{
    enum {value=1};
};

#define MUSTINLINE __attribute__((always_inline))

template <class T, int SIZE>
struct Unroll
{

    static MUSTINLINE void copy(T *target_array, T *source_array)
    {
        *target_array++=*source_array++;
        Unroll<T,SIZE-1>::copy(target_array,source_array);
    }

    static MUSTINLINE void copy(T *target_array, T *source_array, int *index_array, int j)
    {
        target_array[index_array[j]]=source_array[index_array[j]];
        Unroll<T,SIZE-1>::copy(target_array,source_array,index_array,j+1);
    }
};

template <class T>
struct Unroll<T,0>
{
    static MUSTINLINE void copy(T *target_array, T *source_array) {}
    static MUSTINLINE void copy(T *target_array, T *source_array, int *index_array, int j) {}
};
