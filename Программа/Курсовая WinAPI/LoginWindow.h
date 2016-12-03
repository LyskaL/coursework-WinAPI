#pragma once
#include"Header.h"
#include "AdminWindow.h"

namespace UI {
	class LoginWindow
	{
		Admins* admins;
		ClientBase* clients;
		INT AuthorizationCheck();

		HWND hEditLogin;
		HWND hEditPassword;

	public:

		static LoginWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);
		
		LoginWindow();
	};
}