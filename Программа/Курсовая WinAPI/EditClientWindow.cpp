#include "EditClientWindow.h"
using namespace UI;

EditClientWindow* EditClientWindow::ptr = nullptr;

EditClientWindow::EditClientWindow(Client* client){
	this->client = client;
	ptr = this;
}

BOOL EditClientWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void EditClientWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_EDITWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_EDITWIN_EDIT) {
		INT size = 50;
		TCHAR* text = new TCHAR[size]{};
		GetWindowText(hLogin, text, size);
		client->setLogin(text);
		GetWindowText(hPassword, text, size);
		client->setPassword(text);
		GetWindowText(hLastName, text, size);
		client->setLastName(text);
		GetWindowText(hName, text, size);
		client->setName(text);
		GetWindowText(hMiddleName, text, size);
		client->setMiddleName(text);
		GetWindowText(hBirthday, text, size);
		client->setDateBirth(text);
		GetWindowText(hSerialPassport, text, size);
		client->setSeriesPassport(text);
		GetWindowText(hNumberPassport, text, size);
		client->setNumberPassport(text);
		delete[]text;
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

BOOL EditClientWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hLogin = GetDlgItem(hwnd, IDC_EDWIN_LOGIN);
	hPassword = GetDlgItem(hwnd, IDC_EDWIN_PASS);
	hLastName = GetDlgItem(hwnd, IDC_EDWIN_LASTNAME);
	hName = GetDlgItem(hwnd, IDC_EDWIN_NAME);
	hMiddleName = GetDlgItem(hwnd, IDC_EDWIN_MIDLENAME);
	hBirthday = GetDlgItem(hwnd, IDC_EDWIN_BIRTHDAY);
	hSerialPassport = GetDlgItem(hwnd, IDC_EDWIN_SERIALPASPORT);
	hNumberPassport = GetDlgItem(hwnd, IDC_EDWIN_NUMBERPASPORT);

	SetWindowText(hLogin, client->getLogin().c_str());
	SetWindowText(hPassword, client->getPassword().c_str());
	SetWindowText(hLastName, client->getLastName().c_str());
	SetWindowText(hName, client->getName().c_str());
	SetWindowText(hMiddleName, client->getMiddleName().c_str());
	SetWindowText(hBirthday, client->getDateBirth().c_str());
	SetWindowText(hSerialPassport, client->getSeriesPassport().c_str());
	SetWindowText(hNumberPassport, client->getNumberPassport().c_str());
	
	return TRUE;
}

void EditClientWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}
