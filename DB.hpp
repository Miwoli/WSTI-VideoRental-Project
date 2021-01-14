#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/optional.hpp>
#include "Movie.hpp"
#include "User.hpp"
#include "Utils.hpp"
#include "Auth.hpp"

class DB {
	std::fstream openedDB;
	std::vector<Movie> movies;
	std::vector<User> selectUsers();
	void connect(std::string tableName, bool read);
	void disconnect();

public:
	static DB& getDB();
	std::vector<Movie> selectMovies();
	Movie getMovie(int id);
	boost::optional<User> getUser(std::string login);
	void createMovie(Movie movie);
	void createUser(User user, std::string passwordHash, std::string salt);
};

