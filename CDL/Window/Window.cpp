#include <CDL/Window/Window.h>
#include <cstdarg>

#define XFontStr "-*-fixed-medium-r-*-*-15-*-*-*-*-*-iso8859-1"
#define FONT_LIST m_list[0]
#define PUTBEGIN_LIST m_list[1]
#define PUTEND_LIST m_list[2]
#define BACKTEXTURE m_list[3]
#define BACKTEXTURE_LIST m_list[4]


#if defined(Windows_NT)
#include <windows.h>
#define WINPROCNAME glWinProc
#include <CDL/Window/winProc.h>
#else
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#define WINPROCNAME glWinProc
#include <CDL/Window/xwinProc.h>
#include "toon_root.h"

typedef struct
{
    Display *dpy;
    ::Window win;
} winid_t;
#endif


namespace CDL
{
    DEFCLASS("Window");

    float Window::view_fov=60;
    float Window::near_clip=0.01;
    float Window::far_clip=1.0E10;

    size_t rtpot(const size_t &x)
    {
        size_t r=1;

        while (x > r)
            r<<=1;

        return r;
    }

    size_t getFormat(const Image &img)
    {
        switch (img.getType())
        {
            case Image::LUMINANCE:
                return GL_LUMINANCE;
            case Image::LUMINANCE_ALPHA:
                return GL_LUMINANCE_ALPHA;
            case Image::RGB:
                return GL_RGB;
            case Image::BGR:
                return GL_BGR;
            case Image::RGBA:
                return GL_RGBA;
            case Image::BGRA:
                return GL_BGRA;
            default:
                Error_send("Invalid image format to load as texture\n");
                return 0;
        }
    }

