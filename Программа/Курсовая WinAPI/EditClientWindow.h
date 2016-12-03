#pragma once
#include"Header.h"
#include "Client.h"

namespace UI {
	class EditClientWindow
	{
	private:
		Client* client;
		HWND hLogin, hPassword, hLastName, hName, hMiddleName, hBirthday, hSerialPassport, hNumberPassport, hOK, hCancel;
	

	public:
		static EditClientWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		EditClientWindow(Client* client);
	};
}