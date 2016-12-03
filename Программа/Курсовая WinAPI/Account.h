#pragma once
#include "Header.h"
#include "Client.h"

class Client;

class Account{
	STRING numberAccount;
	Client* name;
	INT sumСredit;
	INT ThisCreditAccount = FALSE;
	STRING paymentHistory;

	//Время и дата записать в файл 
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
	Погашение кредита
	Принимает:
	- sumRepayment - сумму для погашения кредита;
	Возвращает:
	- true - если кредит успешно погашен
	- false - списание не удалось
	*/
	BOOL repaymentCredit(INT sumRepayment);
	STRING generateNumberAccount();
};