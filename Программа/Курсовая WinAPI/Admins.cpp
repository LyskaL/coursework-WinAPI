
#include "Admins.h"
Admins::~Admins(){}

Admins::Admins() {
	admins = new vector<Admin*>;
	HANDLE file = CreateFile(TEXT("adb.txt"), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	TCHAR buffer[1280]{};
	ReadFile(file, buffer, 1280, NULL, NULL);
	TCHAR temp[100]{}; //массив в котором хранится значение логина или пароля
	INT counter = 0; //счётчик, считает, что на данный ммомент считываем логин или пароль
	Admin* admin = new Admin; 

	INT index = 0; //индекс записываемого символа
	for (int i = 0; i < lstrlen(buffer); ++i) {
		if (counter % 2 == 0 && buffer[i] != ';') {
			temp[index] = buffer[i];
			index++;
		}
		if (counter % 2 != 0 && buffer[i] != ';') {
			temp[index] = buffer[i];
			index++;
		}
		if (buffer[i] == ';') {
			if (counter % 2 == 0) {	admin->login = temp; }
			if (counter % 2 == 1) { admin->password = temp; }

			if (counter % 2 == 1) { 
				admins->push_back(admin); 
				admin = new Admin;
			}
			memset(temp, 0, sizeof(temp)); //обнуляем массив со старым значением
			counter++;
			index = 0;
		}
	}
	CloseHandle(file);
}

INT Admins::getSize() {
	return admins->size();
}

VOID Admins::setLogin(STRING login, INT index) {
	admins->at(index)->login = login;
}

VOID Admins::setPassword(STRING password, INT index){
	admins->at(index)->password = password;
}

STRING Admins::getLogin(INT index){
	return admins->at(index)->login;
}

STRING Admins::getPassword(INT index) {
	return admins->at(index)->password;
}

VOID Admins::add(STRING login, STRING password) {
	Admin* newAd = new Admin;
	newAd->login = login;
	newAd->password = password;
	admins->push_back(newAd);
}

VOID Admins::copyInFile() {
	HANDLE file = CreateFile(TEXT("adb.txt"), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, AdminsToString().c_str(), lstrlen(AdminsToString().c_str())*sizeof(TCHAR), NULL, NULL);

	CloseHandle(file);
}

VOID Admins::remove(STRING login) {
	for (INT i = 0; i < getSize(); ++i) {
		if (login == admins->at(i)->login) {
			admins->erase(admins->begin() + i);
		}
	}
}

STRING Admins::AdminsToString() {
	STRING* temp = new STRING;
	for (INT i = 0; i < getSize(); ++i) {
		*temp += admins->at(i)->login.c_str();
		*temp += TEXT(";");
		*temp += admins->at(i)->password.c_str();
		*temp += TEXT(";");
	}
	return *temp;
}

INT Admins::FindAdmin(STRING login, STRING password) {
	for (INT i = 0; i < getSize(); ++i) {
		if (admins->at(i)->login == login && admins->at(i)->password == password) {
			return i;
		}
	}
	return -1;
}