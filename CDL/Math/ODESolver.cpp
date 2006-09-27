//========================================================================
/** @type     C++ Source File
 *  @file     ODESolver.cpp
 *  @author   acornejo
 *  @date
 *   Created:       13:58:46 27/09/2006
 *   Last Update:   18:08:34 27/09/2006
 */
//========================================================================
#include <CDL/Math/ODESolver.h>

namespace CDL
{
    DEFCLASS("ODESolver");

    ODESolver::ODESolver(): m_method(EULER), m_time(0.0f), m_size(0) {}

    ODESolver::~ODESolver() {}

    const size_t &ODESolver::getSize() const
    {
        return m_size;
    }

    const float &ODESolver::getTime() const
    {
        return m_time;
    }

    const ODESolver::ODESolve_Method &ODESolver::getMethod() const
    {
        return m_method;
    }

    void ODESolver::setMethod(const ODESolve_Method &method)
    {
        m_method=method;
    }

    void ODESolver::solve(const float &dt)
    {
        float y0[m_size], yEval[m_size];

        toArray(y0);
        switch(m_method)
        {
            case EULER:
                dydt(yEval);
                for (size_t i=0; i<m_size; i++)
                    y0[i]+=yEval[i]*dt;
                m_time+=dt;
                break;
            case MIDPOINT:
                {
                    float y1[m_size], dt2=dt*.5f;
                    dydt(yEval);
                    for (size_t i=0; i<m_size; i++)
                        y1[i]=y0[i]+yEval[i]*dt2;
                    m_time+=dt2;
                    fromArray(y1);
                    dydt(yEval);
                    for (size_t i=0; i<m_size; i++)
                        y0[i]+=yEval[i]*dt;
                    m_time+=dt2;
                }
                break;
            case RUNGEKUTTA:
                {
                    float y1[m_size], y2[m_size], y3[m_size];
                    dydt(y1);
                    for (size_t i=0; i<m_size; i++)
                    {
                        y1[i]*=dt;
                        yEval[i]=y0[i]+y1[i]*.5f;
                    }
                    fromArray(yEval);
                    dydt(y2);
                    for (size_t i=0; i<m_size; i++)
                    {
                        y2[i]*=dt;
                        yEval[i]=y0[i]+y2[i]*.5f;
                    }
                    fromArray(yEval);
                    dydt(y3);
                    for (size_t i=0; i<m_size; i++)
                    {
                        y3[i]*=dt;
                        yEval[i]=y0[i]+y3[i];
                    }
                    fromArray(yEval);
                    dydt(yEval);
                    for (size_t i=0; i<m_size; i++)
                    {
                        yEval[i]*=dt;
                        y0[i]+=y1[i]/6.0+y2[i]/3.0+y3[i]/3.0+yEval[i]/6.0;
                    }
                    m_time+=dt;
                }
                break;
            default:
                Error_send("Unkown ODE solver method %d\n", m_method);
                break;
        }
        fromArray(y0);
    }
}
