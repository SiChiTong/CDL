#ifndef __CDL_RANDOM_H__
#define __CDL_RANDOM_H__

#include <CDL/defs.h>

namespace CDL
{
    class DLL_API Random
    {
        private:
            long m_seed;

        public:
            Random(const long &s=-1);
            void    randomize(const long &s=-1);
            DefType rnd();
            const long &irnd();
            DefType uniform(const DefType&, const DefType&);
            int     uniform(const int&, const int&);
            DefType exponential(const DefType&);
            int     geometric(const DefType&);
            int     bernulli(const DefType&);
            int     binomial(const int&, const DefType&);
            int     poisson(const DefType&);
            DefType erlang(const int&, const DefType&);
            DefType gaussian(const DefType&, const DefType&);
            const long &getSeed() const;
    };
}

#endif//__CDL_RANDOM_H__
