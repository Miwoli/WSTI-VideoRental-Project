#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>
#include <openssl/ssl3.h>
#include "DB.hpp"
#include "User.hpp"
#include "Utils.hpp"

class Auth {
	static User loggedUser;
	static std::string sha256(std::string str);
	static std::string generateSalt(int length);
	static std::string generateHash(std::string password, std::string salt);

public:
	static bool login(std::string login, std::string password);
	static bool registerUser(User newUser, std::string password);
};

