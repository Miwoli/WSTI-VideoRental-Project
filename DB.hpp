#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <optional>
#include "Movie.hpp"
#include "User.hpp"
#include "Rent.hpp"
#include "Utils.hpp"
#include "Auth.hpp"

class DB {
	std::fstream openedDB;
	std::vector<User> selectUsers();
	void connect(std::string tableName, bool read);
	void disconnect();

public:
	static DB& getDB();
	std::vector<Movie> selectMovies();
	std::vector<Rent> selectRents();
	std::vector<Rent> selectUserRents(std::string login);
	std::optional<Movie> getMovie(int id);
	std::optional<User> getUser(std::string login);
	std::optional<Rent> getRent(int id);
	std::optional<std::vector<std::string>> getAuthData(std::string login);
	void createMovie(Movie);
	void createUser(User, std::string passwordHash, std::string salt);
	void createRent(Rent);
	void updateMovie(Movie);
	bool areAnyUsers();
};

