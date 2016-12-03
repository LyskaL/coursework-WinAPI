#pragma once
#include "Header.h"
#include "Client.h"

class Client;

class Account{
	STRING numberAccount;
	Client* name;
	INT sum�redit;
	INT ThisCreditAccount = FALSE;
	STRING paymentHistory;

	//����� � ���� �������� � ���� 
	VOID writeCurrentDate();
	STRING createFileAddress();

public:
	Account();
	Account(STRING _number, INT summa, Client* _name);
	~Account();

	
	STRING getNumberAccount();
	Client* getClient();
	INT getSumCredit();
	INT getThisCreditAccount();
	STRING getPaymentHistory();
	VOID SaveToFilePaymentHistori();

	VOID setNumberAccount(STRING _numberAccount);
	VOID saveAccount(Client* _name);
	VOID setSumCredit(INT summa);
	VOID setAccount(Account* _number);
	VOID setNameClient(Client* _name);
	VOID setThisCreditAccount(INT value);
	VOID setPaymentHistory(STRING text);
	VOID CreatePaymentHistory();

	VOID reduceSumCredit(INT sum);

	/*
	��������� �������
	���������:
	- sumRepayment - ����� ��� ��������� �������;
	����������:
	- true - ���� ������ ������� �������
	- false - �������� �� �������
	*/
	BOOL repaymentCredit(INT sumRepayment);
	STRING generateNumberAccount();
};