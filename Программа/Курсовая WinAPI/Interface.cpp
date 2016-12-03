#include "Header.h"
#include "LoginWindow.h"
#include "ClientBase.h"

INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Cls_OnClose(HWND hwnd);

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmdLine, int nCmdShow) {
	srand(time(NULL));
	ClientBase cl;
	UI::LoginWindow log;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGINWINDOW), NULL, UI::LoginWindow::dlgProc);
}