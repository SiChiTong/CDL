//========================================================================
/** @type     C/C++ Header File
 *  @file     NonCopyable.h
 *  @author   alex
 *  @date
 *   Created:       10:43:17 30/05/2007
 *   Last Update:   10:44:31 30/05/2007
 */
//========================================================================
#ifndef __CDL_NONCOPYABLE_H__
#define __CDL_NONCOPYABLE_H__

namespace CDL
{
    class NonCopyable
    {
        protected:
            NonCopyable() {}
            ~NonCopyable() {}

        private:
            NonCopyable(const NonCopyable &);
            const NonCopyable &operator=(const NonCopyable &);
    };
}

#endif//__CDL_NONCOPYABLE_H__
