#pragma once
#include"Header.h"
#include "NewClientWindow.h"
#include "RemoveClientWindow.h"
#include "ClientWindow.h"
#include "AddAdminWindow.h"
#include "RemoveAdminWindow.h"

namespace UI {
	class AdminWindow
	{
	private:
		INT indexAdmin;
		ClientBase* clients;
		Admins* admins;
		HWND hList, hTextAdmin, hComboBox, hSearch;

		VOID CreateTable(HWND hwnd);
		VOID fillTable(HWND hList);
		STRING ToStringNameClient(INT i);
		STRING ToStringPassportClient(INT i);
		STRING ToStringCreditAccount(INT i);
		VOID refreshListView();
		INT searchClient(HWND hwnd);

	public:
		static AdminWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		AdminWindow(Admins* admins, ClientBase* clients, INT indexAdmin);
	};
}