#include <CDL/Util/Mutex.h>

namespace CDL
{
#if   defined(Windows_NT)
	#include <windows.h>
	#define mutex_t HANDLE
    #define Mutex_create(handle)  *((mutex_t*)handle)=CreateMutex(NULL,FALSE,NULL)
    #define Mutex_destroy(handle) CloseHandle(*((mutex_t*)handle))
    #define Mutex_lock(handle)    WaitForSingleObject(*((mutex_t*)handle),INFINITE);
    #define Mutex_unlock(handle)  ReleaseMutex(*((mutex_t*)handle))
    #define Mutex_trylock(handle) WaitForSingleObject(*((mutex_t*)handle),0) == WAIT_OBJECT_0
#elif defined(Linux)
	#include <pthread.h>
	#define mutex_t pthread_mutex_t
    #define Mutex_create(handle)  pthread_mutex_init((mutex_t *)handle,0)
    #define Mutex_destroy(handle) pthread_mutex_destroy((mutex_t *)handle)
    #define Mutex_lock(handle)    pthread_mutex_lock((mutex_t *)handle)
    #define Mutex_unlock(handle)  pthread_mutex_unlock((mutex_t *)handle)
    #define Mutex_trylock(handle) pthread_mutex_trylock((mutex_t *)handle) == 0
#endif

    Mutex::Mutex()
    {
        m_handle=new mutex_t;
        Mutex_create(m_handle);
        m_ref=new int(1);
    }

    Mutex::~Mutex()
    {
        --(*m_ref);
        if ((*m_ref) == 0)
        {
            delete m_ref;
            Mutex_destroy(m_handle);
            delete (mutex_t*)m_handle;
        }
    }

    Mutex::Mutex(const Mutex &m)
    {
        m_ref=m.m_ref;
        ++(*m_ref);
        m_handle=m.m_handle;
    }

    Mutex& Mutex::operator=(const Mutex &m)
    {
        if (this != &m)
        {
            --(*m_ref);
            if (*m_ref == 0)
            {
                delete m_ref;
                Mutex_destroy(m_handle);
                delete (mutex_t*)m_handle;
            }
            m_ref=m.m_ref;
            ++(*m_ref);
            m_handle=m.m_handle;
        }
        return *this;
    }

    void *Mutex::getPtr() const
    {
        return m_handle;
    }

    void Mutex::lock()
    {
        Mutex_lock(m_handle);
    }

    void Mutex::unlock()
    {
        Mutex_unlock(m_handle);
    }

    bool Mutex::trylock()
    {
         return Mutex_trylock(m_handle);
    }
}
