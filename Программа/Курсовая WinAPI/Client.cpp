#include "Client.h"

//Функция выделяет память всем полям класса
VOID Client::init() {
	number = new vector <Account*>;
}

Client::Client(){
	this->login = TEXT("");
	this->password = TEXT("");
	this->name = TEXT("");
	this->lastName = TEXT("");
	this->middleName = TEXT("");
	this->dateBirth = TEXT("");
	this->seriesPassport = TEXT("");
	this->numberPassport = TEXT("");
	init();
	capacity = 0;
}

Client::Client(STRING login, STRING password, STRING name, STRING lastName, STRING middleName, STRING dateBirth,
	STRING seriesPassport, STRING numberPassport) :Client(){
	this->login = login;
	this->password = password;
	this->name = name;
	this->lastName = lastName;
	this->middleName = middleName;
	this->dateBirth = dateBirth;
	this->seriesPassport = seriesPassport;
	this->numberPassport = numberPassport;
}

Client::~Client(){
	delete[] number;
}


INT Client::getCapacity() const{
	return capacity;
}


STRING Client::getLogin() const{
	return login;
}

STRING Client::getPassword()const{
	return password;
}

STRING Client::getName()const{
	return name;
}

STRING Client::getLastName()const{
	return lastName;
}

STRING Client::getMiddleName()const{
	return middleName;
}

VOID Client::setLogin(STRING _login){
	this->login = _login;
}

VOID Client::setPassword(STRING _password){
	this->password = _password;
}

VOID Client::setName(STRING _name){
	this->name = _name;
}

VOID Client::setLastName(STRING _lastName){
	this->lastName = _lastName;
}

VOID Client::setMiddleName(STRING _middleName){
	this->middleName = _middleName;
}

Client::Client(Client &p) {
	copy(p);
}

vector<Account*>* Client::getArrayNumber() const {
	return number;
}

Account* Client::getNumber(INT i) const{
	return number->at(i);
}

VOID Client::setNumber(Account* _number) {
	capacity++;
	number->push_back(_number);
}

STRING Client::getDateBirth() const{
	return dateBirth;
}

STRING Client::getSeriesPassport() const{
	return seriesPassport;
}

STRING Client::getNumberPassport() const{
	return numberPassport;
}

VOID Client::setDateBirth(STRING _dateBirth) {
	this->dateBirth = _dateBirth;
}

VOID Client::setSeriesPassport(STRING _seriesPassport){
	this->seriesPassport = _seriesPassport;
}

VOID Client::setNumberPassport(STRING _numberPassport){
	this->numberPassport = _numberPassport;
}

VOID Client::setCapacity(INT capacity){
	this->capacity = capacity;
}

VOID Client::copy(Client& name) {
	setLogin(name.getLogin());
	setPassword(name.getPassword());
	setName(name.getName());
	setLastName(name.getLastName());
	setMiddleName(name.getMiddleName());
	setDateBirth(name.getDateBirth());
	setSeriesPassport(name.getSeriesPassport());
	setNumberPassport(name.getNumberPassport());

	capacity = 0;
	number = new vector <Account*>;
	for (int i = 0; i < name.getCapacity(); ++i) {
		setNumber(name.getArrayNumber()->at(i));
	}
}

STRING Client::ClientToString() {
	STRING* temp = new STRING;
	TCHAR capacity[50]{};
	*temp += TEXT("Логин:  ");
	*temp += getLogin();
	*temp += TEXT("\r\n");
	*temp += TEXT("Пароль: ******");
	*temp += TEXT("\r\n \r\n");
	*temp += TEXT("Ф.И.О:  ");
	*temp += getLastName();
	*temp += TEXT("  ");
	*temp += getName();
	*temp += TEXT("  ");
	*temp += getMiddleName();
	*temp += TEXT("\r\n");
	*temp += TEXT("Дата рождения:  ");
	*temp += getDateBirth();
	*temp += TEXT("\r\n");
	*temp += TEXT("Паспортные данные:  ");
	*temp += getSeriesPassport();
	*temp += TEXT("  ");
	*temp += getNumberPassport();
	*temp += TEXT("\r\n");

	wsprintf(capacity, TEXT("Количество счетов:  %d"), getCapacity());
	*temp += capacity;

	return *temp;
}

STRING Client::AccountToString(STRING& temp){
	TCHAR capacity[50]{};
	temp += TEXT("\r\n \r\n");
	if (getCapacity() > 0) {
		for (int j = 0; j < getCapacity(); ++j) {
			temp += TEXT("Номер счёта:  ");
			temp += getArrayNumber()->at(j)->getNumberAccount();
			temp += TEXT("\r\n");
			wsprintf(capacity, TEXT("Сумма: %d грн"), getArrayNumber()->at(j)->getSumCredit());
			temp += capacity;
			temp += TEXT("\r\n \r\n");
		}
	}
	return temp;
}