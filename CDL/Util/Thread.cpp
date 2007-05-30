#include <CDL/Util/Thread.h>

namespace CDL
{
#if   defined(Windows_NT)
	#include <windows.h>
	#define thread_t HANDLE
    #define Thread_create(handle)  (*(thread_t*)handle)=CreateThread(0,0,(LPTHREAD_START_ROUTINE)entryPoint,this,0,0)
    #define Thread_destroy(handle) TerminateThread((*(thread_t*)handle),0)
    #define Thread_join(handle)    WaitForSingleObject(*((thread_t*)handle), INFINITE)
    #define Thread_yield()         SwitchToThread()
	#define Thread_exit()          ExitThread(0)
	#define Thread_currentThread() GetCurrentThread()
#else
	#include <pthread.h>
	#define thread_t pthread_t
    #define Thread_create(handle)  pthread_create((thread_t *)handle,&attr,entryPoint,this)
    #define Thread_destroy(handle) pthread_cancel(*((thread_t*)handle))
    #define Thread_join(handle)    pthread_join(*((thread_t*)handle), NULL)
    #define Thread_yield()         pthread_yield()
	#define Thread_exit()          pthread_exit(NULL)
	#define Thread_currentThread() pthread_self()
#endif

    void *Thread::entryPoint(void *threadp)
    {
        Thread *thread=(Thread *)threadp;

        thread->m_alive=true;
        thread->m_id=(unsigned int)Thread_currentThread();
        thread->run();
        thread->m_alive=false;

        Thread_exit();
    }

    Thread::Thread()
    {
        m_alive=false;
        m_handle=new thread_t;
    }

    Thread::~Thread()
    {
        delete (thread_t*)m_handle;
    }

    void Thread::start()
    {
#if defined(Linux)
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
#endif

//        if (m_alive)
//            return;
        m_alive=true;
        Thread_create(m_handle);
#if defined(Linux)
        pthread_attr_destroy(&attr);
#endif
    }

    void Thread::stop()
    {
        if (!m_alive)
            return;
        Thread_destroy(m_handle);
        m_alive=false;
    }

    void Thread::join()
    {
        if (!m_alive)
            return;
        Thread_join(m_handle);
    }

    const unsigned int &Thread::getID() const
    {
         return m_id;
    }

    void Thread::yield()
    {
        Thread_yield();
    }

    unsigned int Thread::currentThread()
    {
        return (unsigned int)Thread_currentThread();
    }

    const bool &Thread::isAlive() const
    {
        return m_alive;
    }
}
