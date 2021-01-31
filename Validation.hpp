#pragma once
#include "Movie.hpp"
#include "User.hpp"
#include "Movie.hpp"
#include "DB.hpp"

class Validation {
public:
	static bool isMovieRent(Movie);
	static bool isLoginUsed(std::string);
	static bool isMovieNameUsed(std::string);
	static bool isDecimallBetween(double value, double lowerRange, double upperRange);
};

