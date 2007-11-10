//========================================================================
/** @type     C/C++ Header File
 *  @file     Lockable.h
 *  @author   alex
 *  @date
 *   Created:       01:23:51 11/09/2007
 *   Last Update:   15:01:18 10/11/2007
 */
//========================================================================
#ifndef __CDL_LOCKABLE_H__
#define __CDL_LOCKABLE_H__

namespace CDL
{

    class Lockable
    {
        public:
            virtual ~Lockable() {}
            virtual void lock()=0;
            virtual void unlock()=0;
    };

    class ScopeLock
    {
        private:
            bool m_first;
            Lockable *m_lck;
        public:
            ScopeLock(Lockable *lck): m_first(true), m_lck(lck) {m_lck->lock();}
            ~ScopeLock() {m_lck->unlock();}
            void finish() {m_first=false;}
            operator bool () const {return m_first;}
    };

#define synchronized_scope_on(x) (ScopeLock)(x)
#define synchronized_scope       synchronized_scope_on(this)

#define synchronized_on(x) for(ScopeLock scopelock=x; scopelock; scopelock.finish())
#define syncrhonized       synchronized_on(this)
}

#endif//__CDL_LOCKABLE_H__
