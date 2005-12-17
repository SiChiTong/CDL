#ifndef __CDL_WINDOW_H__
#define __CDL_WINDOW_H__

#include <CDL/Image/Image.h>

namespace CDL
{
    class DLL_API Window
    {
        public:
            static float view_fov, near_clip, far_clip;
            typedef enum {KEY_BACKSPACE=8, KEY_TAB, KEY_ENTER=13, KEY_PAUSE=19, KEY_CAPSLOCK=20, KEY_ESC=27, KEY_SPACE=32, KEY_PGUP=33, KEY_PGDN, KEY_END, KEY_HOME, KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_INSERT=45, KEY_DELETE, KEY_F1=112, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_LSHIFT=160, KEY_RSHIFT, KEY_LCTRL, KEY_RCTRL, KEY_LALT, KEY_RALT} Keycode;
            typedef enum {MOUSE_LEFT=1<<0, MOUSE_RIGHT=1<<1, MOUSE_MIDDLE=1<<2} MOUSE_BUTTONS;
            typedef enum {FULLSCREEN=1<<0, NOCURSOR=1<<1,    CENTERCURSOR=1<<2, NOBORDER=1<<3, DESKTOPLEVEL=1<<4, TRANSPARENT=1<<5} FLAGS;

        protected:
            bool  m_running, m_visible;
            int   m_list[5];
            float m_pixelSize;
            int   m_x, m_y, m_width, m_height;
            int   m_mouseX, m_mouseY, m_mouseB;
            int   m_flags;
            int   m_keyPress;
            bool  m_keys[300];
            void *m_winid;

        public:
            Window();
            void open(const char *title, const int &width, const int &height);
            void print(const int &, const int &, const char *fmt, ...);
            void put(const size_t &x, const size_t &y, const Image &img);
            const float &getPixelSize() const;
            virtual void init() {};
            virtual void update()=0;
            virtual void deinit() {};
            virtual void close();
            const bool &isRunning()  const;
            const bool &isVisible() const;
            const int &getWidth()  const;
            const int &getHeight() const;
            const int &getKeyPress() const;
            void setPosition(const int &, const int &);
            void getPosition(int &, int &);
            void setKeyPress(const int &);
            bool getKey(const int &) const;
            void setKey(const int &, const bool &);
            const int &getFlags() const;
            void  setFlags(const int&);
            const int &getMouseButton() const;
            void  setMouseButton(const int &);
            const int &getMouseX() const;
            void  setMouseX(const int &);
            const int &getMouseY() const;
            void  setMouseY(const int &);
    };
}

#endif//__CDL_WINDOW_H__
