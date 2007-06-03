#ifndef __CDL_DOMNODE_H__
#define __CDL_DOMNODE_H__

#include <CDL/Util/string.h>

namespace CDL
{
    class DLL_API DOMNode
    {
        private:
			int   *m_ref;
            string m_value;
			void  *m_child;
            void  *m_sibling;
            string m_name;

        public:
			explicit DOMNode(const string &x=string::nullstr);
			DOMNode(const DOMNode &);
			virtual ~DOMNode();
            const DOMNode& operator=(const DOMNode&);

            const string &getName() const;
            DOMNode *find(const string &, const bool &r=false) const;

            const DOMNode& operator[](const string &) const;
            DOMNode&       operator[](const string &);

            size_t getChildCount() const;
            const DOMNode &getChild(const size_t &) const;
            DOMNode       &getChild(const size_t &);
            DOMNode       &addChild(const string &);
            void deleteChild(const string &);

            size_t getSiblingCount() const;
            const DOMNode &getSibling(const size_t &) const;
            DOMNode       &getSibling(const size_t &);
            DOMNode       &addSibling();
            void deleteSibling(const size_t &);

            const string &value() const {return m_value;}

            void operator=(const int &);
            void operator=(const size_t &);
            void operator=(const float &);
            void operator=(const double &);
            void operator=(const char &);
            void operator=(const bool &);
            void operator=(const string &);
    };
}

#endif//__CDL_DOMNODE_H__
