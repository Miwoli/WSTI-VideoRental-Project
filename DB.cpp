#include "DB.hpp"

std::vector<User> DB::selectUsers() {
	connect("users", false);
	if (openedDB.is_open()) {
		std::vector<User> users;

		while (openedDB.good()) {
			std::string row;
			std::getline(openedDB, row);
			users.push_back(User::vectorOfStringsToModel(Utils::split(row, ";")));
		}
		disconnect();
		return users;
	} else {
		throw "Failed opening the file";
	}

	return std::vector<User>();
}

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

Movie DB::getMovie(int id) {
	std::vector<Movie> movies = DB::getDB().selectMovies();
	auto it = std::find_if(movies.begin(), movies.end(), [&id](Movie obj) {return obj.getId() == id; });

	return *it;
}

boost::optional<User> DB::getUser(std::string login) {
	std::vector<User> users = DB::getDB().selectUsers();
	auto it = std::find_if(users.begin(), users.end(), [&login](User obj) {return obj.getLogin() == login;  });

	if (it == users.end()) return boost::none;
	return *it;
}

void DB::createMovie(Movie movie) {
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

void DB::createUser(User user, std::string passwordHash, std::string salt) {
	int lastIndex = selectUsers().back().getId();
	connect("users", true);
	if (openedDB.is_open()) {
		user.setId(++lastIndex);
		openedDB << std::endl << user.modelToString() << ";" << passwordHash << ";" << salt;

		disconnect();
	} else {
		throw "Failed opening the file";
	}
}

