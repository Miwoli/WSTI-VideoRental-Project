#include "DB.hpp"

void DB::connect(std::string tableName) {
	openedDB.open(tableName + ".csv");
}

void DB::disconnect() {
	openedDB.close();
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
	std::cout << "AAA";
	std::cout << selectMovies().back();
	//int lastIndex = selectMovies().back().getId();
	/*connect("movies");
	if (openedDB.is_open()) {
		movie.setId(++lastIndex);
		openedDB << movie.modelToString() << std::endl;

		disconnect();
	} else {
		throw "Failed opening the file";
	}*/
}

