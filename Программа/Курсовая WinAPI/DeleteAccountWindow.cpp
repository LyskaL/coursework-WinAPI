#include "DeleteAccountWindow.h"
using namespace UI;

DeleteAccountWindow* DeleteAccountWindow::ptr = nullptr;

DeleteAccountWindow::DeleteAccountWindow(Client* client, INT IndexAccount){
	this->client = client;
	ptr = this;
	this->IndexAccount = IndexAccount;
}

BOOL DeleteAccountWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void DeleteAccountWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_DELETEACCOUNTWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_DELETEACCOUNTWIN_OK) {
		client->getArrayNumber()->erase(client->getArrayNumber()->begin() + IndexAccount);
		client->setCapacity(client->getCapacity() - 1);
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

BOOL DeleteAccountWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hNumber = GetDlgItem(hwnd, IDC_DELETEACCOUNTWIN_NUMBER);
	hSum = GetDlgItem(hwnd, IDC_DELETEACCOUNTWIN_SUM);

	SetWindowText(hNumber, client->getArrayNumber()->at(IndexAccount)->getNumberAccount().c_str());
	TCHAR* text = new TCHAR[10]{};
	int sum = client->getArrayNumber()->at(IndexAccount)->getSumCredit();
	wsprintf(text, TEXT("%d"), sum);
	SetWindowText(hSum, text);
	delete[]text;

	return TRUE;
}

void DeleteAccountWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

