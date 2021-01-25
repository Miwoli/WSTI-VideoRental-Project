#pragma once
#include <string>
#include <vector>
#include "Model.hpp"
#include "Utils.hpp"

class User: public Model {
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
	void setId(int);
	void setLogin(std::string);
	void setFirstName(std::string);
	void setLastName(std::string);
	void setPhone(std::string);
	void setAddress(std::string);
	void setRegisterDate(std::string);
	void setIsAdmin(bool);
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
