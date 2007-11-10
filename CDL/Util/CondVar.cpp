#include <CDL/Util/CondVar.h>

namespace CDL
{
#if defined(Windows_NT)
	#include <windows.h>
	#define condvar_t HANDLE
    #define mutex_t HANDLE
    #define CondVar_create(handle)    *((condvar_t*)handle)=CreateEvent(NULL,FALSE,FALSE,NULL)
    #define CondVar_destroy(handle)   CloseHandle(*((condvar_t*)handle))
    #define CondVar_signal(handle)    SetEvent(*((condvar_t*)handle))
    #define CondVar_broadcast(handle) PulseEvent(*((condvar_t*)handle))
	#define CondVar_wait(handle,x)    {SignalObjectAndWait(*((condvar_t*)x.getPtr()),*((condvar_t*)handle),INFINITE, \
            FALSE);WaitForSingleObject(*((condvar_t*)x.getPtr()),INFINITE);};
	#define CondVar_timedwait(handle,x,ms) {SignalObjectAndWait(*((condvar_t*)x.getPtr()),*((condvar_t*)handle),ms, \
            FALSE);WaitForSingleObject(*((condvar_t*)x.getPtr()),INFINITE);};
#else
	#include <pthread.h>
	#define condvar_t pthread_cond_t
	#define mutex_t pthread_mutex_t
    #define CondVar_create(handle)    pthread_cond_init((condvar_t*)handle,NULL)
    #define CondVar_destroy(handle)   pthread_cond_destroy((condvar_t*)handle)
    #define CondVar_signal(handle)    pthread_cond_signal((condvar_t*)handle)
    #define CondVar_broadcast(handle) pthread_cond_broadcast((condvar_t*)handle)
	#define CondVar_wait(handle,x)    pthread_cond_wait((condvar_t*)handle, (mutex_t *)x.getPtr())
	#define CondVar_timedwait(handle,x,ms) {timeval now;gettimeofday(&now,NULL);timespec timeout;timeout.tv_sec=now.tv_sec+(ms/1000);timeout.tv_nsec=now.tv_usec*1000+(ms%1000)*1000000;pthread_cond_timedwait((condvar_t*)handle, (mutex_t *)x.getPtr(),&timeout);}
#endif

    CondVar::CondVar()
    {
        m_handle=new condvar_t;
        CondVar_create(m_handle);
    }

    CondVar::~CondVar()
    {
        CondVar_destroy(m_handle);
        delete (condvar_t*)m_handle;
    }

    void CondVar::wait(Mutex &mutex)
    {
        CondVar_wait(m_handle,mutex); // unlocks and waits, then lockes external mutex when returning
    }

    void CondVar::timedwait(Mutex &mutex, const size_t &ms)
    {
        CondVar_timedwait(m_handle,mutex,ms);
    }

    void CondVar::broadcast()
    {
        CondVar_broadcast(m_handle);
    }

    void CondVar::signal()
    {
        CondVar_signal(m_handle);
    }
}
