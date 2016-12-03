#include "NewClientWindow.h"
using namespace UI;

NewClientWindow* NewClientWindow::ptr = nullptr;

NewClientWindow::NewClientWindow(ClientBase* clients){
	this->clients = clients;
	ptr = this;
}

BOOL NewClientWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}

void NewClientWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	if (id == IDC_NEWCLIENT_DOWNLOAD) {
		loadingFile(hwnd);
	}

	if (id == IDC_NEWCLIENT_ADD) {
		SaveNewClient(hwnd);
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}

	if (id == IDC_NEWCLIENT_CANCEL) {
		SendMessage(hwnd, WM_CLOSE, 0, 0);
	}
}

BOOL NewClientWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	hAdd = GetDlgItem(hwnd, IDC_NEWCLIENT_ADD);
	hCancel = GetDlgItem(hwnd, IDC_NEWCLIENT_CANCEL);

	hLogin = GetDlgItem(hwnd, IDC_NEWCLIENT_LOGIN);
	hPassword = GetDlgItem(hwnd, IDC_NEWCLIENT_PASSWORD);
	hName = GetDlgItem(hwnd, IDC_NEWCLIENT_NAME);
	hSerial = GetDlgItem(hwnd, IDC_NEWCLIENT_SERIAL);
	hNumber = GetDlgItem(hwnd, IDC_NEWCLIENT_NUMBER);
	hBirthday = GetDlgItem(hwnd, IDC_NEWCLIENT_BIRTHDAY);
	return TRUE;
}

void NewClientWindow::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
}

VOID NewClientWindow::loadingFile(HWND hwnd) {
	TCHAR szFileName[MAX_PATH] = TEXT("");
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = TEXT("Bitmap Files (*.bmp)\0*.bmp\0All Files (*.*)\0*.*\0");
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("bmp");
	GetOpenFileName(&ofn);
}

VOID NewClientWindow::SaveNewClient(HWND hwnd) {
	Client* newClient = new Client;
	const INT SIZE = 100;
	TCHAR text[SIZE]{};

	GetWindowText(hLogin, text, SIZE);
	newClient->setLogin(text); //Сохраняем LOGIN клиента
	memset(text, 0, sizeof(text));

	GetWindowText(hPassword, text, SIZE);
	newClient->setPassword(text); //Сохраняем PASSWORD клиента
	memset(text, 0, sizeof(text));

	GetWindowText(hName, text, SIZE);
	SaveNameClient(text, newClient); //Сохраняем Ф.И.О клиента
	memset(text, 0, sizeof(text));

	GetWindowText(hSerial, text, SIZE);
	newClient->setSeriesPassport(text); //Сохраняем серийный номер паспорта клиента
	memset(text, 0, sizeof(text));

	GetWindowText(hNumber, text, SIZE);
	newClient->setNumberPassport(text); //Сохраняем номер паспорта клиента
	memset(text, 0, sizeof(text));

	GetWindowText(hBirthday, text, SIZE);
	newClient->setDateBirth(text); //Сохраняем дату рождения клиента
	memset(text, 0, sizeof(text));

	newClient->setCapacity(0);
	clients->add(*newClient);
}

VOID NewClientWindow::SaveNameClient(TCHAR text[], Client* newClient) {
	const INT SIZE = 50;
	TCHAR temp[SIZE]{};
	INT index = 0;
	INT counter = 0;
	for (int i = 0; i < lstrlen(text); ++i) {
		if (text[i] == ' ') {
			if (counter == 0) {
				newClient->setLastName(temp);
			}
			else if (counter == 1) {
				newClient->setName(temp);
			}
			memset(temp, 0, sizeof(temp));
			index = 0;
			counter++;
			continue;
		}
		temp[index] = text[i];
		index++;

		if (i == lstrlen(text) - 1) {
			newClient->setMiddleName(temp);
		}
	}
}