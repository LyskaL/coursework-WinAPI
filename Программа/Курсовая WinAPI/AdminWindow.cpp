#include "AdminWindow.h"
using namespace UI;

AdminWindow* AdminWindow::ptr = nullptr;

AdminWindow::AdminWindow(Admins* admins, ClientBase* clients, INT indexAdmin){
	this->admins = admins;
	this->clients = clients;
	this->indexAdmin = indexAdmin;
	ptr = this;
}

BOOL AdminWindow::dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg) {
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
	}
	return FALSE;
}

BOOL AdminWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam){
	CreateTable(hwnd); // Создаём таблицу(с колонками, нужного размера)

	hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
	hTextAdmin = GetDlgItem(hwnd, IDC_ADMINWIN_ADMIN);
	hSearch = GetDlgItem(hwnd, IDC_ADMINWIN_SEARCH_TEXT);

	STRING nameAdmin = admins->getAdminIndex(indexAdmin)->login;
	SetWindowText(hTextAdmin, nameAdmin.c_str());
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT(" Ф.И.О"));
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT(" сумме кредита"));
	SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)TEXT(" № кредитного счёта"));
	SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
	return TRUE;
}

void AdminWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){

	INT iPos = ListView_GetNextItem(hList, -1, LVNI_SELECTED); //получаем индекс выделенной строки в таблице

	if (id == IDC_ADMINWIN_DELETE_CLIENT) {
		if (iPos < 0) {
			MessageBox(hwnd, TEXT("Не выбран клиент для удаления!"), TEXT("Удаление"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			RemoveClientWindow remove(clients, clients->getClientInBase(iPos));
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_REMOVEWINDOW), hwnd, UI::RemoveClientWindow::dlgProc);
		}
	}
	if (id == IDC_ADMINWIN_NEWCLIENT) {
		UI::NewClientWindow newCl(clients);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NEW_CLIENT_WINDOW), hwnd, UI::NewClientWindow::dlgProc);
	}

	if (id == IDC_ADMINWIN_SEARCH) {
		INT index = searchClient(hwnd);
		//Если index равен -1, то клиент с такими параметрами не найден
		if (index < 0) {
			MessageBox(hwnd, TEXT("Клиентов с заданными параметрами для поиска не зайдено!"), TEXT("Результат поиска"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			UI::ClientWindow cl(clients->getClientInBase(index));
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CLIENTMENU), hwnd, UI::ClientWindow::dlgProc);
			clients->copyInFile();
		}
	}

	if (id ==  IDC_ADMINWIN_NEWADMIN) {
		UI::AddAdminWindow addAd(admins);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NEWADMIN_WINDOW), hwnd, UI::AddAdminWindow::dlgProc);
		admins->copyInFile();
	}

	if (id == IDC_ADMINWIN_DELETEADMIN) {
		UI::RemoveAdminWindow removeAdmin(admins);
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_REMOVEADMIN_WINDOW), hwnd, UI::RemoveAdminWindow::dlgProc);
		admins->copyInFile();
	}

	if (id == IDC_ADMINWIN_SHOW){
		if (iPos < 0){
			MessageBox(hwnd, TEXT("Чтобы отобразить информацию о клиенте, выделите его в таблице! "), TEXT("Информация о клиенте"), MB_OK | MB_ICONERROR);
		}
		else {
			UI::ClientWindow cl(clients->getClientInBase(iPos));
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CLIENTMENU), hwnd, UI::ClientWindow::dlgProc);
			clients->copyInFile();
		}
	}
	refreshListView();
}

void AdminWindow::Cls_OnClose(HWND hwnd){
	EndDialog(hwnd, 0);
}

