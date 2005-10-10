#ifndef __CDL_MUTEX_H__
#define __CDL_MUTEX_H__

#include <CDL/defs.h>

namespace CDL
{
    class DLL_API Mutex
    {
        protected:
            void   *m_handle;
            int    *m_ref;

        public:
            Mutex();
            virtual ~Mutex();
            Mutex(const Mutex &);
            Mutex& operator=(const Mutex &);
            void *getPtr() const;
            void lock();
            void unlock();
            bool trylock();
    };
}

#endif//__CDL_MUTEX_H__
