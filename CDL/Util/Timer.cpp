#include <CDL/Util/Timer.h>
#include <vector>

namespace CDL
{
#if   defined(Windows_NT)
	#include <windows.h>
	#include <mmsystem.h>
    typedef unsigned int timerx_t;
    #define Timer_reset(time) *((timerx_t*)time)=timeGetTime()
    #define Timer_sleep(ms)   Sleep(ms)
#else
	#include <sys/timeb.h>
	#include <unistd.h>
    typedef struct timeb timerx_t;
    #define Timer_reset(time) ftime((timerx_t*)time)
    #define Timer_sleep(ms)   usleep(ms*1000)
#endif

    class AlarmThread: public Thread
    {
        private:
            size_t m_ms;
            Timer::callback m_callback;

        public:
            AlarmThread(const size_t &ms, Timer::callback func)
            {
                m_ms=ms;
                m_callback=func;
                start();
            }
            void run()
            {
                Timer::sleep(m_ms);
                (*m_callback)();
            }
    };

    std::vector<AlarmThread *> alarmqueue;

    Timer::Timer()
    {
        m_time=new timerx_t;
        Timer_reset(m_time);
    }

    Timer::~Timer()
    {
        delete (timerx_t*)m_time;
    }

    Timer::Timer(const Timer &t)
    {
        m_time=new timerx_t;
        *((timerx_t*)m_time)=*((timerx_t*)t.m_time);
    }

    Timer& Timer::operator=(const Timer &t)
    {
        if (this != &t)
        {
            *((timerx_t*)m_time)=*((timerx_t*)t.m_time);
        }
        return *this;
    }

    void Timer::reset()
    {
        Timer_reset(m_time);
    }

    size_t Timer::getElapsed() const
    {
#if defined(Windows_NT)
        return timeGetTime()-*((timerx_t*)m_time);
#else
        timerx_t now;
        ftime(&now);
        return (now.time-((timerx_t*)m_time)->time)*1000+now.millitm-((timerx_t*)m_time)->millitm;
#endif
    }

    void Timer::sleep(const size_t &ms)
    {
        Timer_sleep(ms);
    }

    double Timer::getTimeOfDay()
    {
         static const double unixEpoch=2440587.5;
         time_t curtime=time((time_t*)'\0');

         return unixEpoch+((double)curtime)/86400.0;
    }

    void Timer::alarm(const size_t &ms, callback func)
    {
        std::vector<AlarmThread *>::iterator begin=alarmqueue.begin();
        while (begin != alarmqueue.end())
        {
            if ((*begin)->isAlive())
                begin++;
            else
            {
                delete *begin;
                begin=alarmqueue.erase(begin);
            }
        }

        alarmqueue.push_back(new AlarmThread(ms,func));
    }
}
