#pragma once
#include"Header.h"
#include "ClientBase.h"

namespace UI {
	class NewClientWindow
	{
	private:
		ClientBase* clients;
		HWND hAdd, hCancel, hLogin, hPassword, hName, hSerial, hNumber, hBirthday;

		OPENFILENAME ofn;
		VOID loadingFile(HWND hwnd);
		VOID SaveNewClient(HWND hwnd);
		VOID SaveNameClient(TCHAR text[], Client* newClient);

	public:
		static NewClientWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		NewClientWindow(ClientBase* clients);
	};
}