#pragma once
#include "Header.h"

class Admins {
	struct Admin {
		STRING login;
		STRING password;
	};

	vector<Admin*>* admins;
public:

	VOID newSizeArray(INT _size);

	Admins();
	Admins(STRING login, STRING password);
	~Admins();

	VOID add(STRING login, STRING password);
	VOID remove(STRING login);
	VOID setLogin(STRING login, INT index);
	VOID setPassword(STRING password, INT index);
	VOID copyInFile();
	STRING getLogin(INT index);
	STRING getPassword(INT index);
	INT getSize();

	vector<Admin*>* getArrayAdmins() {
		return admins;
	}

	Admin* getAdminIndex(INT index) {
		return admins->at(index);
	}
	STRING AdminsToString();
	INT FindAdmin(STRING login, STRING password);
};

