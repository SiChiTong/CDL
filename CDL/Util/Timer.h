#ifndef __CDL_TIMER_H__
#define __CDL_TIMER_H__

#include <CDL/Util/Thread.h>

namespace CDL
{
    class DLL_API Timer
    {
        private:
            void *m_time;

        public:
            typedef void (*callback)();

            Timer();
            virtual ~Timer();
            Timer(const Timer &);
            Timer& operator=(const Timer &);
            void reset();
            size_t getElapsed() const;
            static void sleep(const size_t &);
            static void alarm(const size_t &, callback);
            static double getTimeOfDay();
    };
}

#endif//__CDL_TIMER_H__
