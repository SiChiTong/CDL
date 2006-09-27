//========================================================================
/** @type     C/C++ Header File
 *  @file     ODESolver.h
 *  @author   acornejo
 *  @date
 *   Created:       23:35:51 26/09/2006
 *   Last Update:   18:08:22 27/09/2006
 */
//========================================================================

#ifndef __ODESOLVER_H__
#define __ODESOLVER_H__

#include <CDL/Math/Math.h>

namespace CDL
{
    class DLL_API ODESolver
    {
        public:
            typedef enum {EULER=0, MIDPOINT, RUNGEKUTTA} ODESolve_Method;

        protected:
            float m_time;
            size_t m_size;
            ODESolve_Method m_method;

            virtual void toArray(float []) const=0;
            virtual void fromArray(const float [])=0;
            virtual void dydt(float [])=0;

        public:
            ODESolver();
            virtual ~ODESolver();
            const size_t &getSize() const;
            const float &getTime() const;
            const ODESolve_Method &getMethod() const;
            void setMethod(const ODESolve_Method &);
            void solve(const float &dt);
    };
}
#endif//__ODESOLVER_H__
