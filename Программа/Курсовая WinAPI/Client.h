#pragma once
#include "Header.h"
#include "Account.h"

class Account;
class Client{
	STRING login;
	STRING password;

	STRING name;
	STRING lastName;
	STRING middleName;

	STRING dateBirth;
	STRING seriesPassport;
	STRING numberPassport;

	vector<Account*>* number;
	INT capacity;

	static const INT SIZE_ARRAY = 50;
	VOID init();

public:
	Client();
	Client(Client &p);
	Client(STRING login, STRING password, STRING name, STRING lastName, STRING middleName, STRING dateBirth, STRING seriesPassport, STRING numberPassport);
	~Client();

	STRING getLogin() const;
	STRING getPassword() const;

	STRING getName() const;
	STRING getLastName() const;
	STRING getMiddleName() const;

	STRING getDateBirth() const;
	STRING getSeriesPassport() const;
	STRING getNumberPassport() const;
	INT getCapacity() const;

	Account* getNumber(INT i) const;
	vector<Account*>* getArrayNumber() const;

	VOID saveCreditAccount(Account* num);/////////

	VOID setLogin(STRING _login);
	VOID setPassword(STRING _password);

	VOID setName(STRING _name);
	VOID setLastName(STRING _lastName);
	VOID setMiddleName(STRING _middleName);

	VOID setNumber(Account* _number);

	VOID setDateBirth(STRING _dateBirth);
	VOID setSeriesPassport(STRING _seriesPassport);
	VOID setNumberPassport(STRING _numberPassport);
	VOID setCapacity(INT capacity);

	STRING ClientToString();
	STRING AccountToString(STRING& temp);
	VOID copy(Client& name);
};