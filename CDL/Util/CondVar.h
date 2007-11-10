#ifndef __CDL_CONDVAR_H__
#define __CDL_CONDVAR_H__

#include <CDL/Util/Mutex.h>
#include <CDL/Util/NonCopyable.h>

namespace CDL
{
    class DLL_API CondVar: public NonCopyable
    {
        private:
            void  *m_handle;
            bool   m_locked;

        public:
            CondVar();
            virtual ~CondVar();
            void wait(Mutex &m);
            void timedwait(Mutex &m, const size_t &ms);
            void signal();
            void broadcast();
    };
}

#endif//__CDL_CONDVAR_H__
