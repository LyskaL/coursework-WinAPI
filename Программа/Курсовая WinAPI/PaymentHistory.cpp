#include "PaymentHistory.h"

PaymentHistory::PaymentHistory(){
	payments = new vector<Payment*>;
}
PaymentHistory::~PaymentHistory(){}

VOID PaymentHistory::newPaymentHistory(Account& number) {
	/*ofstream  file(createFileAddress(number));
	Service h;
	file << "\t ��������� ������� � " << number.getNumberAccount();
	file << "\n\t ����������� ����� �������: " << number.getSumCredit() << " ������";
	file << "\n\t ���� ";
	h.writeCurrentDate(file);
	file << "\n --------------------------------------------------------- " << endl;
	file.close();*/
}

STRING PaymentHistory::createFileAddress(Account& number) {
	STRING str1 = TEXT("������� ��������\\");
	STRING str2 = number.getNumberAccount();
	STRING str3 = TEXT(".txt");
	return str1 += str2 + str3;;
}

//�������� ������ 
VOID PaymentHistory::makePayment(Account& number, INT sum) {
	
}

VOID PaymentHistory::removePaymentHistory(vector<Account*>* number) {
	for (INT i = 0; i < number->size(); ++i) {
		STRING temp = createFileAddress(*number->at(i));
		/*remove(temp1); ��������� ����� � ����� �� �������� �� WIN API!!!!! */ 
	}
}