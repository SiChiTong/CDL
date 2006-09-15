#ifndef __XWINPROC_H__
#define __XWINPROC_H__

#ifndef WINPROCNAME
#define WINPROCNAME xwinProc
#endif

#define kstate (((XKeyEvent *)(&event))->state)
#define klock  (kstate&LockMask)
#define kshift (kstate&ShiftMask)

void WINPROCNAME(CDL::Window &win, XEvent &event, Display *dpy, ::Window mwin)
{
    static const int keycodes[256]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,45,68,69,70,71,72,73,74,75,76,77,78,79,36,37,38,39,40,33,34,35,88,89,90,91,92,93,94,95,96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,112,113,114,115,116,117,118,119,120,121,122,123,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,160,161,162,163,20,230,231,232,164,165,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,46};
    int k, width=win.getWidth(), height=win.getHeight();

    switch (event.type)
    {
        case ClientMessage:
        case DestroyNotify:
            win.close();
            break;
        case ButtonPress:
            switch (event.xbutton.button)
                    {
                    case Button1:
                        win.setMouseButton(win.getMouseButton()|CDL::Window::MOUSE_LEFT);
                        break;
                    case Button2:
                        win.setMouseButton(win.getMouseButton()|CDL::Window::MOUSE_MIDDLE);
                        break;
                    case Button3:
                        win.setMouseButton(win.getMouseButton()|CDL::Window::MOUSE_RIGHT);
                        break;
                    }
                    break;
                case ButtonRelease:
                    switch (event.xbutton.button)
                    {
                    case Button1:
                        win.setMouseButton(win.getMouseButton()&~CDL::Window::MOUSE_LEFT);
                        break;
                    case Button2:
                        win.setMouseButton(win.getMouseButton()&~CDL::Window::MOUSE_MIDDLE);
                        break;
                    case Button3:
                        win.setMouseButton(win.getMouseButton()&~CDL::Window::MOUSE_RIGHT);
                        break;
                    }
                    break;
                case KeyPress:
                    k=keycodes[XLookupKeysym(&event.xkey,0)&0xFF];
                    if (win.getConsoleKey() == k)
                    {
                        win.toggleConsole();
                    }
                    else
                    {
                        if (win.isConsoleActive())
                        {
                            int rk=k;
                            if ((k >= 'A' && k <= 'Z') && ((klock && kshift) || (!klock && !kshift)))
                                rk|=0x20;
                            win.getConsole().processKey(rk);
                        }
                        else
                        {
                            if ((k >= 'A' && k <= 'Z') && ((klock && kshift) || (!klock && !kshift)))
                                win.setKeyPress(k|0x20);
                            else
                                win.setKeyPress(k);
                            win.setKey(k,true);
                        }
                    }
                    break;
                case KeyRelease:
                    if (XPending(dpy)) // to avoid autorepeat
                    {
                        XEvent pevent;
                        XPeekEvent(dpy, &pevent);
                        if (pevent.type== KeyPress && \
                                pevent.xkey.keycode == event.xkey.keycode && \
                                pevent.xkey.time-event.xkey.time < 2)
                        {
                            XNextEvent(dpy,&pevent);
                            break;
                        }
                    }
                    win.setKey(keycodes[XLookupKeysym(&event.xkey,0)&0xFF],false);
                    break;
                case MotionNotify:
                    win.setMouseX(event.xmotion.x);
                    win.setMouseY(event.xmotion.y);
                    if (win.getFlags()&(CDL::Window::CENTERCURSOR))
                        XWarpPointer(dpy,mwin,mwin,0,0,0,0,width/2,height/2);
                    break;
                default:
                    break;
                }

}


#endif//__XWINPROC_H__
