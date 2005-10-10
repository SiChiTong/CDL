//========================================================================
/** @type     C++ Source File
 *  @in     XML.cpp
 *  @author   acornejo
 *  @date
 *   Created:       02:57:45 02/05/2005
 *   Last Update:   05:09:15 17/05/2005
 */
//========================================================================

#include <CDL/Util/XML.h>
#include <string>

typedef std::string string_t;

#define TAB "    "

void writeCString(CDL::OutputStream &out, const char *str)
{
    for (int i=0; i<strlen(str); i++)
        out.writeChar(str[i]);
}

namespace CDL
{
    DEFCLASS("XML");

    void write(OutputStream &out, const DOMNode &node, const int &depth)
    {
        const char *value=node;
        if (strlen(value))
        {
            for (int i=0;i<depth; i++)
                writeCString(out,TAB);
            writeCString(out,FormatString("%s\n", value));
        }
        if (node.getChildCount())
        {
            for (int i=0; i<node.getChildCount(); i++)
            {
                const DOMNode &child=node.getChild(i);
                const char *name=child.getName();
                for (int j=0; j<depth; j++)
                    writeCString(out,TAB);
                if (child.getChildCount() > 0)
                {
                    writeCString(out,FormatString("<%s>\n", name));
                    write(out, child,depth+1);
                    for (int j=0; j<depth; j++)
                        writeCString(out,TAB);
                    writeCString(out,FormatString("</%s>\n", name));
                }
                else
                    writeCString(out, FormatString("<%s>%s</%s>\n", name, (const char *)child, name));
                for (int j=0; j<child.getSiblingCount(); j++)
                {
                    for (int k=0; k<depth; k++)
                        writeCString(out,TAB);
                    if (child.getChildCount() > 0)
                    {
                        writeCString(out,FormatString("<%s>\n", name));
                        write(out, child.getSibling(j), depth+1);
                        for (int k=0; k<depth; k++)
                            writeCString(out,TAB);
                        writeCString(out,FormatString("</%s>\n", name));
                    }
                    else
                        writeCString(out, FormatString("<%s>%s</%s>\n", name, (const char *)child.getSibling(j), name));
                }
            }
        }
    }

    void XML::write(OutputStream &out, const DOMNode &node)
    {
        CDL::write(out,node,0);
    }

    string_t getToken(InputStream &in)
    {
        char c;
        string_t str;

        do
            in.readChar(c);
        while((c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '<') && in.isValid());

        str+=c;
        do
        {
            in.readChar(c);
            str+=c;
        }
        while (c != '>' && c != '<' && in.isValid());

        if (c == '>')
        {
            if (str[0] == '!' || str[0] == '?')
                return getToken(in);
            else
                return "<"+str;
        }
        else
        {
            c=str[str.size()-1];
            while (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '<')
            {
                str.erase(str.size()-1);
                c=str[str.size()-1];
            }

            return str;
        }
    }


    void read(InputStream &in, DOMNode &node)
    {
        do
        {
            string_t str=getToken(in);
            if (str[0] == '<')
            {
                if (str[1] == '/')
                    return;
                string_t name=str.substr(1,str.length()-2);
                const char *cname=name.c_str();
                if (node.find(cname) == '\0')
                    read(in, node[cname]);
                else
                    read(in, node[cname].addSibling());
            }
            else
                node=str.c_str();
        }
        while (in.isValid());
    }


    DOMNode XML::read(InputStream &in)
    {
        DOMNode node;

        CDL::read(in,node);

        return node;
    }
}
