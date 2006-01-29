#ifndef __CDL_DIGEST_H__
#define __CDL_DIGEST_H__

#include <CDL/Util/Buffer.h>

namespace CDL
{
	class DLL_API Digest
	{
        private:
			const Digest &operator=(const Digest &);
		protected:
            size_t m_length;
            unsigned char *m_data;
			char *m_str;

		public:
			Digest(const unsigned char *d='\0', const int &l=0);
			virtual ~Digest();
			const unsigned char *getValue() const;
			const char *getString() const;
            const size_t &getLength() const;
	};
}

#endif//__CDL_DIGEST_H__
