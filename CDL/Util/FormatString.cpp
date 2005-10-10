#include <CDL/Util/FormatString.h>
#include <cstdarg>

namespace CDL
{
	DEFCLASS("FormatString");

	FormatString::~FormatString()
	{
		delete []m_str;
	}

	FormatString::FormatString(const char *fmt, ...)
	{
		m_str=new char[512];
		va_list ap;

		va_start(ap, fmt);
		vsprintf(m_str, fmt, ap);
		va_end(ap);
	}

	FormatString::FormatString(const int &sz, const char *fmt, ...)
	{
		m_str=new char[sz];
		va_list ap;

		va_start(ap, fmt);
		vsprintf(m_str, fmt, ap);
		va_end(ap);
	}

	FormatString::operator const char *() const
	{
		return m_str;
	}
}
