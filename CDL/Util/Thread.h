#ifndef __CDL_THREAD_H__
#define __CDL_THREAD_H__

#include <CDL/defs.h>
#include <CDL/Util/NonCopyable.h>
#include <CDL/Util/Runnable.h>

namespace CDL
{
    class DLL_API Thread: public NonCopyable, public Runnable
    {
        protected:
            void    *m_handle;
            bool     m_alive;
            unsigned int m_id;
            static void *entryPoint(void *);

        public:
            Thread();
            virtual ~Thread();
            virtual void start();
            virtual void stop();
            void join();
            static void yield();
            static unsigned int currentThread();
            const unsigned int &getID() const;
            const bool &isAlive() const;
    };
}

#endif//__CDL_THREAD_H__
