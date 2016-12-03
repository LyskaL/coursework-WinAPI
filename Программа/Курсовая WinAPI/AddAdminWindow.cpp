#include "AddAdminWindow.h"
using namespace UI;

AddAdminWindow* AddAdminWindow::ptr = nullptr;

AddAdminWindow::AddAdminWindow(Admins* admins){
	this->admins = admins;
	ptr = this;
}

BOOL AddAdminWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void AddAdminWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_NEWADMIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_NEWADMIN_OK) {
		INT size = 50;
		TCHAR* login = new TCHAR[size]{};
		TCHAR* password = new TCHAR[size]{};
		GetWindowText(hLogin, login, size);
		GetWindowText(hPassword, password, size);
		if (admins->FindAdmin(login, password) < 0) {
			MessageBox(hwnd, TEXT("Администратор с таким именем уже существует!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		}
		else{
			admins->add(login, password);
			delete[]login;
			delete[]password;
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
	}
}


BOOL AddAdminWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hLogin = GetDlgItem(hwnd, IDC_NEWADMIN_LOGIN);
	hPassword = GetDlgItem(hwnd, IDC_NEWADMIN_PASSWORD);

	return TRUE;
}

void AddAdminWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}