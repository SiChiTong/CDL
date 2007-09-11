//========================================================================
/** @type     C/C++ Header File
 *  @file     Lockable.h
 *  @author   alex
 *  @date
 *   Created:       01:23:51 11/09/2007
 *   Last Update:   01:31:02 11/09/2007
 */
//========================================================================
#ifndef __CDL_LOCKABLE_H__
#define __CDL_LOCKABLE_H__

namespace CDL
{

    class Lockable
    {
        private:
            Mutex m_lockmutex;

        protected:
            class ScopeLock
            {
                private:
                    bool m_first;
                    Lockable *m_lck;
                public:
                    ScopeLock(Lockable *lck): m_first(true), m_lck(lck) {m_lck->m_lockmutex.lock();}
                    ~ScopeLock() {m_lck->m_lockmutex.unlock();}
                    void finish() {m_first=false;}
                    operator bool () const {return m_first;}
            };
    };

#define syncrhonized for(ScopeLock scopelock=this; scopelock; scopelock.finish())
}

#endif//__CDL_LOCKABLE_H__
