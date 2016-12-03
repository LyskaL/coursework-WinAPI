#pragma once
#include "Client.h"

namespace UI {
	class NewAccountWindow
	{
	private:
		Client* client;
		Account* newAccount;
		HWND hOK, hCancel, hNumber, hSum, hRadioCredit, hRadioAccumulative;

	public:
		static NewAccountWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		NewAccountWindow(Client* client);
	};
}