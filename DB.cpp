#include "DB.hpp"

void DB::connect(std::string tableName, bool read = false) {
	if (!read) {
		openedDB.open(tableName + ".csv");
	} else {
		openedDB.open(tableName + ".csv", std::fstream::app);
	}
}

void DB::disconnect() {
	openedDB.close();
	openedDB.clear();
	openedDB.seekg(0);
}

DB& DB::getDB() {
	static DB instance;
	return instance;
}

std::vector<Movie> DB::selectMovies() {
	connect("movies");
	if (openedDB.is_open()) {
		std::vector<Movie> movies;

		while (openedDB.good()) {
			std::string row;
			std::getline(openedDB, row);
			movies.push_back(Movie::vectorOfStringsToModel(Utils::split(row, ";")));
		}
		disconnect();
		return movies;
	} else {
		throw "Failed opening the file";
	}

	return std::vector<Movie>();
}

void DB::createMovie(Movie movie) {
	std::cout << selectMovies().back().getId();
	int lastIndex = selectMovies().back().getId();
	connect("movies", true);
	if (openedDB.is_open()) {
		movie.setId(++lastIndex);
		openedDB << std::endl << movie.modelToString();

		disconnect();
	} else {
		throw "Failed opening the file";
	}
}

