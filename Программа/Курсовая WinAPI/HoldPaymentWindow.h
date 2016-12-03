#pragma once
#include "Account.h"

namespace UI {
	class HoldPaymentWindow
	{
	private:
		Account* newAccount;
		HWND hNumber, hSum;

	public:
		static HoldPaymentWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		HoldPaymentWindow(Account* account);
	};
}