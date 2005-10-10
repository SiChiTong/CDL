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
#else
	#include <pthread.h>
	#define condvar_t pthread_cond_t
	#define mutex_t pthread_mutex_t
    #define CondVar_create(handle)    pthread_cond_init((condvar_t*)handle,NULL)
    #define CondVar_destroy(handle)   pthread_cond_destroy((condvar_t*)handle)
    #define CondVar_signal(handle)    pthread_cond_signal((condvar_t*)handle)
    #define CondVar_broadcast(handle) pthread_cond_broadcast((condvar_t*)handle)
	#define CondVar_wait(handle,x)    pthread_cond_wait((condvar_t*)handle, (mutex_t *)x.getPtr())
#endif

    CondVar::CondVar(Mutex &mutex): m_mutex(mutex)
    {
        m_ref=new int(1);
        m_handle=new condvar_t;
        CondVar_create(m_handle);
        m_locked=false;
    }

    CondVar::~CondVar()
    {
        if (!--(*m_ref))
        {
            delete m_ref;
            CondVar_destroy(m_handle);
            delete (condvar_t*)m_handle;
        }
    }

    CondVar::CondVar(const CondVar &c): m_mutex(c.m_mutex)
    {
        m_ref=c.m_ref;
        ++(*m_ref);
        m_handle=c.m_handle;
        m_locked=c.m_locked;
    }

    CondVar& CondVar::operator=(const CondVar &c)
    {
        if (this != &c)
        {
            if (!--(*m_ref))
            {
                delete m_ref;
                CondVar_destroy(m_handle);
                delete (condvar_t*)m_handle;
            }
            m_ref=c.m_ref;
            ++(*m_ref);
            m_handle=c.m_handle;
            m_mutex=c.m_mutex;
            m_locked=c.m_locked;
        }
        return *this;
    }

    void CondVar::wait()
    {
        m_mutex.lock();
        while (m_locked)
            CondVar_wait(m_handle,m_mutex); // unlocks and waits, then lockes external mutex when returning
        m_locked=true;
        // here insert what to do
        m_mutex.unlock();
    }

    void CondVar::broadcast()
    {
        m_mutex.lock();
        // here insert what to do
        m_locked=false;
        CondVar_broadcast(m_handle);
        m_mutex.unlock();
    }

    void CondVar::signal()
    {
        m_mutex.lock();
        if (m_locked)
        {
            m_locked=false;
            CondVar_signal(m_handle);
        }
        m_mutex.unlock();
    }
}
