#ifndef __CDL_BUFFER_H__
#define __CDL_BUFFER_H__

#include <CDL/Util/Stream.h>

namespace CDL
{
	class Digest;

	class DLL_API Buffer: public IOStream
	{
		protected:
			void *m_data;
			int   m_length;
            int   m_pos;

		public:
			Buffer(const int &l=0);
			Buffer(const Buffer &);
			virtual ~Buffer();
            int read(void *, const int &s);
            int write(const void *, const int &s);
			Buffer &operator=(const Buffer &);
            bool operator==(const Buffer &) const;
            bool operator!=(const Buffer &) const;
			void *getData() const;
			const int &getLength() const;
			void setLength(const int &);
			void copy(const Buffer &, const int &o=0);
			void clear();
			void encrypt(const long &);
			Digest getMD5() const;
			Digest getSHA1() const;
			Digest getCRC64() const;
	};
}

#include <CDL/Util/Digest.h>

#endif//__CDL_BUFFER_H__
