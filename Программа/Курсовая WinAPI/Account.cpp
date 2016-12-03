#include "Account.h"

Account::Account(){
	numberAccount = generateNumberAccount();
	sum�redit = 0;
	this->name = nullptr;
}

Account::Account(STRING _number, INT summa, Client* _name) {
	setNumberAccount(_number);
	setSumCredit(summa);
	this->name = _name;
	name->setNumber(this);
}

STRING Account::generateNumberAccount() {
	const INT MIN = 100000;
	const INT MAX = 999999;
	LONG number1 = rand() % (MAX - MIN + 1) + MIN;
	TCHAR number[8];
	STRING NewNumber = TEXT("KF");
	_itot_s(number1, number, 10);
	NewNumber += number;
	return NewNumber;
	//_tstoi
}

//��������� ������ � �������, �������� ���� �����������
VOID Account::saveAccount(Client* _name){
	this->name = _name;

	name->setNumber(this);

}

Account::~Account(){}

STRING Account::getNumberAccount() {
	return numberAccount;
}

VOID Account::reduceSumCredit(INT sum) {
	TCHAR temp[100]{};

	this->sum�redit += sum;
	if (ThisCreditAccount == TRUE) {
		wsprintf(temp, TEXT("��������� ������� �� %d   �������: %d    ����: "), sum, sum�redit);
		paymentHistory += temp;
		writeCurrentDate();
	}
	else {
		if (sum > 0) {
			wsprintf(temp, TEXT("���������� ����� �� %d   ������: %d    ����: "), sum, sum�redit);
		}
		else {
			wsprintf(temp, TEXT("�������� �� ����� %d    �������: %d    ����: "), sum, sum�redit);
		}
		paymentHistory += temp;
		writeCurrentDate();
	}

}

VOID Account::setNumberAccount(STRING _numberAccount) {
	this->numberAccount = _numberAccount;
}

INT Account::getSumCredit() {
	return sum�redit;
}

VOID Account::setSumCredit(INT summa) {
	this->sum�redit = summa;
	if (sum�redit < 0) {
		this->ThisCreditAccount = TRUE;
	}
	CreatePaymentHistory();
}

VOID Account::setNameClient(Client* _name){
	this->name = _name;
}

Client* Account::getClient() {
	return name;
}

INT Account::getThisCreditAccount() {
	return ThisCreditAccount;
}

VOID Account::setThisCreditAccount(INT value) {
	this->ThisCreditAccount = value;
}

VOID Account::CreatePaymentHistory() {
	paymentHistory = TEXT("����� �����:  ");
	paymentHistory += numberAccount;
	paymentHistory += TEXT("\r\n");
	if (ThisCreditAccount == TRUE) {
		paymentHistory += TEXT("����������� ����� �������:  ");
	}
	else {
		paymentHistory += TEXT("����� ��� �������� �����:  ");
	}

	TCHAR temp[20]{};
	wsprintf(temp, TEXT("%d ������\r\n"), sum�redit);
	paymentHistory += temp;
	paymentHistory += TEXT("����:  ");
	writeCurrentDate();
}

STRING Account::createFileAddress() {
	STRING str1 = TEXT("������� ��������\\");
	str1 += numberAccount;
	str1 += TEXT(".txt");
	return str1;
}

VOID Account::writeCurrentDate() {
	time_t rawtime;
	struct tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	TCHAR temp[20]{};
	wsprintf(temp, TEXT(" %.2d.%.2d.%.2d "), timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year - 100);

	paymentHistory += temp;
	INT hour = timeinfo.tm_hour;
	INT min = timeinfo.tm_min;

	wsprintf(temp, TEXT(" %.2d:%.2d\r\n"), hour, min);
	paymentHistory += temp;
}

VOID Account::SaveToFilePaymentHistori() {
	HANDLE file = CreateFile(createFileAddress().c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, paymentHistory.c_str(), lstrlen(paymentHistory.c_str())*sizeof(TCHAR), NULL, NULL);

	CloseHandle(file);
}

VOID Account::setPaymentHistory(STRING text) {
	this->paymentHistory = text;
}

STRING Account::getPaymentHistory() {
	return paymentHistory;
}