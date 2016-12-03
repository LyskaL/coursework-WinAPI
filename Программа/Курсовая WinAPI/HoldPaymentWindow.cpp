#include "HoldPaymentWindow.h"
using namespace UI;

HoldPaymentWindow* HoldPaymentWindow::ptr = nullptr;

HoldPaymentWindow::HoldPaymentWindow(Account* account){
	ptr = this;
	this->newAccount = account;
}

BOOL HoldPaymentWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void HoldPaymentWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_HOLDPAYWIN_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
	if (id == IDC_HOLDPAYWIN_OK) {
		TCHAR sum[10]{};
		GetWindowText(hSum, sum, 10);
		if (lstrlen(sum) > 0) {
			newAccount->reduceSumCredit(_tstoi(sum));
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		}
		else {
			MessageBox(hwnd, TEXT("¬ведите сумму платежа!"), TEXT("ќшибка"), MB_OK | MB_ICONERROR);
		}
	}
}

BOOL HoldPaymentWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hNumber = GetDlgItem(hwnd, IDC_HOLDPAYWIN_NUMBER);
	hSum = GetDlgItem(hwnd, IDC_HOLDPAYWIN_SUM);
	
	SetWindowText(hNumber, newAccount->getNumberAccount().c_str());
	return TRUE;
}

void HoldPaymentWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

