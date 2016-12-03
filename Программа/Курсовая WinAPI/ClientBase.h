#pragma once
#include "Header.h"
#include "Client.h"

class Client;
class ClientBase{
	vector <Client*>* clientBase;

	INT CheckSizeOfArray(INT _size);
	VOID newSizeArray(INT _size);
	VOID copy(vector <Client*> buffer, Client& client, INT index);
	VOID ThatSaveFile(Client* newClient, INT indexSTRING, STRING text);
	VOID recordCreditAccount(Client* newClient, INT indexSTRING, INT& indexCreditAccount, TCHAR* text, TCHAR* buffer, INT i);
	STRING ToStringClientBase();
	VOID countPayments();

public:
	ClientBase();
	~ClientBase();

	BOOL add(Client& client);
	BOOL remove(Client& client);
	BOOL remove(INT index);
	Client* getClientInBase(INT index);
	INT getSize();
	VOID copyInFile();
};

