#include <CDL/Util/DOMNode.h>
#include <map>
#include <vector>

namespace CDL
{
    DEFCLASS("DOMNode");

    typedef std::map<string,DOMNode*> child_t;
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

    DOMNode::DOMNode(const string &name)
    {
        m_ref=new int(1);
        m_child=new child_t();
        m_sibling=new sibling_t();
        m_name=name;
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
            cleanChilds((child_t *)m_child);
            cleanSiblings((sibling_t *)m_sibling);
        }
    }

    const DOMNode& DOMNode::operator=(const DOMNode &v)
    {
        if (this != &v)
        {
            if (!--(*m_ref))
            {
                delete m_ref;
                cleanChilds((child_t *)m_child);
                cleanSiblings((sibling_t *)m_sibling);
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

    DOMNode *DOMNode::find(const string &name, const bool &recursive) const
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

    const DOMNode &DOMNode::operator[](const string &name) const
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            Error_send("Querying for inexistent node [...]%s\\%s\n", m_name.c_str(), name.c_str());
            return *this;
        }
        return *((*((child_t*)m_child))[name]);
    }

    DOMNode& DOMNode::operator[](const string &name)
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            DOMNode *node=new DOMNode(name);
            ((child_t*)m_child)->insert(std::pair<string,DOMNode*>(node->getName(), node));
        }
        return *((*((child_t*)m_child))[name]);
    }

    const string &DOMNode::getName() const
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

    DOMNode &DOMNode::addChild(const string &name)
    {
        return (*this)[name];
    }

    void DOMNode::deleteChild(const string &name)
    {
        if (((child_t*)m_child)->find(name) == ((child_t*)m_child)->end())
        {
            Error_send("Unable to delete inexistent child [...]%s\\%s\n", m_name.c_str(), name.c_str());
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

    void DOMNode::operator=(const int    &x) { m_value=string::printf("%d", x);}
    void DOMNode::operator=(const size_t &x) { m_value=string::printf("%ud", x);}
    void DOMNode::operator=(const float  &x) { m_value=string::printf("%f", x);}
    void DOMNode::operator=(const double &x) { m_value=string::printf("%lf",x);}
    void DOMNode::operator=(const char   &x) { m_value=string::printf("%c", x);}
    void DOMNode::operator=(const bool   &x) { m_value=string::printf("%s", (x ? "true" : "false"));}
    void DOMNode::operator=(const string &x) { m_value=x; }
}
