#ifndef __CDL_DIGEST_H__
#define __CDL_DIGEST_H__

#include <CDL/Util/Buffer.h>

namespace CDL
{
	class DLL_API Digest: public Buffer
	{
        private:
			const Digest &operator=(const Digest &);
		protected:
			char *m_str;

		public:
			Digest(unsigned char *d='\0', const int &l=0);
			virtual ~Digest();
			const unsigned char *getValue() const;
			const char *getString() const;
	};
}

#endif//__CDL_DIGEST_H__
