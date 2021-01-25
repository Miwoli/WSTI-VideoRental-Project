#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <random>
#include <openssl/ssl3.h>
#include <optional>
#include "DB.hpp"
#include "User.hpp"
#include "Utils.hpp"

class Auth {
	static std::optional<User> loggedUser;
	static std::string sha256(std::string str);
	static std::string generateSalt(int length);
	static std::string generateHash(std::string password, std::string salt);

public:
	static std::optional<User> getLoggedUser();
	static bool login(std::string login, std::string password);
	static void logout();
	static void registerUser(User newUser, std::string password);
	static bool isLoggedInAdmin();
};
