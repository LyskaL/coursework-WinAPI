#include "RemoveClientWindow.h"
using namespace UI;

RemoveClientWindow* RemoveClientWindow::ptr = nullptr;

RemoveClientWindow::RemoveClientWindow(ClientBase* clients, Client* removeClient) {
	this->clients = clients;
	this->removeClient = removeClient;
	ptr = this;
}

BOOL RemoveClientWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}

void RemoveClientWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_REMOVEWIN_OK) {
		clients->remove(*removeClient);
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}

	if (id == IDC_REMOVEWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

BOOL RemoveClientWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hOK = GetDlgItem(hwnd, IDC_REMOVEWIN_OK);
	hCancel = GetDlgItem(hwnd, IDC_REMOVEWIN_CANCEL);
	hEditText = GetDlgItem(hwnd, IDC_REMOVEWIN_EDITTEXT);
	STRING temp = removeClient->ClientToString();
	SetWindowText(hEditText, removeClient->AccountToString(temp).c_str());

	return FALSE;
}

void RemoveClientWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

