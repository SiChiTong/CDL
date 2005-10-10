#ifndef __WINPROC_H__
#define __WINPROC_H__

#ifndef WINPROCNAME
#define WINPROCNAME winProc
#endif

using CDL::Window;

LRESULT CALLBACK WINPROCNAME(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lret=0;
    Window *win=(Window *)GetWindowLong(hWnd, GWL_USERDATA);

    switch(uMsg)
    {
    case WM_CREATE:
        SetWindowLong(hWnd, GWL_USERDATA, (LONG)(((CREATESTRUCT *)lParam)->lpCreateParams));
        break;
    case WM_MOUSEMOVE:
        {
            POINT point;
            GetCursorPos(&point);
            ScreenToClient(hWnd, &point);
            win->setMouseX(point.x);
            win->setMouseY(point.y);
            if (win->getFlags()&Window::CENTERCURSOR)
            {
                point.x=win->getWidth()/2;
                point.y=win->getHeight()/2;
                ClientToScreen(hWnd, &point);
                SetCursorPos(point.x, point.y);
            }
        }
        break;
    case WM_KEYDOWN:
        {
        int kshift=GetKeyState(VK_SHIFT) < 0, klock=GetKeyState(VK_CAPITAL)&0x01;
        if ((wParam >= 'A' && wParam <= 'Z') && ((klock && kshift) || (!klock && !kshift)))
            win->setKeyPress(wParam|0x20);
        else
            win->setKeyPress(wParam);
        }
        win->setKey(wParam,true);
        break;
    case WM_KEYUP:
        win->setKey(wParam,false);
        break;
    case WM_LBUTTONDOWN:
        win->setMouseButton(win->getMouseButton()|Window::MOUSE_LEFT);
        break;
    case WM_LBUTTONUP:
        win->setMouseButton(win->getMouseButton()&~Window::MOUSE_LEFT);
        break;
    case WM_MBUTTONDOWN:
        win->setMouseButton(win->getMouseButton()|Window::MOUSE_MIDDLE);
        break;
    case WM_MBUTTONUP:
        win->setMouseButton(win->getMouseButton()&~Window::MOUSE_MIDDLE);
        break;
    case WM_RBUTTONDOWN:
        win->setMouseButton(win->getMouseButton()|Window::MOUSE_RIGHT);
        break;
    case WM_RBUTTONUP:
        win->setMouseButton(win->getMouseButton()&~Window::MOUSE_RIGHT);
        break;
    case WM_DESTROY:
        win->close();
        break;
    default:
        lret=DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return lret;
}

#endif//__WINPROC_H__

