#include "Rent.hpp"

Rent::Rent() {
	setId(0);
	setRentDate("");
	setExpReturnDate("");
	setReturnDate("");
}

Rent::Rent(
	int newId,
	int newMovie,
	std::string newUser,
	std::string newRentDate,
	std::string newExpReturnDate,
	std::string newReturnDate
) {
	setId(newId);
	setMovieId(newMovie);
	setUserLogin(newUser);
	setRentDate(newRentDate);
	setExpReturnDate(newExpReturnDate);
	setReturnDate(newReturnDate);
}

void Rent::setId(int newId) {
	id = newId;
}

void Rent::setMovieId(int newMovie) {
	movieId = newMovie;
}

void Rent::setUserLogin(std::string newUser) {
	userLogin = newUser;
}

void Rent::setRentDate(std::string newDate) {
	rentDate = newDate;
}

void Rent::setExpReturnDate(std::string newDate) {
	expReturnDate = newDate;
}

void Rent::setReturnDate(std::string newDate) {
	returnDate = newDate;
}

int Rent::getId() {
	return id;
}

int Rent::getMovieId() {
	return movieId;
}

std::string Rent::getUserLogin() {
	return userLogin;
}

std::string Rent::getRentDate() {
	return rentDate;
}

std::string Rent::getExpReturnDate() {
	return expReturnDate;
}

std::string Rent::getReturnDate() {
	return returnDate;
}

Rent Rent::vectorOfStringsToModel(std::vector<std::string> data) {
	return Rent(
		std::stoi(data[0]),
		std::stoi(data[1]),
		data[2],
		data[3],
		data[4],
		data[5]
	);
}

std::string Rent::modelToString() {
	return std::to_string(getId()) + ';'
		+ std::to_string(getMovieId()) + ';'
		+ getUserLogin() + ';'
		+ getRentDate() + ';'
		+ getExpReturnDate() + ';'
		+ getReturnDate();
}
