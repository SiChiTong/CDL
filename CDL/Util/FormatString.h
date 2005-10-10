#ifndef __CDL_FORMATSTRING_H__
#define __CDL_FORMATSTRING_H__

#include <CDL/defs.h>

namespace CDL
{
	class DLL_API FormatString
	{
		private:
			char *m_str;

		public:
			FormatString(const char *, ...);
			FormatString(const int &, const char *, ...);
			virtual ~FormatString();
			operator const char *() const;
	};
}

#endif//__CDL_FORMATSTRING_H__
