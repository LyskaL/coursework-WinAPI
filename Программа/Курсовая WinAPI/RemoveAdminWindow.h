#pragma once
#include"Header.h"
#include "Admins.h"

namespace UI {
	class RemoveAdminWindow
	{
	private:
		Admins* admins;
		HWND hLogin, hPassword;

	public:
		static RemoveAdminWindow* ptr;
		static INT_PTR CALLBACK dlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
		void Cls_OnClose(HWND hwnd);

		RemoveAdminWindow(Admins* admins);
	};
}