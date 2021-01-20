#include "User.hpp"

User User::vectorOfStringsToModel(std::vector<std::string> data) {
	return User(
		std::stoi(data[0]),			// ID
		data[1],					// Login
		data[2],					// First Name
		data[3],					// Last Name
		data[4],					// Phone
		data[5],					// Address
		data[6],					// Register Date
		Utils::strToBool(data[7])	// isAdmin
	);
}

std::string User::modelToString() {
	return std::to_string(getId()) + ';'
		+ getLogin() + ';'
		+ getFirstName() + ';'
		+ getLastName() + ';'
		+ getPhone() + ';'
		+ getAddress() + ';'
		+ getRegisterDate() + ';'
		+ Utils::boolToStr(getIsAdmin());
}

void User::setId(int newId) {
	id = newId;
}

void User::setIsAdmin(bool newIsAdmin) {
	isAdmin = newIsAdmin;
}

User::User() {
	setId(0);
	setLogin("");
	setFirstName("");
	setLastName("");
	setPhone("");
	setAddress("");
	setRegisterDate(Utils::nowAsString());
	setIsAdmin(false);
}

User::User(
	int newId,
	std::string newLogin,
	std::string newFirstName,
	std::string newLastName,
	std::string newPhone,
	std::string newAddress,
	std::string newRegisterDate,
	bool newIsAdmin
) {
	setId(newId);
	setLogin(newLogin);
	setFirstName(newFirstName);
	setLastName(newLastName);
	setPhone(newPhone);
	setAddress(newAddress);
	setRegisterDate(newRegisterDate);
	setIsAdmin(newIsAdmin);
}

void User::setLogin(std::string newLogin) {
	login = newLogin;
}

void User::setFirstName(std::string newFirstName) {
	firstName = newFirstName;
}

void User::setLastName(std::string newLastName) {
	lastName = newLastName;
}

void User::setPhone(std::string newPhone) {
	phone = newPhone;
}

void User::setAddress(std::string newAddress) {
	address = newAddress;
}

void User::setRegisterDate(std::string newRegisterDate) {
	registerDate = newRegisterDate;
}

int User::getId() {
	return id;
}

std::string User::getLogin() {
	return login;
}

std::string User::getFirstName() {
	return firstName;
}

std::string User::getLastName() {
	return lastName;
}

bool User::getIsAdmin() {
	return isAdmin;
}

std::string User::getPhone() {
	return phone;
}

std::string User::getAddress() {
	return address;
}

std::string User::getRegisterDate() {
	return registerDate;
}
