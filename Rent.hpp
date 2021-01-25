#pragma once

#include <string>
#include <vector>
#include "Model.hpp"
#include "Movie.hpp"
#include "User.hpp"
#include "Utils.hpp"

class Rent {
	int id;
	int movieId;
	std::string userLogin;
	std::string rentDate;
	std::string expReturnDate;
	std::string returnDate;

public:
	Rent();
	Rent(
		int newId,
		int newMovieId,
		std::string newUserLogin,
		std::string newRentDate,
		std::string newExpReturnDate,
		std::string newReturnDate
	);
	void setId(int);
	void setMovieId(int);
	void setUserLogin(std::string);
	void setRentDate(std::string);
	void setExpReturnDate(std::string);
	void setReturnDate(std::string);
	int getId();
	int getMovieId();
	std::string getUserLogin();
	std::string getRentDate();
	std::string getExpReturnDate();
	std::string getReturnDate();
	Rent static vectorOfStringsToModel(std::vector<std::string> row);
	std::string modelToString();
};
