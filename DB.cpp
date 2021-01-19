#include "DB.hpp"

std::vector<User> DB::selectUsers() {
	connect("users", false);
	if (openedDB.is_open()) {
		std::vector<User> users;

		if (Utils::isEmptyFile(openedDB)) {
			disconnect();
			return users;
		};

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

void DB::connect(std::string tableName, bool write = false) {
	if (!write) {
		openedDB.open(tableName + ".csv");
	} else {
		openedDB.open(tableName + ".csv", std::fstream::app);
	}
}

void DB::disconnect() {
	openedDB.close();
	openedDB.seekg(0);
	openedDB.clear();
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

std::optional<User> DB::getUser(std::string login) {
	std::vector<User> users = DB::getDB().selectUsers();
	auto it = std::find_if(users.begin(), users.end(), [&login](User obj) {return obj.getLogin() == login;});

	if (it == users.end()) return std::nullopt;
	return *it;
}

std::optional<std::vector<std::string>> DB::getAuthData(std::string login) {
	if (!getUser(login)) {
		return std::nullopt;
	}

	int id = getUser(login).value().getId();

	connect("users");

	std::vector<std::string> result;
	std::string line;

	if (openedDB.is_open()) {
		for (int i = 1; std::getline(openedDB, line) && i <= id; i++) {
			if (i == id) {
				std::vector<std::string> temp = Utils::split(line, ";");
				result.push_back(temp.end()[-2]); // hash
				result.push_back(temp.end()[-1]); // salt
			}
		}

		disconnect();
		return result;
	} else {
		throw "Failed opening the file";
	}

	return std::nullopt;
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
	int lastIndex = selectUsers().empty() ? 0 : selectUsers().back().getId();
	connect("users", true);
	if (openedDB.is_open()) {
		if (lastIndex != 0) {
			openedDB << std::endl;
		}
		user.setId(++lastIndex);
		openedDB << user.modelToString() << ";" << passwordHash << ";" << salt;

		disconnect();
	} else {
		throw "Failed opening the file";
	}
}
