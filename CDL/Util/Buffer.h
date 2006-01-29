#ifndef __CDL_BUFFER_H__
#define __CDL_BUFFER_H__

#include <CDL/Util/Stream.h>

namespace CDL
{
	class Digest;

	class DLL_API Buffer: public RandomAccessIOStream
	{
		protected:
			void *m_data;
            bool  m_clean;
			int   m_length;
            int   m_pos;

		public:
			Buffer(const int &l=0, unsigned char *b='\0');
            Buffer(const char *);
			Buffer(const Buffer &);
			virtual ~Buffer();
			const Buffer &operator=(const Buffer &);
            int read(void *, const int &s);
            int write(const void *, const int &s);
            int  seek(const long &, const int &m=SEEK_SET);
            long tell();
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
