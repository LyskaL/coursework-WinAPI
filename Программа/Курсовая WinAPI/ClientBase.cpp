#include "ClientBase.h"

ClientBase::ClientBase(){
	clientBase = new vector<Client*>;
	Client* newClient = new Client;
	HANDLE file = CreateFile(TEXT("clb.txt"), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	TCHAR buffer[3280]{};
	ReadFile(file, buffer, 3280, NULL, NULL);

	INT index = 0;
	INT indexSTRING = 0; //индекс считываемой строки ";"
	INT indexCOUNTER = 0; //индекс клиента
	TCHAR text[100] {};
	BOOL metCapacity = FALSE; //Дошли ли мы до capacity
	INT indexCreditAccount = 0; //счётчик кредитных счетов
	for (int i = 0; i < lstrlen(buffer); ++i){
		//Если мы доходим до количества кредитных счетов, то
		if (indexSTRING == 8) {
			//выставляем флаг в тру!
			metCapacity = TRUE;
			//сохраняем число в текст
			text[index] = buffer[i];
			index = 0; //индекст символа в тексте
			if (_tstoi(text) > 0){
				for (int i = 0; i < _tstoi(text); i++) {
					Account* temp = new Account;
					temp->setNumberAccount(TEXT(""));
					temp->saveAccount(newClient);
				}
				indexSTRING++;
				i++;
				memset(text, 0, sizeof(text)); //обнуляем массив со старым значением
				index = 0;
				continue;
			}
			else {
				indexCOUNTER++;
				indexSTRING = 0;
				clientBase->push_back(newClient);
				newClient = new Client;
				metCapacity = FALSE;
				memset(text, 0, sizeof(text)); //обнуляем массив со старым значением
				index = 0;
				i++;
				continue;
			}
		}

		if (buffer[i] == ';') {
			if (indexSTRING < 8) {
				ThatSaveFile(newClient, indexSTRING, text);
			}
			if (metCapacity) {
				recordCreditAccount(newClient, indexSTRING, indexCreditAccount, text, buffer, i);
			}
			indexSTRING++;
			memset(text, 0, sizeof(text)); //обнуляем массив со старым значением
			index = 0;
		}
		else {
			text[index] = buffer[i];
			index++;
		}
		if (indexCreditAccount == newClient->getCapacity() && metCapacity) {
			clientBase->push_back(newClient);
			newClient = new Client;
			indexCOUNTER++;
			indexSTRING = 0;
			metCapacity = FALSE;
			index = 0;
			indexCreditAccount = 0;
		}

	}
	CloseHandle(file);

	countPayments();
}

VOID ClientBase::countPayments(){
	for (int i = 0; i < clientBase->size(); ++i) {
		for (int j = 0; j < clientBase->at(i)->getCapacity(); ++j) {
			STRING temp = TEXT("История платежей\\");
			temp += clientBase->at(i)->getArrayNumber()->at(j)->getNumberAccount();
			temp += TEXT(".txt");

			HANDLE file = CreateFile(temp.c_str(), GENERIC_READ, 0, NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			TCHAR buffer[2280]{};
			ReadFile(file, buffer, 2280, NULL, NULL);
			clientBase->at(i)->getArrayNumber()->at(j)->setPaymentHistory(buffer);
			CloseHandle(file);
		}
	}
}

VOID ClientBase::recordCreditAccount(Client* newClient, INT indexSTRING, INT& indexCreditAccount, TCHAR* text, TCHAR* buffer, INT i){
	if (indexCreditAccount == newClient->getCapacity()) {
		return;
	}
	else {
		if ((indexSTRING % 2) != 0) {
			newClient->getArrayNumber()->at(indexCreditAccount)->setNumberAccount(text);
		}
		else{
			newClient->getArrayNumber()->at(indexCreditAccount)->setSumCredit(_tstoi(text));
			if (_tstoi(text) < 0) {
				newClient->getArrayNumber()->at(indexCreditAccount)->setThisCreditAccount(TRUE);
			}
			indexCreditAccount++;
		}
	}
}

ClientBase::~ClientBase(){}


VOID ClientBase::ThatSaveFile(Client* newClient, INT indexSTRING, STRING text) {
	switch (indexSTRING) {
	case 0:
		newClient->setLogin(text);
		break;
	case 1:
		newClient->setPassword(text);
		break;
	case 2:
		newClient->setLastName(text);
		break;
	case 3:
		newClient->setName(text);
		break;
	case 4:
		newClient->setMiddleName(text);
		break;
	case 5:
		newClient->setDateBirth(text);
		break;
	case 6:
		newClient->setSeriesPassport(text);
		break;
	case 7:
		newClient->setNumberPassport(text);
		break;
	}
}

VOID ClientBase::copy(vector <Client*> buffer, Client& client, INT index) {
	buffer[index]->setLogin(client.getLogin());
	buffer[index]->setPassword(client.getPassword());
	buffer[index]->setName(client.getName());
	buffer[index]->setLastName(client.getLastName());
	buffer[index]->setMiddleName(client.getMiddleName());
	buffer[index]->setDateBirth(client.getDateBirth());
	buffer[index]->setSeriesPassport(client.getSeriesPassport());
	buffer[index]->setNumberPassport(client.getNumberPassport());


	for (INT i = 0; i < client.getCapacity(); ++i) {
		buffer[index]->setNumber(client.getArrayNumber()->at(i));
	}
}

INT ClientBase::getSize() {
	return clientBase->size();
}

BOOL ClientBase::add(Client& client) {
	clientBase->push_back(&client);
	copyInFile();
	return true;
}

BOOL ClientBase::remove(Client& client) {

	for (INT i = 0; i < clientBase->size(); ++i) {
		if (clientBase->at(i)->getLogin() == client.getLogin() &&
			clientBase->at(i)->getPassword() == client.getPassword() &&
			clientBase->at(i)->getLastName() == client.getLastName()) {
			/*p.removePaymentHistory(*clientBase[i]->getArrayNumber(), clientBase[i]->getCapacity());*/
			clientBase->erase(clientBase->begin() + i);
			copyInFile();
			return true;
		}
	}
	return false;
}

BOOL ClientBase::remove(INT index) {

	/*HANDLE file = CreateFile(TEXT("База клиентов.txt"), GENERIC_WRITE, 0, NULL,
	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	TCHAR buff[10000];
	wsprintf(buff, TEXT("Lyuda;2569lu;Лыска;Людмила;Юрьевна;10.03.1993;АН;796012;"));
	WriteFile(file, buff, lstrlen(buff)*sizeof(TCHAR), NULL, NULL);
	CloseHandle(file);*/


	/*PaymentHistory p;
	p.removePaymentHistory(*clientBase[index]->getArrayNumber(), clientBase[index]->getCapacity());*/
	clientBase->erase(clientBase->begin() + index);
	copyInFile();
	return true;
}


Client* ClientBase::getClientInBase(INT index) {
	return clientBase->at(index);
}

VOID ClientBase::copyInFile() {
	HANDLE file = CreateFile(TEXT("clb.txt"), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, ToStringClientBase().c_str(), lstrlen(ToStringClientBase().c_str())*sizeof(TCHAR), NULL, NULL);

	CloseHandle(file);
}

STRING ClientBase::ToStringClientBase() {
	STRING* temp = new STRING;
	for (INT i = 0; i < getSize(); ++i) {
		TCHAR capacity[10]{};
		*temp += clientBase->at(i)->getLogin().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getPassword().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getLastName().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getName().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getMiddleName().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getDateBirth().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getSeriesPassport().c_str();
		*temp += TEXT(";");
		*temp += clientBase->at(i)->getNumberPassport().c_str();
		*temp += TEXT(";");
		
		wsprintf(capacity, TEXT("%d"), clientBase->at(i)->getCapacity());
		*temp += capacity;
		*temp += TEXT(";");

		if (_tstoi(capacity) > 0) {
			for (int j = 0; j < clientBase->at(i)->getCapacity(); ++j) {
				*temp += clientBase->at(i)->getArrayNumber()->at(j)->getNumberAccount();
				*temp += TEXT(";");
				wsprintf(capacity, TEXT("%d"), clientBase->at(i)->getArrayNumber()->at(j)->getSumCredit());
				*temp += capacity;
				*temp += TEXT(";");
				clientBase->at(i)->getArrayNumber()->at(j)->SaveToFilePaymentHistori();
			}
		}
	}

	return *temp;
}