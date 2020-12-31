#pragma once
#include <vector>
#include <fstream>
#include "Movie.hpp"
#include "Utils.hpp"

class DB {
	DB();
	std::fstream openedDB;
	std::vector<Movie> movies;
	void connect(std::string tableName);
	void disconnect();

public:
	static DB& getDB();
	std::vector<Movie> selectMovies();
	std::vector<Movie> getMovies();
	void createMovie(Movie movie);
};

