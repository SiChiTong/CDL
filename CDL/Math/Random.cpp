#include <CDL/Math/Random.h>

namespace CDL
{
#define MODULUS    2147483647 // DON'T CHANGE THIS VALUE 2^31-1
#define MULTIPLIER 48271      // DON'T CHANGE THIS VALUE

    const long Q=MODULUS/MULTIPLIER;
    const long R=MODULUS%MULTIPLIER;

    Random::Random(const long &s)
    {
        if (s >= 0)
            randomize(s);
        else
            randomize(123456789);
    }

    void Random::randomize(const long &s)
    {
        if (s > 0)
            m_seed = s % MODULUS;
        else
            m_seed=((unsigned long)time((time_t *)'\0')) % MODULUS;
        if (m_seed < 0) m_seed += MODULUS;
    }

    DefType Random::rnd()
    {
        m_seed = MULTIPLIER * (m_seed%Q) - R *(m_seed/Q);
        if (m_seed < 0) m_seed += MODULUS;

        return ((DefType)m_seed/MODULUS);
    }

    const long &Random::irnd()
    {
        m_seed = MULTIPLIER * (m_seed%Q) - R *(m_seed/Q);
        if (m_seed < 0) m_seed += MODULUS;

        return m_seed;
    }

    DefType Random::uniform(const DefType &a, const DefType &b)
    {
        return rnd()*(b-a)+a;
    }

    int   Random::uniform(const int &a, const int &b)
    {
        return a+(int)((b-a+1.0)*rnd());
    }

    DefType Random::exponential(const DefType &lamda)
    {
        return -log(rnd())/lamda;
    }

    int   Random::geometric(const DefType &p)
    {
        return ((int)(log(rnd())/log(1.0-p)));
    }

    int   Random::bernulli(const DefType &p)
    {
        if (rnd() <= p)
            return 1;
        else
            return 0;
    }

    int   Random::binomial(const int &n, const DefType &p)
    {
        int i=0;
        DefType u=rnd(), q=pow(1.0-p, (DefType)n), f=q;

        while (f <= u)
        {
            q*=(p*(n-i)/((i+1.0)*(1.0-p)));
            f+=q;
            i++;
        }

        return i;
    }

    int   Random::poisson(const DefType &alpha)
    {
        int i=0;
        DefType u=rnd(), p=exp(-alpha), f=p;

        while (f <= u)
        {
            p*=(alpha/(i+1.0));
            f+=p;
            i++;
        }
        return i;
    }

    DefType Random::erlang(const int &m, const DefType &a)
    {
        double w=1.0;
        for (int i=0; i<m; i++)
            w*=rnd();
        return ((-a/m)*log(w));
    }

    DefType Random::gaussian(const DefType &mean, const DefType &dev)
    {
        return dev*sqrt(exponential(0.5))*cos(uniform(0.0f,2*MM_PI))+mean;
    }

    const long &Random::getSeed() const
    {
         return m_seed;
    }
}
