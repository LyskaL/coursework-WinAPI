#pragma once
#include"Header.h"
#include "EditClientWindow.h"
#include "NewAccountWindow.h"
#include "HoldPaymentWindow.h"
#include "DeleteAccountWindow.h"

namespace UI {
	class ClientWindow
	{
	private:
		Client* client;
		HWND hPhoto, hText, hEdit, hNewAccount, hHoldPay, hAccountsList, hHistoriList;
		VOID FillListBoxNumbers();
		VOID FillListBoxPaymentHistory();
		TCHAR* ToStringListBox(INT i);
		VOID GetPaymentHistoryOnSelectedNumber();
		INT FindTheSelectedNumber(INT index);
		VOID createListNumber();

	public:
		static ClientWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		ClientWindow(Client* removeClient);
	};
}