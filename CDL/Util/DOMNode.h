#ifndef __CDL_DOMNODE_H__
#define __CDL_DOMNODE_H__

#include <CDL/Util/FormatString.h>

namespace CDL
{
    class DLL_API DOMNode
    {
        private:
			int   *m_ref;
			void  *m_value;
			void  *m_child;
            void  *m_sibling;
            char  *m_name;

        public:
			explicit DOMNode(const char *x='\0');
			DOMNode(const DOMNode &);
			virtual ~DOMNode();
            const DOMNode& operator=(const DOMNode&);

            const char *getName() const;
            DOMNode *find(const char *, const bool &r=false) const;

            const DOMNode& operator[](const char *) const;
            DOMNode&       operator[](const char *);

            size_t getChildCount() const;
            const DOMNode &getChild(const size_t &) const;
            DOMNode       &getChild(const size_t &);
            DOMNode       &addChild(const char *);
            void deleteChild(const char *);

            size_t getSiblingCount() const;
            const DOMNode &getSibling(const size_t &) const;
            DOMNode       &getSibling(const size_t &);
            DOMNode       &addSibling();
            void deleteSibling(const size_t &);

            void operator=(const int &);
            void operator=(const size_t &);
            void operator=(const float &);
            void operator=(const double &);
            void operator=(const char &);
            void operator=(const bool &);
            void operator=(const char *);
            operator int()    const;
            operator size_t() const;
            operator float()  const;
            operator double() const;
            operator char()   const;
            operator bool()   const;
            operator const char*()  const;
    };
}

#endif//__CDL_DOMNODE_H__
