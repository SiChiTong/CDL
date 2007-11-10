//========================================================================
/** @type     C/C++ Header File
 *  @file     Waitable.h
 *  @author   acornejo
 *  @date
 *   Created:       15:03:45 10/11/2007
 *   Last Update:   15:05:34 10/11/2007
 */
//========================================================================
#ifndef __WAITABLE_H__
#define __WAITABLE_H__

namespace CDL
{
    class Waitable
    {
        public:
            virtual ~Waitable() {}
            virtual void wait()=0;
            virtual void wait(const size_t &ms)=0;
    };
}

#endif//__WAITABLE_H__
