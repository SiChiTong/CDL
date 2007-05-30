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
            byte *m_data;
            string m_str;

		public:
			Digest(const byte *d='\0', const int &l=0);
			virtual ~Digest();
			const byte *getValue() const;
			const string &getString() const;
            const size_t &getLength() const;
	};
}

#endif//__CDL_DIGEST_H__