    void Window::print(const int &x, const int &y, const char *str, ...)
    {
        va_list ap;
        char strText[256];

        if (str == '\0' || str[0] == '\0') return;

        va_start(ap, str);
        vsprintf(strText,str,ap);
        va_end(ap);

        glTranslatef(x,y,0);
        glRasterPos2f(0,12);
        glPushAttrib(GL_LIST_BIT);
        glListBase(FONT_LIST);
        glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);
        glPopAttrib();
        glTranslatef(-x,-y,0);
    }

    void Window::put(const size_t &x, const size_t &y, const Image &img)
    {
        glPushAttrib(GL_CURRENT_BIT|GL_PIXEL_MODE_BIT|GL_COLOR_BUFFER_BIT);
        glCallList(PUTBEGIN_LIST);
        glRasterPos2i(x,y);
        glCallList(PUTEND_LIST);
        size_t fmt=getFormat(img);
        bool blend= fmt == GL_RGBA ? true : fmt == GL_BGRA ? true : fmt == GL_LUMINANCE_ALPHA ? true : false;
        if (blend)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
        }
        glDrawPixels(img.getWidth(), img.getHeight(), getFormat(img), GL_UNSIGNED_BYTE, img.getData());
        glPopAttrib();
    }

    void initGL(int *m_list, const size_t &width, const size_t &height)
    {
        glViewport(0,0,width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(Window::view_fov, (float)width/(float)height, Window::near_clip, Window::far_clip);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        FONT_LIST=glGenLists(256);
#ifdef Windows_NT
        HFONT font, oldfont;
        HDC hDC=GetDC(GetActiveWindow());
        font=CreateFont(-12, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, \
                CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, "Courier New");
        oldfont=(HFONT)SelectObject(hDC,font);wglUseFontBitmaps(hDC, 0, 256, FONT_LIST);
        SelectObject(hDC,oldfont);DeleteObject((HGDIOBJ)(HFONT)(font));
#else
        Display *dpy=XOpenDisplay(0);
        XFontStruct *font;
        font=XLoadQueryFont(dpy, XFontStr);
        glXUseXFont(font->fid, 0, 256, FONT_LIST);
        XFreeFont(dpy, font);
        XCloseDisplay(dpy);
#endif
        PUTBEGIN_LIST=glGenLists(1);
        glNewList(PUTBEGIN_LIST, GL_COMPILE);
        glPixelZoom(1,-1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0,width,height,0,-1,1);
        glEndList();
        PUTEND_LIST=glGenLists(1);
        glNewList(PUTEND_LIST, GL_COMPILE);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glEndList();
        glGenTextures(1,(unsigned int *)&BACKTEXTURE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, (unsigned int)BACKTEXTURE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D,0,3,rtpot(width),rtpot(height),0,GL_BGR,GL_UNSIGNED_BYTE,NULL);
        glDisable(GL_TEXTURE_2D);
        BACKTEXTURE_LIST=glGenLists(1);
        glNewList(BACKTEXTURE_LIST, GL_COMPILE);
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, BACKTEXTURE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0,1,1,0,-1,1);
        glBegin(GL_QUADS);
        float w=width/(float)rtpot(width), h=height/(float)rtpot(height);
        glTexCoord2f(0,0);glVertex3i(0,0,0);
        glTexCoord2f(0,h);glVertex3i(0,1,0);
        glTexCoord2f(w,h);glVertex3i(1,1,0);
        glTexCoord2f(w,0);glVertex3i(1,0,0);
        glEnd();
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();
        glEndList();
    }

    void deinitGL(int *m_list)
    {
        glDeleteLists(FONT_LIST, 256);
        glDeleteLists(PUTBEGIN_LIST, 1);
        glDeleteLists(PUTEND_LIST, 1);
        glDeleteTextures(1, (unsigned int*)&BACKTEXTURE);
        glDeleteLists(BACKTEXTURE_LIST,1);
    }

    void Window::getDesktopSize(int &width, int &height)
    {
#ifdef Windows_NT
        RECT rect;
        GetWindowRect(GetDesktopWindow(),&rect);
        width=rect.right;
        height=rect.bottom;
#else
        Display *dpy=XOpenDisplay(0);
        int screen=DefaultScreen(dpy), clk;
        XF86VidModeModeLine modeline;
        if (!XF86VidModeGetModeLine(dpy,screen,&clk,&modeline))
        {
            width=height=0;
            Error_send("Unable to query video mode\n");
        }
        else
        {
            width=modeline.hdisplay;
            height=modeline.vdisplay;
        }
        XCloseDisplay(dpy);
#endif
    }

    void Window::setPosition(const int &x, const int &y)
    {
        if (m_winid == NULL)
        {
            Error_send("Window has not been created\n");
        }
        else
        {
#ifdef Windows_NT
            HWND hWnd=*((HWND *)m_winid);
            SetWindowPos(hWnd,HWND_TOPMOST,x,y,0,0,SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER);
#else
            winid_t winid=*((winid_t*)m_winid);
            XMoveWindow(winid.dpy,winid.win,x,y);
#endif
        }
    }

    void Window::getPosition(int &x, int &y)
    {
        if (m_winid == NULL)
        {
            Error_send("Window has not been created\n");
        }
        else
        {
#ifdef Windows_NT
            HWND hWnd=*((HWND *)m_winid);
            RECT rect;
            GetWindowRect(hWnd,&rect);
            x=rect.left;
            y=rect.top;
#else
            winid_t winid=*((winid_t*)m_winid);
            ::Window root, parent, child, *childs;
            size_t width,height,border,depth, num_childs;
            XGetGeometry(winid.dpy,winid.win,&root,&x,&y,&width,&height,&border,&depth);
            XQueryTree(winid.dpy,winid.win,&root,&parent,&childs,&num_childs);
            XFree(childs);
            XTranslateCoordinates(winid.dpy,parent,root,x,y,&x,&y,&child);
#endif
        }
    }
