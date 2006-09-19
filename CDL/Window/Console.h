//========================================================================
/** @type     C/C++ Header File
 *  @file     Console.h
 *  @author   acornejo
 *  @date
 *   Created:       15:27:46 14/09/2006
 *   Last Update:   13:38:09 15/09/2006
 */
//========================================================================

#ifndef __CDL_CONSOLE_H__
#define __CDL_CONSOLE_H__

#include <CDL/defs.h>

namespace CDL { class Window; }

namespace CDL
{
    class DLL_API Console
    {
        private:
            Window &m_win;
            void *m_history;
            size_t m_historySize;
            size_t m_historyPos;
            void *m_buffer;
            size_t m_bufferSize;
            size_t m_bufferPos;
            void *m_curLine;
            size_t m_curPos;

        public:
            Console(Window &);
            const Console &operator=(const Console &);
            virtual ~Console();
            const size_t &getHistorySize() const;
            void setHistorySize(const size_t &);
            const size_t &getBufferSize() const;
            void setBufferSize(const size_t &);
            void print(const char *fmt, ...);
            void processKey(const int &);
            void render() const;
    };
}

#include <CDL/Window/Window.h>

#endif//__CDL_CONSOLE_H__
