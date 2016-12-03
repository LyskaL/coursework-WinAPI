#pragma once
#include "Client.h"

namespace UI {
	class DeleteAccountWindow
	{
	private:
		Client* client;
		INT IndexAccount;
		HWND hNumber, hSum;

	public:
		static DeleteAccountWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		DeleteAccountWindow(Client* name, INT IndexAccount);
	};
}