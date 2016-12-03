#include "ClientWindow.h"
using namespace UI;

ClientWindow* ClientWindow::ptr = nullptr;

ClientWindow::ClientWindow(Client* client){
	this->client = client;
	ptr = this;
}

BOOL ClientWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}


void ClientWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (codeNotify == LBN_SELCHANGE) {
		GetPaymentHistoryOnSelectedNumber();
	}
	if (id == IDC_CLWIN_SHOWALLHISTORI) {
		SendMessage(hAccountsList, LB_SETCURSEL, -1, 0);
		FillListBoxPaymentHistory();
	}
	if (id == IDC_CLWIN_EDIT) {
		UI::EditClientWindow edit(client);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_EDITCLIENT_WINDOW), hwnd, UI::EditClientWindow::dlgProc);
		SetWindowText(hText, client->ClientToString().c_str());
	}
	if (id == IDC_CLWIN_NEWACCOUNT) {
		UI::NewAccountWindow newAccount(client);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NEWACCOUNT_WINDOW), hwnd, UI::NewAccountWindow::dlgProc);
		FillListBoxNumbers();
		FillListBoxPaymentHistory();
	}
	if (id == IDC_CLWIN_HOLDPAY || id == IDC_CLWIN_CLOSEACCOUNT){
		INT index = SendMessage(hAccountsList, LB_GETCURSEL, 0, 0);
		if (index < 0) {
			MessageBox(hwnd, TEXT("Выберите номер счёта!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		}
		else {
			TCHAR* temp = new TCHAR[40]{};
			SendMessage(hAccountsList, LB_GETTEXT, index, (LPARAM)temp);
			STRING text = temp;

			for (int i = 8; i < lstrlen(temp); ++i) {
				text.erase(8, 1);
			}

			for (int i = 0; i < client->getCapacity(); ++i){
				if (client->getArrayNumber()->at(i)->getNumberAccount() == text) {
					if (id == IDC_CLWIN_HOLDPAY) {
						UI::HoldPaymentWindow pay(client->getArrayNumber()->at(i));
						DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_HOLDPAYMENT_WINDOW), hwnd, UI::HoldPaymentWindow::dlgProc);
					}
					else{
						INT index = SendMessage(hAccountsList, LB_GETCURSEL, 0, 0);
						UI::DeleteAccountWindow close(client, i);
						DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DELETEACCOUNT_WINDOW), hwnd, UI::DeleteAccountWindow::dlgProc);
					}
					FillListBoxNumbers();
					FillListBoxPaymentHistory();
					return;
				}
			}
		}
	}
}


BOOL ClientWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hText = GetDlgItem(hwnd, IDC_CLWIN_CLIENTTEXT);
	hEdit = GetDlgItem(hwnd, IDC_CLWIN_EDIT);
	hNewAccount = GetDlgItem(hwnd, IDC_CLWIN_NEWACCOUNT);
	hHoldPay = GetDlgItem(hwnd, IDC_CLWIN_HOLDPAY);
	hAccountsList = GetDlgItem(hwnd, IDC_CLWIN_ACCOUNTLIST);
	hHistoriList = GetDlgItem(hwnd, IDC_CLWIN_HISTORY);

	SetWindowText(hText, client->ClientToString().c_str());
	FillListBoxNumbers();
	FillListBoxPaymentHistory();
	return TRUE;
}

void ClientWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

VOID ClientWindow::FillListBoxNumbers() {
	SendMessage(hAccountsList, LB_RESETCONTENT, 0, 0);
	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < client->getCapacity(); ++i) {
			if (client->getArrayNumber()->at(i)->getThisCreditAccount() == TRUE && j == 0 
				|| client->getArrayNumber()->at(i)->getThisCreditAccount() == FALSE && j == 1) {

				SendMessage(hAccountsList, LB_ADDSTRING, 0, (LPARAM)ToStringListBox(i));
			}
		}
	}
}

VOID ClientWindow::FillListBoxPaymentHistory(){
	STRING temp{};
	for (int i = 0; i < client->getCapacity(); ++i) {
		temp += client->getArrayNumber()->at(i)->getPaymentHistory();
		temp += TEXT("\r\n");
	}
	SetWindowText(hHistoriList, temp.c_str());
}

TCHAR* ClientWindow::ToStringListBox(INT i) {
	//Формирование строки для вывода на экран
	TCHAR* stringNumber = new TCHAR[100]{};
	TCHAR sum[20];
	INT sumCredit = client->getArrayNumber()->at(i)->getSumCredit();
	if (client->getArrayNumber()->at(i)->getThisCreditAccount() == TRUE) {
		wsprintf(sum, TEXT("            %d"), sumCredit);
	}
	else {
		wsprintf(sum, TEXT("             %d"), sumCredit);
	}

	STRING number = client->getArrayNumber()->at(i)->getNumberAccount();
	number += TEXT("    ");
	lstrcat(stringNumber, number.c_str());
	lstrcat(stringNumber, sum);

	return stringNumber;
}

VOID ClientWindow::GetPaymentHistoryOnSelectedNumber() {
	INT index = SendMessage(hAccountsList, LB_GETCURSEL, 0, 0);

	if (index < 0) {
		FillListBoxPaymentHistory();
	}

	if (index >= 0) {
		SetWindowText(hHistoriList, client->getArrayNumber()->at(FindTheSelectedNumber(index))->getPaymentHistory().c_str());
	}

}

//принимает индекс считаной строки
//возвращает индекс счёта
INT ClientWindow::FindTheSelectedNumber(INT index) {
	TCHAR* temp = new TCHAR[100]{};
	TCHAR* text = new TCHAR[9]{};
	SendMessage(hAccountsList, LB_GETTEXT, index, (LPARAM)temp);

	INT j = 0;
	for (int i = 0; i < lstrlen(temp); ++i) {
		if (temp[i] != ' ') {
			text[j] = temp[i];
			j++;
		}
		else {
			break;
		}
	}

	STRING tNumber = text;

	if (client->getCapacity() > 0) {
		for (int i = 0; i < client->getCapacity(); ++i) {
			if (client->getArrayNumber()->at(i)->getNumberAccount() == tNumber) {
				delete[]temp;
				delete[]text;
				return i;
			}
		}
	}
}

