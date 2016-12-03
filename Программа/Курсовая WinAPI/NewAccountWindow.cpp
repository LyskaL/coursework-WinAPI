#include "NewAccountWindow.h"
using namespace UI;

NewAccountWindow* NewAccountWindow::ptr = nullptr;

NewAccountWindow::NewAccountWindow(Client* client){
	this->client = client;
	ptr = this;
	this->newAccount = new Account;
}

BOOL NewAccountWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void NewAccountWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_NEWACCOUNTWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_NEWACCOUNTWIN_OK) {
		TCHAR sum [10]{};
		GetWindowText(hSum, sum, 10);

		newAccount->setSumCredit(_tstoi(sum));

		if (SendMessage(hRadioCredit, BM_GETCHECK, 0, 0)){
			newAccount->setThisCreditAccount(1);
		}
		else if (SendMessage(hRadioAccumulative, BM_GETCHECK, 0, 0)) {
			newAccount->setThisCreditAccount(0);
		}

		newAccount->saveAccount(client);
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

BOOL NewAccountWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hNumber = GetDlgItem(hwnd, IDC_NEWACCOUNTWIN_NUMBER);
	hRadioCredit = GetDlgItem(hwnd, IDC_NEWACCOUNTWIN_R_CREDIT);
	hSum = GetDlgItem(hwnd, IDC_NEWACCOUNTWIN_SUM);
	SetWindowText(hNumber, newAccount->getNumberAccount().c_str());
	return TRUE;
}

void NewAccountWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

