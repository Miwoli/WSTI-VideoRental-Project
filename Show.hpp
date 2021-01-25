#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "DB.hpp"
#include "Movie.hpp"

enum class SortOrder {
	ASC,
	DESC
};

class Show {
	static bool sortByIdAsc(Movie lhs, Movie rhs);
	static bool sortByIdDesc(Movie lhs, Movie rhs);
	static bool sortByNameAsc(Movie lhs, Movie rhs);
	static bool sortByNameDesc(Movie lhs, Movie rhs);
	static bool sortByGenreAsc(Movie lhs, Movie rhs);
	static bool sortByGenreDesc(Movie lhs, Movie rhs);
	static bool sortByLengthAsc(Movie lhs, Movie rhs);
	static bool sortByLengthDesc(Movie lhs, Movie rhs);
	static bool sortByRatingAsc(Movie lhs, Movie rhs);
	static bool sortByRatingDesc(Movie lhs, Movie rhs);
	static bool sortByAddDateAsc(Movie lhs, Movie rhs);
	static bool sortByAddDateDesc(Movie lhs, Movie rhs);
	static bool sortByAvailableAsc(Movie lhs, Movie rhs);
	static bool sortByAvailableDesc(Movie lhs, Movie rhs);
	static void registerUser();
	static void loginUser();
	static void rentMovie(User, Movie);
	static void returnMovie(User);
	static void menuAllMovies();
	static void menuLoginLogout();
	static void menuRentRegister();
	static int mainDefaultMenu();
	static int mainAdminMenu();
	static void movieDetails(int id);
	static void userRents(std::string login);
	static void allMovies(SortOrder order = SortOrder::ASC, MovieParams param = MovieParams::ID);
	static void addMovie();

public:
	static void mainMenu();
};

