//========================================================================
/** @type     C++ Source File
 *  @in     XML.cpp
 *  @author   acornejo
 *  @date
 *   Created:       02:57:45 02/05/2005
 *   Last Update:   23:50:15 30/05/2007
 */
//========================================================================

#include <CDL/Util/XML.h>
#include <CDL/Util/string.h>

namespace CDL
{
    DEFCLASS("XML");

    string TAB("    ");

    void write(OutputStream &out, const DOMNode &node, const int &depth)
    {
        const string &value=node.value();
        if (value.length() > 0)
        {
            for (int i=0;i<depth; i++)
                out.writeString(TAB);
            out.writeString(string::printf("%s\n", value.c_str()));
        }
        if (node.getChildCount())
        {
            for (int i=0; i<node.getChildCount(); i++)
            {
                const DOMNode &child=node.getChild(i);
                const char *name=child.getName().c_str();
                for (int j=0; j<child.getSiblingCount(); j++)
                {
                    for (int k=0; k<depth; k++)
                        out.writeString(TAB);
                    if (child.getChildCount() > 0)
                    {
                        out.writeString(string::printf("<%s>\n",name));
                        write(out, child.getSibling(j), depth+1);
                        for (int k=0; k<depth; k++)
                            out.writeString(TAB);
                        out.writeString(string::printf("</%s>\n", name));
                    }
                    else
                        out.writeString(string::printf("<%s>%s</%s>\n", name,child.getSibling(j).value().c_str(),name));
                }
            }
        }
    }

    void XML::write(OutputStream &out, const DOMNode &node)
    {
        CDL::write(out,node,0);
    }

    string getToken(InputStream &in)
    {
        char c;
        string str;

        do
            in.readChar(c);
        while((c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '<') && in.isValid());

        str=str+c;
        do
        {
            in.readChar(c);
            str=str+c;
        }
        while (c != '>' && c != '<' && in.isValid());

        if (c == '>')
        {
            if (str.at(0) == '!' || str.at(0) == '?')
                return getToken(in);
            else
                return '<'+str;
        }
        else
        {
            c=str.at(str.length()-1);
            while (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '<')
            {
                str=str.substr(0,str.length()-1);
                c=str.at(str.length()-1);
            }

            return str;
        }
    }


    void read(InputStream &in, DOMNode &node)
    {
        do
        {
            string str=getToken(in);
            if (str.at(0) == '<')
            {
                if (str.at(1) == '/')
                    return;
                string name=str.substr(1,str.length()-2);
                if (node.find(name) == '\0')
                    read(in, node[name]);
                else
                    read(in, node[name].addSibling());
            }
            else
                node=str;
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
