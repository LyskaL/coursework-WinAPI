#pragma once
#include"Header.h"
#include "ClientBase.h"

namespace UI {
	class RemoveClientWindow
	{
	private:
		ClientBase* clients;
		Client* removeClient;
		HWND hOK, hCancel, hEditText;

	public:
		static RemoveClientWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		RemoveClientWindow(ClientBase* clients, Client* removeClient);
	};
}