INT AdminWindow::searchClient(HWND hwnd) {
	TCHAR text[100]{};
	INT indexComboBox = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
	GetWindowText(hSearch, text, 100);


	if (lstrlen(text) < 2) {
		return -1;
	}

	STRING temp = text;
	vector<INT>* indexClients = new vector<INT>;

	for (int i = 0; i < clients->getSize(); i++) {
		if (indexComboBox == 0) {
			STRING name = clients->getClientInBase(i)->getLastName();
			name += TEXT(" ");
			name += clients->getClientInBase(i)->getName();
			name += TEXT(" ");
			name += clients->getClientInBase(i)->getMiddleName();

			if (temp == name) {
				//Возвращаем индекс найденого клинта
				return i;
			}
		}
		else if (indexComboBox == 1) {
			for (int j = 0; j < clients->getClientInBase(i)->getCapacity(); ++j) {
				INT sum = clients->getClientInBase(i)->getArrayNumber()->at(j)->getSumCredit();
				INT a = _tstoi(temp.c_str());
				if (a == sum) {
					indexClients->push_back(i);
				}
			}
		}
		else if (indexComboBox == 2) {
			for (int j = 0; j < clients->getClientInBase(i)->getCapacity(); ++j) {
				STRING number = clients->getClientInBase(i)->getArrayNumber()->at(j)->getNumberAccount();
				if (temp == number) {
					//Возвращаем индекс найденого клинта
					return i;
				}
			}
		}

	}

	if (indexComboBox == 1) {
		if (indexClients->size() > 1) {
			//Вызвать окно для нескольких найденов клиентов
		}
		else if (indexClients->size() == 1) {
			return indexClients->at(0);
		}
	}
	return -1;
}
//Создание таблицы с нужным количеством столбцов и нужными размерами
VOID AdminWindow::CreateTable(HWND hwnd) {
	hList = GetDlgItem(hwnd, IDC_ADMINWIN_LISTCONTROL);
	LVITEM LvItem;
	LVCOLUMN LvCol;
	memset(&LvCol, 0, sizeof(LvCol));                  // Zero Members
	LvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;    // Type of mask
	LvCol.cx = 0x100;                                  // width between each coloum
	LvCol.pszText = TEXT("Клиент ");                            // First Header Text
	
	STRING text;
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&LvCol); // Insert/Show the coloum
	LvCol.cx = 0x50;
	LvCol.pszText = TEXT("Паспорт ");
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&LvCol); // Insert/Show the coloum
	LvCol.cx = 0x59;
	LvCol.pszText = TEXT("№ счёта ");
	SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&LvCol); // Insert/Show the coloum

	fillTable(hList);

	//Выделить строку с определённым индексом
	//SendMessage(hList, LVM_SETITEMSTATE, 0, (LPARAM)&LvItem); // указатель на LVITEM lvItem;
	


}

//Заполняем таблицу базой данных клиентов
VOID AdminWindow::fillTable(HWND hList) {
	for (int i = 0; i < clients->getSize(); i++) {
		TCHAR buff[50]{};
		lstrcat(buff, ToStringNameClient(i).c_str());

		LVITEM lvItem;
		memset(&lvItem, 0, sizeof(lvItem)); // Обнуление структуры
		lvItem.mask = LVIF_TEXT;
		lvItem.state = 0;
		lvItem.stateMask = 0;
		lvItem.iItem = i;
		lvItem.iImage = 0;
		lvItem.iSubItem = 0;
		lvItem.pszText = buff;
		lvItem.cchTextMax = lstrlen(buff);
		ListView_InsertItem(hList, &lvItem);

		memset(buff, 0, sizeof(buff));
		lstrcat(buff, ToStringPassportClient(i).c_str());
		ListView_SetItemText(hList, i, 1, buff);

		memset(buff, 0, sizeof(buff));
		lstrcat(buff, ToStringCreditAccount(i).c_str());
		ListView_SetItemText(hList, i, 2, buff);
	}

	//ListView_SetItemState(hList, 1, 0xF, LVIS_SELECTED); // выделить index строку
	//ListView_SetItemState(hList, 1, 0x0, LVIS_SELECTED); // сбросить index строку

}

//Преобразуем в строку, имя и фамилию клиента по индексу
STRING AdminWindow::ToStringNameClient(INT i) {
	STRING temp = clients->getClientInBase(i)->getLastName();
	temp += TEXT(" ");
	temp += clients->getClientInBase(i)->getName();
	temp += TEXT(" ");
	temp += clients->getClientInBase(i)->getMiddleName();
	return temp;
}

//Преобразуем в строку, паспортный данные клиента по индексу
STRING AdminWindow::ToStringPassportClient(INT i) {
	STRING temp = clients->getClientInBase(i)->getSeriesPassport();
	temp += TEXT(" ");
	temp += clients->getClientInBase(i)->getNumberPassport();
	return temp;
}

//Преобразуем в строку, кредитный номер клиента по индексу
STRING AdminWindow::ToStringCreditAccount(INT i) {
	STRING temp{};
	if (clients->getClientInBase(i)->getCapacity() == 0) {
		temp += TEXT("Номеров нет");
	}
	else {
		temp += clients->getClientInBase(i)->getArrayNumber()->at(0)->getNumberAccount();
	}
	return temp;
}

VOID AdminWindow::refreshListView() {
	for (int i = clients->getSize(); i >= 0; --i) {
		SendMessage(hList, LVM_DELETEITEM, i, 0);
	}
	fillTable(hList);
}