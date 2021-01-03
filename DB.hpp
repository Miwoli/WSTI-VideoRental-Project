#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Movie.hpp"
#include "Utils.hpp"

class DB {
	std::fstream openedDB;
	std::vector<Movie> movies;
	void connect(std::string tableName);
	void disconnect();

public:
	static DB& getDB();
	std::vector<Movie> selectMovies();
	void createMovie(Movie movie);
};

