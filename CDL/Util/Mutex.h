#ifndef __CDL_MUTEX_H__
#define __CDL_MUTEX_H__

#include <CDL/defs.h>
#include <CDL/Util/NonCopyable.h>
#include <CDL/Util/Lockable.h>

namespace CDL
{
    class DLL_API Mutex: public NonCopyable, public Lockable
    {
        protected:
            void   *m_handle;

        public:
            Mutex();
            virtual ~Mutex();
            void *getPtr() const;
            void lock();
            void unlock();
            bool trylock();
    };
}

#endif//__CDL_MUTEX_H__
