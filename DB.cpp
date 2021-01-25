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

		if (Utils::isEmptyFile(openedDB)) {
			disconnect();
			return movies;
		}

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

std::vector<Rent> DB::selectRents() {
	connect("rents");
	if (openedDB.is_open()) {
		std::vector<Rent> rents;

		if (Utils::isEmptyFile(openedDB)) {
			disconnect();
			return rents;
		}

		while (openedDB.good()) {
			std::string row;
			std::getline(openedDB, row);
			rents.push_back(Rent::vectorOfStringsToModel(Utils::split(row, ";")));
		}
		disconnect();
		return rents;
	} else {
		throw "Failed opening the file";
	}

	return std::vector<Rent>();
}

std::vector<Rent> DB::selectUserRents(std::string login) {
	std::vector<Rent> allRents = DB::getDB().selectRents();
	std::vector<Rent> userRents;

	std::copy_if(allRents.begin(), allRents.end(), std::back_inserter(userRents), [&login](Rent obj) { return obj.getUserLogin() == login; });

	return userRents;
}

std::optional<Movie> DB::getMovie(int id) {
	std::vector<Movie> movies = DB::getDB().selectMovies();
	auto it = std::find_if(movies.begin(), movies.end(), [&id](Movie obj) { return obj.getId() == id; });

	if (it == movies.end()) return std::nullopt;
	return *it;
}

std::optional<User> DB::getUser(std::string login) {
	std::vector<User> users = DB::getDB().selectUsers();
	auto it = std::find_if(users.begin(), users.end(), [&login](User obj) { return obj.getLogin() == login; });

	if (it == users.end()) return std::nullopt;
	return *it;
}

std::optional<Rent> DB::getRent(int id) {
	std::vector<Rent> rents = DB::getDB().selectRents();
	auto it = std::find_if(rents.begin(), rents.end(), [&id](Rent obj) { return obj.getId() == id; });

	if (it == rents.end()) return std::nullopt;
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
	int lastIndex = selectMovies().empty() ? 0 : selectMovies().back().getId();
	connect("movies", true);
	if (openedDB.is_open()) {
		if (lastIndex != 0) {
			openedDB << std::endl;
		}
		movie.setId(++lastIndex);
		openedDB << movie.modelToString();

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

void DB::createRent(Rent rent) {
	int lastIndex = selectRents().empty() ? 0 : selectRents().back().getId();
	connect("rents", true);
	if (openedDB.is_open()) {
		if (lastIndex != 0) {
			openedDB << std::endl;
		}
		rent.setId(++lastIndex);
		openedDB << rent.modelToString();

		disconnect();
	} else {
		throw "Failed opening the file";
	}
}

void DB::updateMovie(Movie updated) {
	std::vector<Movie> allMovies = selectMovies();

	allMovies[updated.getId() - 1] = updated;
	openedDB.open("movies.csv", std::fstream::trunc);
	int index = 0;

	for (auto movie : allMovies) {
		if (index != 0) {
			openedDB << std::endl;
		}
		openedDB << movie.modelToString();
	}
	disconnect();
}

bool DB::areAnyUsers() {
	connect("users");
	if (Utils::isEmptyFile(openedDB)) {
		disconnect();
		return false;
	}
	disconnect();
	return true;
}
