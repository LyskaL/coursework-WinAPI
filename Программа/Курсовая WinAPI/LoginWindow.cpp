#include "LoginWindow.h"
using namespace UI;

LoginWindow* LoginWindow::ptr = nullptr;

LoginWindow::LoginWindow() {
	clients = new ClientBase;
	admins = new Admins;
	ptr = this;
}

BOOL LoginWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}

BOOL LoginWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hEditLogin = GetDlgItem(hwnd, IDC_LOGWIN_LOGIN);
	hEditPassword = GetDlgItem(hwnd, IDC_LOGWIN_PASS);
	return TRUE;
}

void LoginWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

void LoginWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){

	if (id == IDC_LOGWIN_OK) {
		INT index = AuthorizationCheck();
		if (index > 0) {
			AdminWindow admin(admins, clients, index);
			ShowWindow(hwnd, HIDE_WINDOW);
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ADMIN_WINDOW), hwnd, AdminWindow::dlgProc);
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		else {
			MessageBox(hwnd, TEXT("Логин и пароль введены не верно!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
			SetWindowText(hEditLogin, TEXT(""));
			SetWindowText(hEditPassword, TEXT(""));
		}
	}
	else if (id == IDC_LOGWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}

}

INT LoginWindow::AuthorizationCheck() {
	TCHAR login[100]{};
	TCHAR password[100]{};

	GetWindowText(hEditLogin, login, 100);
	GetWindowText(hEditPassword, password, 100);

	if (lstrlen(login) == 0 || lstrlen(password) == 0) {
		return -1;
	}
	return admins->FindAdmin(login, password);
}


