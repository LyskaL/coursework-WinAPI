#pragma once
#include "Header.h"
#include "Account.h"
//#include "Service.h"

class Account;
class PaymentHistory
{
	struct Payment {
		STRING number;
		STRING history;
	};

	vector<Payment*>* payments;
	
public:

	PaymentHistory();
	~PaymentHistory();
	STRING createFileAddress(Account& number);
	VOID newPaymentHistory(Account& number);
	VOID makePayment(Account& number, INT sum);
	VOID removePaymentHistory(vector<Account*>* number);
};

