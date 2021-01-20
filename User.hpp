#pragma once
#include <string>
#include <vector>
#include "Utils.hpp"

class User {
	int id;
	std::string login;
	std::string firstName;
	std::string lastName;
	bool isAdmin;
	std::string phone;
	std::string address;
	std::string registerDate;

public:
	User();
	User(
		int newId,
		std::string newLogin,
		std::string newFirstName,
		std::string newLastName,
		std::string newPhone,
		std::string newAddress,
		std::string newRegisterDate,
		bool newIsAdmin
	);
	void setId(int newId);
	void setLogin(std::string newLogin);
	void setFirstName(std::string newFirstName);
	void setLastName(std::string newLastName);
	void setPhone(std::string newPhone);
	void setAddress(std::string newAddress);
	void setRegisterDate(std::string newRegisterDate);
	void setIsAdmin(bool newIsAdmin);
	int getId();
	std::string getLogin();
	std::string getFirstName();
	std::string getLastName();
	bool getIsAdmin();
	std::string getPhone();
	std::string getAddress();
	std::string getRegisterDate();
	User static vectorOfStringsToModel(std::vector<std::string>);
	std::string modelToString();
};
