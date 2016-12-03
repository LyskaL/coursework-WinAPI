#include "RemoveAdminWindow.h"
using namespace UI;

RemoveAdminWindow* RemoveAdminWindow::ptr = nullptr;

RemoveAdminWindow::RemoveAdminWindow(Admins* admins){
	this->admins = admins;
	ptr = this;
}

BOOL RemoveAdminWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void RemoveAdminWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_REMOVEADMIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_REMOVEADMIN_OK) {
		INT size = 50;
		TCHAR* login = new TCHAR[size]{};
		TCHAR* password = new TCHAR[size]{};
		GetWindowText(hLogin, login, size);
		GetWindowText(hPassword, password, size);

		if (admins->FindAdmin(login, password) > 0) {
			admins->remove(login);
			delete[]login;
			delete[]password;
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		else{
			MessageBox(hwnd, TEXT("Администратор с таким именем не найден!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		}
	}
}


BOOL RemoveAdminWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hLogin = GetDlgItem(hwnd, IDC_REMOVEADMIN_LOGIN);
	hPassword = GetDlgItem(hwnd, IDC_REMOVEADMIN_PASS);
	return TRUE;
}

void RemoveAdminWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}