#ifdef Windows_NT
    void Window::open(const char *tit, const int &w, const int &h)
    {
        char                  *classname=new char[32];
        HINSTANCE             hInstance=0;
        HWND                  hWnd;
        HDC                   hDC;
        HGLRC                 hRC;
        WNDCLASS              wc;
        PIXELFORMATDESCRIPTOR pfd;
        DEVMODE               dms;
        DWORD                 dws=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
        RECT                  r;
        MSG                   msg;
        GLuint                pfmt;

        memset(&wc, 0, sizeof(WNDCLASS));
        memset(&dms,0, sizeof(DEVMODE));
        memset(&pfd,0, sizeof(PIXELFORMATDESCRIPTOR));
        sprintf(classname, "%s-%d", __class__, this);

        m_width=w;
        m_height=h;
        m_pixelSize=2.0*tan(DEG2RAD(view_fov/2.0))/(float)m_height;

        wc.style         = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
        wc.lpfnWndProc   = WINPROCNAME;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = classname;

        r.left           = 0;
        r.right          = w;
        r.top            = 0;
        r.bottom         = h;

        pfd.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion     = 1;
        pfd.dwFlags      = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
        pfd.iPixelType   = PFD_TYPE_RGBA;
        pfd.cColorBits   = 24;
        pfd.cRedBits     = 8;
        pfd.cGreenBits   = 8;
        pfd.cBlueBits    = 8;
        pfd.cAlphaBits   = 8;
        pfd.cDepthBits   = 24;
        pfd.cAccumBits   = 0;
        pfd.cStencilBits = 8;

        if (!RegisterClass(&wc))
        {
            Error_send("Unable to register window class\n");
            return;
        }

        if (m_flags&FULLSCREEN)
        {
            if (!EnumDisplaySettings(NULL, ((unsigned long)-1), &dms))
            {
                Error_send("Unable to enum display settings\n");
                PostQuitMessage(0);
                return;
            }
            dms.dmPelsWidth  = w;
            dms.dmPelsHeight = h;
            if (ChangeDisplaySettings(&dms, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            {
                Error_send("Unable to change display settings\n");
                PostQuitMessage(0);
                return;
            }
            dws|=WS_POPUP;
        }
        else
            if (m_flags&NOBORDER)
                dws|=WS_POPUP|WS_VISIBLE;
            else
                dws|=WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX;
        if (m_flags&NOCURSOR)
            ShowCursor(FALSE);

        AdjustWindowRect(&r, dws, false);

        if (!(hWnd=CreateWindow(classname, tit, dws, CW_USEDEFAULT, CW_USEDEFAULT, r.right-r.left, r.bottom-r.top, NULL, NULL, hInstance, this)))
        {
            Error_send("Unable to create window\n");
            PostQuitMessage(0);
            return;
        }
        if (!(hDC=GetDC(hWnd)))
        {
            Error_send("Unable to create device context\n");
            PostQuitMessage(0);
            return;
        }
        if (!(pfmt=ChoosePixelFormat(hDC, &pfd)))
        {
            Error_send("Unable to choose pixel format\n");
            PostQuitMessage(0);
            return;
        }
        if (!SetPixelFormat(hDC, pfmt, &pfd))
        {
            Error_send("Unable to set pixel format\n");
            PostQuitMessage(0);
            return;
        }
        if (!(hRC=wglCreateContext(hDC)))
        {
            Error_send("Unable to create rendering context\n");
            PostQuitMessage(0);
            return;
        }
        if (!wglMakeCurrent(hDC, hRC))
        {
            Error_send("Unable to activate rendering context\n");
            PostQuitMessage(0);
            return;
        }

        m_winid=&hWnd;
        ShowWindow(hWnd, SW_SHOW);
        SetForegroundWindow(hWnd);
        SetFocus(hWnd);
        SetActiveWindow(hWnd);
        SendMessage(hWnd, WM_SIZE, 0, w|h<<16);

        initGL(m_list, m_width, m_height);
        init();
        m_running=true;
        do
        {
            if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
            {
                if (msg.message != WM_QUIT)
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
                else
                    m_running=false;
            }
            else
            {
                update();
                m_keyPress=0;
                SwapBuffers(hDC);
            }
        }
        while (m_running);
        deinit();
        deinitGL(m_list);

        if (m_flags&NOCURSOR) ShowCursor(TRUE);
        if (m_flags&FULLSCREEN) ChangeDisplaySettings(NULL, 0);
        wglMakeCurrent(NULL,NULL);
        wglDeleteContext(hRC);
        ReleaseDC(hWnd, hDC);
        DestroyWindow(hWnd);
        UnregisterClass(classname, hInstance);
        delete []classname;
    }

#else
    void updateBackground(Display *dpy, ::Window win, ::Window root, int *m_list)
    {
        static int x, y, old_x, old_y;
        static Pixmap back=None;
        bool changed=false;

        Atom id=XInternAtom(dpy, "_XROOTPMAP_ID", True);

        if (id != None)
        {
            Atom a;
            int b;
            unsigned long c,d;
            unsigned char *prop=NULL;
            if (XGetWindowProperty(dpy, root, id,0,1,False,XA_PIXMAP,&a,&b,&c,&d,&prop) == Success)
            {
                if (prop)
                {
                    if (*((Pixmap*)prop) != back)
                    {
                        changed=true;
                        back=*((Pixmap*)prop);
                    }
                    XFree(prop);
                }
            }
        }

        if (back != None)
        {
            XWindowAttributes attr;
            unsigned int num_child_windows;
            ::Window child_win, parent_win, root_win, *child_windows;
            XGetWindowAttributes(dpy,win,&attr);
            XQueryTree(dpy,win,&root_win,&parent_win,&child_windows,&num_child_windows);
            XFree(child_windows);
            XTranslateCoordinates(dpy,parent_win,root_win,attr.x,attr.y,&old_x,&old_y,&child_win);
            if (x != old_x || y != old_y)
            {
                changed=true;
                x=old_x;
                y=old_y;
            }
            if (changed)
            {
                XImage *i=XGetImage(dpy, back, x,y,attr.width,attr.height,AllPlanes, ZPixmap);
                glBindTexture(GL_TEXTURE_2D, BACKTEXTURE);
                if (i->red_mask == 0xff)
                    if (i->bits_per_pixel == 32)
                        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,i->width,i->height,GL_RGBA,GL_UNSIGNED_BYTE,i->data);
                    else
                        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,i->width,i->height,GL_RGB,GL_UNSIGNED_BYTE,i->data);
                else
                    if (i->bits_per_pixel == 32)
                        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,i->width,i->height,GL_BGRA,GL_UNSIGNED_BYTE,i->data);
                    else
                        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,i->width,i->height,GL_BGR,GL_UNSIGNED_BYTE,i->data);
                XDestroyImage(i);
            }
        }
        glCallList(BACKTEXTURE_LIST);
    }

    void Window::open(const char *t, const int &w, const int &h)
    {
        m_width=w;
        m_height=h;
        m_pixelSize=2.0*tan(DEG2RAD(view_fov/2.0))/(float)m_height;

        XVisualInfo *vi;
        GLXContext ctx;
        int screen, k, cws=CWColormap|CWEventMask;
        Display *dpy;
        ::Window win, root;
        int attr[]={GLX_RGBA,GLX_DOUBLEBUFFER,GLX_RED_SIZE,8,GLX_GREEN_SIZE,8,GLX_BLUE_SIZE,8,GLX_ALPHA_SIZE,8,GLX_DEPTH_SIZE,24,GLX_STENCIL_SIZE,8, None};
        XSetWindowAttributes at;
        XF86VidModeModeInfo oldMode, **modes, newMode;
        XEvent event;

        if ((dpy=XOpenDisplay(0)) == NULL)
        {
            Error_send("Unable to open X Display\n");
            return;
        }
        screen=DefaultScreen(dpy);
        if ((vi=glXChooseVisual(dpy, screen, attr)) == NULL)
        {
            Error_send("Unable to choose visual\n");
            return;
        }
        if (!(ctx=glXCreateContext(dpy, vi, 0, True)))
        {
            Error_send("Unable to create context\n");
            return;
        }
        if (m_flags&DESKTOPLEVEL)
            root=ToonGetRoot(dpy, screen);
        else
            root=RootWindow(dpy,screen);

        at.colormap=XCreateColormap(dpy, root, vi->visual, AllocNone);
        at.event_mask=KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|StructureNotifyMask;

        if (m_flags&NOBORDER || m_flags&FULLSCREEN)
        {
            cws=cws|CWOverrideRedirect;
            at.override_redirect=True;
        }
        if (m_flags&FULLSCREEN)
        {
            int modeNum;
            XF86VidModeGetAllModeLines(dpy, screen, &modeNum, &modes);
            oldMode=*modes[0];
            newMode=oldMode;
            for (k=0; k<modeNum; k++)
                if (modes[k]->hdisplay == m_width && modes[k]->vdisplay == m_height)
                    newMode=*modes[k];
            XFree(modes);

            if (!XF86VidModeSwitchToMode(dpy, screen, &newMode))
            {
                Error_send("Unable to switch video mode\n");
                return;
            }
            XF86VidModeSetViewPort(dpy, screen, 0, 0);

            win=XCreateWindow(dpy, root, 0,0,m_width,m_height,0,vi->depth,InputOutput,vi->visual,cws,&at);
            XGrabKeyboard(dpy, win, False, GrabModeAsync, GrabModeAsync, CurrentTime);
            XGrabPointer(dpy, win, False, ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, win, None, CurrentTime);
        }
        else
        {
            win=XCreateWindow(dpy, root,0,0,m_width,m_height,0,vi->depth,InputOutput,vi->visual,cws,&at);
            Atom wmDelete=XInternAtom(dpy, "WM_DELETE_WINDOW", True);
            XSetWMProtocols(dpy, win, &wmDelete, 1);
        }
        if (!glXMakeCurrent(dpy, win, ctx))
        {
            Error_send("Unable to activate context\n");
            return;
        }
        if (m_flags&DESKTOPLEVEL)
            root=RootWindow(dpy,screen);
        winid_t winid={dpy,win};
        m_winid=&winid;
        XMapWindow(dpy, win);
        XSizeHints sh;
        sh.flags=PMinSize|PMaxSize;
        sh.min_width=sh.max_width=m_width;
        sh.min_height=sh.max_height=m_height;
        XSetWMNormalHints(dpy,win,&sh);
        XWMHints wh;
        wh.flags=InputHint|StateHint;
        wh.input=True;
        wh.initial_state=NormalState;
        XSetWMHints(dpy,win,&wh);
        XStoreName(dpy, win, t);

        initGL(m_list, m_width, m_height);
        init();
        m_running=true;
        do
        {
            if (XPending(dpy) > 0)
            {
                XNextEvent(dpy, &event);
                WINPROCNAME(*this,event,dpy);
            }
            else
            {
                if (m_flags&TRANSPARENT)
                    updateBackground(dpy,win,root,m_list);
                update();
                m_keyPress=0;
                glXSwapBuffers(dpy, win);
            }
        }
        while(m_running);
        deinit();
        deinitGL(m_list);

        if (m_flags&FULLSCREEN)
        {
            XUngrabPointer(dpy,CurrentTime);
            XUngrabKeyboard(dpy, CurrentTime);
            XF86VidModeSwitchToMode(dpy, screen, &oldMode);
            XF86VidModeSetViewPort(dpy, screen, 0, 0);
        }
        glXMakeCurrent(dpy, None, NULL);
        glXDestroyContext(dpy, ctx);
        XDestroyWindow(dpy,win);
        XCloseDisplay(dpy);
    }
