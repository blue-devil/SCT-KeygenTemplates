#include "SCT.h"

// Key generator function. 
void
GenerateSerial(
    HANDLE hEdtName,    // Name edit handle
    HANDLE hEdtSerial)  // Serial edit handle
{
    wchar_t temp[256];
    wchar_t key[256];

    if (GetWindowText(hEdtName, temp, 256)) {
        wcscpy_s(key, sizeof(strSCT), strSCT);
        wcscat_s(key, 256, TEXT("-"));
        wcscat_s(key, 256, temp);
        SetWindowText(hEdtSerial, key);
    }
}

// Adds transparency to the dialog
void
TransparentDialog(
    HWND hWnd,          // Handle of the window to be transparent
    BYTE Transparency)  // Transparency value 0 to 255
{
    HANDLE hUser32 = GetModuleHandle(TEXT("user32"));
    FARPROC pProperty = GetProcAddress(hUser32, "SetLayeredWindowAttributes");
    if (pProperty != 0) {
        LONG val = GetWindowLong(hWnd, GWL_EXSTYLE);

        if (Transparency == 255) {
            val ^= WS_EX_LAYERED;
        }
        else {
            val |= WS_EX_LAYERED;
        }

        SetWindowLong(hWnd, GWL_EXSTYLE, val);
        if (Transparency < 255) {
            SetLayeredWindowAttributes(hWnd, 0, Transparency, LWA_ALPHA);
        }
    }
}

// Loads finger cursor when over a link
LRESULT CALLBACK
CursorLoader(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    RECT rect;
    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        GetClientRect(hWnd, &rect);
        if (GetCapture() != hWnd) {
            isCursorOver = TRUE;
            SetCapture(hWnd);
        }

        if (LOWORD(lParam) > rect.right || HIWORD(lParam) > rect.bottom) {
            isCursorOver = FALSE;
            ReleaseCapture();
        }

        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
        break;

    case WM_MOUSELEAVE:
        InvalidateRect(hWnd, NULL, TRUE);
        return UpdateWindow(hWnd);

    case WM_SETCURSOR:
        hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
        if (NULL == hCursor)
        {
            hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
        }
        SetCursor(hCursor);
        isCursorOver = TRUE;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    default:
        return CallWindowProc(lpOrgStaticProc, hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
