//========================================================================
/** @type     C/C++ Header File
 *  @file     Runnable.h
 *  @author   acornejo
 *  @date
 *   Created:       14:53:55 10/11/2007
 *   Last Update:   14:56:41 10/11/2007
 */
//========================================================================
#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

namespace CDL
{
    class Runnable
    {
        public:
            virtual ~Runnable() {}
            virtual void run()=0;
    };
}
#endif//__RUNNABLE_H__