#endif

    Window::Window()
    {
        m_winid=NULL;
        m_visible=false;
        m_running=false;
        m_width=0;
        m_height=0;
        m_flags=0;
        m_mouseX=0;
        m_mouseY=0;
        m_mouseB=0;
        for (int i=0; i<300; i++)
            m_keys[i]=false;
    }

    const float &Window::getPixelSize() const
    {
        return m_pixelSize;
    }

    void Window::close()
    {
        m_running=false;
    }

    const int &Window::getWidth() const
    {
        return m_width;
    }

    const int &Window::getHeight() const
    {
        return m_height;
    }

    const bool &Window::isVisible() const
    {
        return m_visible;
    }

    const bool &Window::isRunning() const
    {
        return m_running;
    }

    const int &Window::getKeyPress() const
    {
        return m_keyPress;
    }

    void Window::setKeyPress(const int &c)
    {
        m_keyPress=c;
    }

    bool Window::getKey(const int &i) const
    {
        if (i < 0 || i > 299)
            return false;
        else
            return m_keys[i];
    }

    void Window::setKey(const int &i, const bool &b)
    {
        if (i < 0 || i > 299)
            return;
        m_keys[i]=b;
    }

    const int &Window::getMouseButton() const
    {
        return m_mouseB;
    }

    void  Window::setMouseButton(const int &b)
    {
        m_mouseB=b;
    }

    const int &Window::getMouseX() const
    {
        return m_mouseX;
    }

    void  Window::setMouseX(const int &x)
    {
        m_mouseX=x;
    }

    const int &Window::getMouseY() const
    {
        return m_mouseY;
    }

    void  Window::setMouseY(const int &y)
    {
        m_mouseY=y;
    }

    const int &Window::getFlags() const
    {
        return m_flags;
    }

    void Window::setFlags(const int &f)
    {
        m_flags=f;
    }
}
