//========================================================================
/** @type     C++ Source File
 *  @file     Console.cpp
 *  @author   acornejo
 *  @date
 *   Created:       16:19:29 14/09/2006
 *   Last Update:   16:28:08 05/12/2007
 */
//========================================================================
#include <CDL/Window/Console.h>
#include <CDL/Util/string.h>
#include <CDL/Util/StringTokenizer.h>
#include <deque> // should replace for list
#include <stdarg.h>
#include <GL/gl.h>

namespace CDL
{

typedef std::deque<string> queue_t;
#define _history ((queue_t*)m_history)
#define history (*_history)
#define _buffer ((queue_t*)m_buffer)
#define buffer (*_buffer)

    Console::Console(Window &win): m_win(win)
    {
        m_win=win;
        m_history=new queue_t();
        m_buffer=new queue_t();
        m_bufferSize=800;
        m_historySize=50;
        m_bufferPos=0;
        m_historyPos=0;
        m_curPos=0;
    }

    Console::~Console()
    {
        history.clear();
        buffer.clear();
        delete _history;
        delete _buffer;
    }

    const Console &Console::operator=(const Console &cons)
    {
        if (this != &cons)
        {
            history=*((queue_t*)cons.m_history);
            buffer=*((queue_t*)cons.m_buffer);
            m_curLine=cons.m_curLine;
            m_win=cons.m_win;
            m_bufferSize=cons.m_bufferSize;
            m_historySize=cons.m_historySize;
            m_bufferPos=cons.m_bufferPos;
            m_historyPos=cons.m_historyPos;
            m_curPos=cons.m_curPos;
        }

        return *this;
    }

    const size_t &Console::getHistorySize() const
    {
        return m_historySize;
    }

    void Console::setHistorySize(const size_t &size)
    {
        m_historySize=size;
        if (m_historySize < history.size())
            history.resize(m_historySize);
    }

    const size_t &Console::getBufferSize() const
    {
        return m_bufferSize;
    }

    void Console::setBufferSize(const size_t &size)
    {
        if (size < 0)
            print("Error: Cannot have a buffer of size 0\n");
        m_bufferSize=size;
        if (m_bufferSize < buffer.size())
            buffer.resize(m_bufferSize);
    }

    void Console::print(const string &str)
    {
        StringTokenizer tokens(string(str),string("\n"));
        while (tokens.hasMoreTokens())
        {
            if (buffer.size() == m_bufferSize)
                buffer.pop_back();
            buffer.push_front(tokens.nextToken());
        }
    }

    void Console::processKey(const int &key)
    {
        size_t buffSize=buffer.size(), histSize=history.size();
        switch(key)
        {
            case Window::KEY_LEFT:
                if (m_curPos > 0) m_curPos--;
                break;
            case Window::KEY_RIGHT:
                if (m_curPos < m_curLine.length()) m_curPos++;
                break;
            case Window::KEY_BACKSPACE:
                if (m_curPos > 0)
                {
                    m_curPos--;
//                    m_curLine.erase(m_curPos,1); missing
                }
                break;
            case Window::KEY_DELETE:
//                m_curLine.erase(m_curPos,1); missing
                break;
            case Window::KEY_UP:
                if (m_historyPos < histSize)
                {
                    m_historyPos++;
                    m_curLine=history[histSize-m_historyPos];
                    m_curPos=m_curLine.length();
                }
                break;
            case Window::KEY_DOWN:
                if (m_historyPos > 0)
                {
                    m_historyPos--;
                    if (!m_historyPos)
                        m_curLine=string::nullstr;
                    else
                        m_curLine=history[history.size()-m_historyPos];
                    m_curPos=m_curLine.length();
                }
                break;
            case Window::KEY_PGUP:
                if (m_bufferPos < buffSize)
                {
                    m_bufferPos+=5;
                    if (m_bufferPos >= buffSize)
                        m_bufferPos=buffSize-1;
                }
                break;
            case Window::KEY_PGDN:
                if (m_bufferPos > 0)
                {
                    m_bufferPos-=5;
                    if (m_bufferPos < 0)
                        m_bufferPos=0;
                }
                break;
            case Window::KEY_ENTER:
                print(string::printf("> %s\n", m_curLine.c_str()));
                if (histSize == m_historySize)
                    history.pop_front();
                history.push_back(m_curLine);
                m_historyPos=0;
                m_curPos=0;
                m_win.processCommand(m_curLine);
                m_curLine=string::nullstr;
                break;
            default:
//                m_curLine.insert(m_curPos,1,(char)key); missing
                m_curPos++;
        }
    }

    void Console::render() const
    {
        size_t width=m_win.getWidth(), height=m_win.getHeight();
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0,width,0,height,-1,1);

        glColor4f(.4,0,0,.6);
        glEnable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
            glVertex2f(0,0);
            glVertex2f(width,0);
            glVertex2f(width,25);
            glVertex2f(0,25);
        glEnd();
        glColor4f(1,1,1,.8);
        glBegin(GL_LINES);
            glVertex2f(width,26);
            glVertex2f(0,26);
        glEnd();
        glColor3f(1,1,1);
        m_win.print(5,0,string::printf("> %s", m_curLine.c_str()));
        m_win.print(23+m_curPos*9,0,"_");
        size_t bufsize=buffer.size(), lines=m_win.getHeight()/18;
        if (bufsize > lines) bufsize=lines;
        for (size_t i=0; i<bufsize; i++)
            m_win.print(5,18*i+20, buffer[i].c_str());
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
    }
}
