#ifndef __CDL_CONDVAR_H__
#define __CDL_CONDVAR_H__

#include <CDL/Util/Mutex.h>

namespace CDL
{
    class DLL_API CondVar
    {
        private:
            int   *m_ref;
            void  *m_handle;
            Mutex &m_mutex;
            bool   m_locked;

        public:
            CondVar(Mutex &);
            virtual ~CondVar();
            CondVar(const CondVar &);
            CondVar& operator=(const CondVar &);
            void wait();
            void signal();
            void broadcast();
    };
}

#endif//__CDL_CONDVAR_H__
