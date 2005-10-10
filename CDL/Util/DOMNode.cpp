#include <CDL/Util/DOMNode.h>
#include <map>
#include <vector>
#include <string>

namespace CDL
{
    DEFCLASS("DOMNode");

    struct ltstr {bool operator()(const char *s1, const char *s2) const {return strcmp(s1, s2)<0;}};
    typedef std::string                value_t;
    typedef std::map<const char *,DOMNode*,ltstr> child_t;
    typedef std::vector<DOMNode*>      sibling_t;

    void cleanChilds(child_t *children)
    {
        child_t::const_iterator begin(children->begin()), end(children->end());

        while (begin != end)
        {
            delete begin->second;
            begin++;
        }

        children->clear();
        delete children;
    }

    void cleanSiblings(sibling_t *siblings)
    {
        sibling_t::const_iterator begin(siblings->begin()), end(siblings->end());

        while (begin != end)
        {
            delete *begin;
            begin++;
        }

        siblings->clear();
        delete siblings;
    }

    DOMNode::DOMNode(const char *name)
    {
        m_ref=new int(1);
        m_value=new value_t();
        m_child=new child_t();
        m_sibling=new sibling_t();
        if (name != '\0')
        {
            m_name=new char[strlen(name)+1];
            strcpy(m_name, name);
        }
        else
            m_name='\0';
    }

    DOMNode::DOMNode(const DOMNode &v)
    {
        m_ref=v.m_ref;
        ++(*m_ref);
        m_value=v.m_value;
        m_child=v.m_child;
        m_sibling=v.m_sibling;
        m_name=v.m_name;
    }

    DOMNode::~DOMNode()
    {
        if (!--(*m_ref))
        {
            delete m_ref;
            delete (value_t *)m_value;
            cleanChilds((child_t *)m_child);
            cleanSiblings((sibling_t *)m_sibling);
            if (m_name) delete []m_name;
        }
    }

    const DOMNode& DOMNode::operator=(const DOMNode &v)
    {
        if (this != &v)
        {
            if (!--(*m_ref))
            {
                delete m_ref;
                delete (value_t *)m_value;
                cleanChilds((child_t *)m_child);
                cleanSiblings((sibling_t *)m_sibling);
                if (m_name) delete []m_name;
            }
            m_ref=v.m_ref;
            ++(*m_ref);
            m_value=v.m_value;
            m_child=v.m_child;
            m_sibling=v.m_sibling;
            m_name=v.m_name;
        }

        return *this;
    }

    DOMNode *DOMNode::find(const char *name, const bool &recursive) const
    {
        child_t::const_iterator found=((child_t*)m_child)->find(name);
        child_t::const_iterator begin(((child_t*)m_child)->begin()), end(((child_t*)m_child)->end());
        if (found != end)
            return found->second;
        else
        {
            if (recursive)
            {
                while (begin != end)
                {
                    DOMNode *nfound=begin->second->find(name, recursive);
                    if (nfound)
                        return nfound;
                    begin++;
                }
                return '\0';
            }
            else
                return '\0';
        }
    }

    const DOMNode &DOMNode::operator[](const char *name) const
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            Error_send("Querying for inexistent node [...]%s\\%s\n", m_name, name);
            return *this;
        }
        return *((*((child_t*)m_child))[name]);
    }

    DOMNode& DOMNode::operator[](const char *name)
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            DOMNode *node=new DOMNode(name);
            ((child_t*)m_child)->insert(std::pair<const char *,DOMNode*>(node->getName(), node));
        }
        return *((*((child_t*)m_child))[name]);
    }

    const char *DOMNode::getName() const
    {
        return m_name;
    }

    size_t DOMNode::getChildCount() const
    {
        return ((child_t*)m_child)->size();
    }

    const DOMNode &DOMNode::getChild(const size_t &i) const
    {
        child_t::const_iterator iter=((child_t*)m_child)->begin();
        for (int j=0; j<i; j++, iter++);
        return *(iter->second);
    }

    DOMNode &DOMNode::getChild(const size_t &i)
    {
        child_t::iterator iter=((child_t*)m_child)->begin();
        for (int j=0; j<i; j++, iter++);
        return *(iter->second);
    }

    DOMNode &DOMNode::addChild(const char *name)
    {
        return (*this)[name];
    }

    void DOMNode::deleteChild(const char *name)
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            Error_send("Unable to delete inexistent child [...]%s\\%s\n", m_name, name);
        }
        else
            ((child_t*)m_child)->erase(name);
    }

    size_t DOMNode::getSiblingCount() const
    {
        return ((sibling_t*)m_sibling)->size()+1;
    }

    const DOMNode &DOMNode::getSibling(const size_t &i) const
    {
        if (!i) return *this;
        sibling_t::const_iterator iter=((sibling_t*)m_sibling)->begin();
        iter+=(i-1);
        return *(*iter);
    }

    DOMNode &DOMNode::getSibling(const size_t &i)
    {
        if (!i) return *this;
        sibling_t::iterator iter=((sibling_t*)m_sibling)->begin();
        iter+=(i-1);
        return *(*iter);
    }

    DOMNode &DOMNode::addSibling()
    {
        DOMNode *node=new DOMNode(m_name);
        ((sibling_t*)m_sibling)->push_back(node);
        return *node;
    }

    void DOMNode::deleteSibling(const size_t &i)
    {
        if (!i)
        {
            Error_send("Unable to delete root sibling\n");
            return;
        }
        sibling_t::iterator iter=((sibling_t*)m_sibling)->begin();
        iter+=i;
        ((sibling_t*)m_sibling)->erase(iter);
    }

    void DOMNode::operator=(const int    &x) {(*((value_t*)m_value))=FormatString("%d", x);}
    void DOMNode::operator=(const size_t &x) {(*((value_t*)m_value))=FormatString("%ud", x);}
    void DOMNode::operator=(const float  &x) {(*((value_t*)m_value))=FormatString("%f", x);}
    void DOMNode::operator=(const double &x) {(*((value_t*)m_value))=FormatString("%lf",x);}
    void DOMNode::operator=(const char   &x) {(*((value_t*)m_value))=FormatString("%c", x);}
    void DOMNode::operator=(const bool   &x) {(*((value_t*)m_value))=FormatString("%s", (x ? "true" : "false"));}
    void DOMNode::operator=(const char   *x) {(*((value_t*)m_value))=FormatString("%s", x);}

    DOMNode::operator int()         const {return (int)atoi(((value_t*)m_value)->c_str());}
    DOMNode::operator size_t()      const {return (size_t)atoi(((value_t*)m_value)->c_str());}
    DOMNode::operator float()       const {return (float)atof(((value_t*)m_value)->c_str());}
    DOMNode::operator double()      const {return (double)atof(((value_t*)m_value)->c_str());}
    DOMNode::operator char()        const {return (char)(*((value_t*)m_value))[0];}
    DOMNode::operator bool()        const {return ((*(value_t*)m_value) == "true" ? true : false);}
    DOMNode::operator const char*() const {return ((value_t*)m_value)->c_str();}
}
