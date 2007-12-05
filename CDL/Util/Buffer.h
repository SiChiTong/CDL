#ifndef __CDL_BUFFER_H__
#define __CDL_BUFFER_H__

#include <CDL/Util/string.h>
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
			Buffer(const int &l=0, byte *b='\0');
            Buffer(const string &);
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
            void RC4(const string &);
			Digest getMD5() const;
			Digest getSHA1() const;
            Digest getSHA256() const;
            Digest getSHA384() const;
            Digest getSHA512() const;
			Digest getCRC64() const;
	};
}

#include <CDL/Util/Digest.h>

#endif//__CDL_BUFFER_H__
