#include "Files\SCT.h"
#include "Files\xmp.h"

int WINAPI
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	InitCommonControls();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)MainDialogProc);

	return 0;
}

LRESULT CALLBACK MainDialogProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	switch (uMsg) {
	case WM_INITDIALOG:
		LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SCT_LOGO));
		hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCT_ICON));
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
 
		//Prepare Language Combo
		SendMessage(GetDlgItem(hWnd, IDC_CMB_LANG), CB_ADDSTRING, 0, (LPARAM)L"EN");
		SendMessage(GetDlgItem(hWnd, IDC_CMB_LANG), CB_SETCURSEL, 0, (LPARAM)L"EN");
		SendMessage(GetDlgItem(hWnd, IDC_CMB_LANG), CB_ADDSTRING, 0, (LPARAM)L"TR");

		// Check Music Checkbox
		CheckDlgButton(hWnd, CHK_MUSIC, BST_CHECKED);
		// Play Music
		SCT_XMplay((void *)RCD_MUSIC, 0, 0);

		// Add Transparency to main dialog;
		TransparentDialog(hWnd, 200);

		// Get handle of some components
		hSerial = GetDlgItem(hWnd, IDC_EDT_SERIAL);
		hName = GetDlgItem(hWnd, IDC_EDT_NAME);
		hLink = GetDlgItem(hWnd, IDC_STC_LINK);

		// Hand Cursor and Colorize on link
		SetWindowLongPtr(hLink, GWLP_USERDATA, (LONG_PTR)strBlueDeviLGithub);
		lpOrgStaticProc = (WNDPROC)SetWindowLongPtr(hLink, GWLP_WNDPROC, (LONG_PTR)CursorLoader);
		hBrush = GetSysColorBrush(COLOR_WINDOWTEXT);

		break;

	case WM_CTLCOLORSTATIC:
		if (lParam == (LPARAM)hLink) {
			if (isCursorOver == TRUE) {
				colorStatic = 0x2F32DC;//RGB(255, 0, 0);
			}
			else if (isCursorOver == FALSE) {
				colorStatic = 0x362B00;//RGB(255, 255, 0);
			}
			SetTextColor((HDC)wParam, colorStatic);
			SetBkMode((HDC)wParam, TRANSPARENT);
		}
		else {
			SetBkMode((HDC)wParam, TRANSPARENT);
		}

		return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
		

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case BTN_GEN:
			GenerateSerial(hName, hSerial);
			break;

		case BTN_COPY:
			SendMessage(hSerial, EM_SETSEL, 0, -1);
			SendMessage(hSerial, WM_COPY, 0, 0);
			SendMessage(hSerial, EM_SETSEL, -1, 0);
			break;

		case BTN_ABOUT:
			if (lang == 0) {
				MessageBox(hWnd, strMsgAboutENG, strMsgTitleENG, MB_OK | MB_ICONINFORMATION);
			}
			else if (lang == 1) {
				MessageBox(hWnd, strMsgAbout, strMsgTitle, MB_OK | MB_ICONINFORMATION);
			}
			break;

		case BTN_EXIT:
			EndDialog(hWnd, 0);
			break;

		default:
			break;
		}

		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			switch (LOWORD(wParam)) {
			case CHK_MUSIC:
				if (IsDlgButtonChecked(hWnd, CHK_MUSIC) == BST_UNCHECKED) {
					SCT_XMpause(1);
				}
				else if (IsDlgButtonChecked(hWnd, CHK_MUSIC) == BST_CHECKED) {
					SCT_XMpause(0);
				}
				break;

			case IDC_STC_LINK:
				ShellExecute(hWnd, TEXT("open"), TEXT("https://github.com/blue-devil/"), 0, 0, SW_SHOWNORMAL);
				break;
			}
			break;

		case CBN_SELCHANGE:
			switch (LOWORD(wParam)) {
				int ItemIndex = 0;
			case IDC_CMB_LANG:
				if (SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) == 0) {
					lang = 0;
					SendMessage(GetDlgItem(hWnd, BTN_GEN), WM_SETTEXT, 0, (LPARAM)TEXT("Generate"));
					SendMessage(GetDlgItem(hWnd, CHK_MUSIC), WM_SETTEXT, 0, (LPARAM)TEXT("Music"));
					SendMessage(GetDlgItem(hWnd, BTN_COPY), WM_SETTEXT, 0, (LPARAM)TEXT("C"));
					SendMessage(GetDlgItem(hWnd, IDC_STC_AD), WM_SETTEXT, 0, (LPARAM)TEXT("NAME:"));
				}
				else if (SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0) == 1) {
					lang = 1;
					SendMessage(GetDlgItem(hWnd, BTN_GEN), WM_SETTEXT, 0, (LPARAM)TEXT("Üret"));
					SendMessage(GetDlgItem(hWnd, CHK_MUSIC), WM_SETTEXT, 0, (LPARAM)TEXT("Müzik"));
					SendMessage(GetDlgItem(hWnd, BTN_COPY), WM_SETTEXT, 0, (LPARAM)TEXT("K"));
					SendMessage(GetDlgItem(hWnd, IDC_STC_AD), WM_SETTEXT, 0, (LPARAM)TEXT("AD:"));
				}
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		break;

	case WM_CLOSE:
		DeleteObject(hBrush);
		SCT_XMstop();
		EndDialog(hWnd, 0);
		break;

	default:
		return FALSE;
	}

	return TRUE;
}
