#include "Show.hpp"

bool Show::sortByIdAsc(Movie lhs, Movie rhs) {
		return lhs.getId() < rhs.getId();
}

bool Show::sortByIdDesc(Movie lhs, Movie rhs) {
	return lhs.getId() > rhs.getId();
}

bool Show::sortByNameAsc(Movie lhs, Movie rhs) {
	return lhs.getName() < rhs.getName();
}

bool Show::sortByNameDesc(Movie lhs, Movie rhs) {
	return lhs.getName() > rhs.getName();
}

bool Show::sortByGenreAsc(Movie lhs, Movie rhs) {
	return lhs.getGenre() < rhs.getGenre();
}

bool Show::sortByGenreDesc(Movie lhs, Movie rhs) {
	return lhs.getGenre() > rhs.getGenre();
}

bool Show::sortByLengthAsc(Movie lhs, Movie rhs) {
	return lhs.getLength() < rhs.getLength();
}

bool Show::sortByLengthDesc(Movie lhs, Movie rhs) {
	return lhs.getLength() > rhs.getLength();
}

bool Show::sortByRatingAsc(Movie lhs, Movie rhs) {
	return lhs.getRating() < rhs.getRating();
}

bool Show::sortByRatingDesc(Movie lhs, Movie rhs) {
	return lhs.getRating() > rhs.getRating();
}

bool Show::sortByAddDateAsc(Movie lhs, Movie rhs) {
	std::vector<std::string> lhsVec = Utils::split(lhs.getAddDate(), "-");
	std::vector<std::string> rhsVec = Utils::split(rhs.getAddDate(), "-");

	if (std::stoi(lhsVec[2]) != std::stoi(rhsVec[2])) return std::stoi(lhsVec[2]) < std::stoi(rhsVec[2]);
	if (std::stoi(lhsVec[1]) != std::stoi(rhsVec[1])) return std::stoi(lhsVec[1]) < std::stoi(rhsVec[1]);
	return std::stoi(lhsVec[0]) < std::stoi(rhsVec[0]);
}

bool Show::sortByAddDateDesc(Movie lhs, Movie rhs) {
	std::vector<std::string> lhsVec = Utils::split(lhs.getAddDate(), "-");
	std::vector<std::string> rhsVec = Utils::split(rhs.getAddDate(), "-");

	if (std::stoi(lhsVec[2]) != std::stoi(rhsVec[2])) return std::stoi(lhsVec[2]) > std::stoi(rhsVec[2]);
	if (std::stoi(lhsVec[1]) != std::stoi(rhsVec[1])) return std::stoi(lhsVec[1]) > std::stoi(rhsVec[1]);
	return std::stoi(lhsVec[0]) > std::stoi(rhsVec[0]);
}

void Show::menuAllMovies() {
	char sortInput;

	int orderInput;
	SortOrder sortOrder;

	int paramInput;
	MovieParams sortParam;

	do {
		std::cout << "Do you want to apply sorting? [y/n]" << std::endl;
		std::cin >> sortInput;
	} while (sortInput != 'Y' && sortInput != 'y' && sortInput != 'N' && sortInput != 'n');

	if (sortInput == 'N' || sortInput == 'n') {
		allMovies();
	} else {
		bool correctInput;
		do {
			std::cout << std::endl << std::endl << "Select sort order:" << std::endl
				<< "1) Ascending" << std::endl
				<< "2) Descending" << std::endl;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			std::cin >> orderInput;
			if (orderInput != 1 && orderInput != 2) {
				correctInput = false;
			} else {
				if (orderInput == 1) sortOrder = SortOrder::ASC;
				if (orderInput == 2) sortOrder = SortOrder::DESC;
				correctInput = true;
			}
		} while (!correctInput && !std::cin);

		do {
			std::cout << std::endl << std::endl << "Select sort param:" << std::endl
				<< "1) ID" << std::endl
				<< "2) Name" << std::endl
				<< "3) Genre" << std::endl
				<< "4) Length" << std::endl
				<< "5) Rating" << std::endl
				<< "6) Add Date" << std::endl
				<< "7) Availibility" << std::endl;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> paramInput;
			correctInput = true;

			switch (paramInput) {
			case 1:
				sortParam = MovieParams::ID;
				break;
			case 2:
				sortParam = MovieParams::NAME;
				break;
			case 3:
				sortParam = MovieParams::GENRE;
				break;
			case 4:
				sortParam = MovieParams::LENGTH;
				break;
			case 5:
				sortParam = MovieParams::RATING;
				break;
			case 6:
				sortParam = MovieParams::ADDDATE;
				break;
			case 7:
				sortParam = MovieParams::AVAILABLE;
				break;
			default:
				correctInput = false;
				break;
			}
		} while (!correctInput || !std::cin);
		allMovies(sortOrder, sortParam);
	}
}

void Show::registerUser() {
	User user = User();
	if (!DB::getDB().areAnyUsers()) {
		std::cout << "WARNING: That's the first user. You'll become administrator!" << std::endl << std::endl;
		user.setIsAdmin(true);
	}

	std::string text;
	bool correctInput;

	do {
		correctInput = true;
		std::cout << "Login: ";
		std::cin >> text;
		if (DB::getDB().getUser(text)) {
			correctInput = false;
			std::cout << std::endl << "Login already used." << std::endl;
		}
	} while (!correctInput);

	user.setLogin(text);

	std::string password;
	std::string confirmPass;

	do {
		std::cout << "Password: ";
		std::cin >> password;

		std::cout << "Confirm password: ";
		std::cin >> confirmPass;

		if (password != confirmPass) std::cout << "Passwords don't match" << std::endl;
	} while (password != confirmPass);


	std::cout << "First name: ";
	std::getline(std::cin >> std::ws, text);
	user.setFirstName(text);

	std::cout << "Last name: ";
	std::getline(std::cin >> std::ws, text);
	user.setLastName(text);

	std::cout << "Phone: ";
	std::getline(std::cin >> std::ws, text);
	user.setPhone(text);

	std::cout << "Address: ";
	std::getline(std::cin >> std::ws, text);
	user.setAddress(text);

	Auth::registerUser(user, password);

	std::cout << "You account has been registered. You can login now using given credentials." << std::endl << std::endl;
}

void Show::loginUser() {
	std::string login;
	std::cout << "Login: ";
	std::cin >> login;

	std::string password;
	std::cout << "Password: ";
	std::cin >> password;

	if (Auth::login(login, password)) {
		std::cout << "Logged in succesfully. Hello, "
			<< Auth::getLoggedUser().value().getFirstName() << std::endl;
	} else {
		std::cout << "Incorrect login or password" << std::endl << std::endl;
	}
}

void Show::rentMovie() {
}

void Show::menuRentRegister() {
	Auth::getLoggedUser() ? rentMovie() : registerUser();
}

void Show::menuLoginLogout() {
	if (!Auth::getLoggedUser()) {
		loginUser();
	} else {
		Auth::logout();
		std::cout << "User logged out succesfully!" << std::endl << std::endl;
	}
}

bool Show::sortByAvailableAsc(Movie lhs, Movie rhs) {
	return lhs.getAvailable() < rhs.getAvailable();
}

bool Show::sortByAvailableDesc(Movie lhs, Movie rhs) {
	return lhs.getAvailable() > rhs.getAvailable();
}

void Show::mainMenu() {

	std::cout << "Welcome to Movie Rental Client. Created by: Michal 'Miwoli' Wolinski. All rights reserverd @2021"
		<< std::endl << "Press any key to start..." << std::endl << std::endl;
	int input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	do {
		std::cout << std::endl << "----- MOVIE RENTAL MAIN MENU -----" << std::endl;
		if (Auth::getLoggedUser()) {
			std::cout << "Welcome, " << Auth::getLoggedUser().value().getFirstName() << " " << Auth::getLoggedUser().value().getLastName() << "." << std::endl;
		}

		std::cout << std::endl << "Select option:" << std::endl
			<< "1) Show all movies" << std::endl
			<< "2) " << (Auth::getLoggedUser() ? "Logout" : "Login") << std::endl
			<< "3) " << (Auth::getLoggedUser() ? "Rent a movie" : "Register") << std::endl
			<< "9) Exit" << std::endl;

		std::cin.clear();
		std::cin >> input;
		std::cout << std::endl;

		switch (input) {
		case 1:
			menuAllMovies();
			break;
		case 2:
			menuLoginLogout();
			break;
		case 3:
			menuRentRegister();
			break;
		default:
			break;
		}

	} while (input != 9 || !std::cin);
}

void Show::movieDetails(int id) {
	Movie movie = DB::getDB().getMovie(id);
	std::string isAvailable = movie.getAvailable() ? "Available" : "Not available";

	std::cout << movie.getName() << std::endl << std::endl
		<< "Rate: " << movie.getRating() << " | " << movie.getLength() << "min. | " << isAvailable << std::endl << std::endl
		<< "Cast: " << Utils::implode(movie.getCast(), ", ") << std::endl << std::endl
		<< movie.getDescription() << std::endl << std::endl
		<< "Available since: " << movie.getAddDate() << std::endl << std::endl;
}

void Show::addMovie() {
	Movie movie = Movie();

	std::string text;
	int intiger;
	float decimal;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, text);
	movie.setName(text);
	std::cout << std::endl;

	std::cout << "Genre: ";
	std::getline(std::cin >> std::ws, text);
	movie.setGenre(text);
	std::cout << std::endl;

	std::cout << "Direcotr: ";
	std::getline(std::cin >> std::ws, text);
	movie.setDirector(text);
	std::cout << std::endl;

	std::cout << "Length: ";
	std::cin >> intiger;
	movie.setLength(intiger);
	std::cout << std::endl;

	std::cout << "Description: ";
	std::getline(std::cin >> std::ws, text);
	movie.setDescription(text);
	std::cout << std::endl;

	std::cout << "Rating (1-5, decimals with .): "; // TODO: Create class validator, validate inputs
	std::cin >> decimal;
	movie.setRating(decimal);
	std::cout << std::endl;

	std::cout << "Cast (separated with comma, with no spaces around commas): " << std::endl;
	std::getline(std::cin >> std::ws, text);
	movie.setCast(Utils::split(text, ","));
	std::cout << std::endl;

	movie.setAddDate(Utils::nowAsString());
	movie.setAvailable(true);

	DB::getDB().createMovie(movie);
}

void Show::allMovies(SortOrder order, MovieParams param) {
	std::vector<Movie> movies = DB::getDB().selectMovies();

	switch (param) {
	case MovieParams::ID:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByIdDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByIdAsc);
		}
		break;
	case MovieParams::NAME:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByNameDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByNameAsc);
		}
		break;
	case MovieParams::GENRE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByGenreDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByGenreAsc);
		}
		break;
	case MovieParams::LENGTH:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByLengthDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByLengthAsc);
		}
		break;
	case MovieParams::RATING:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByRatingDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByRatingAsc);
		}
		break;
	case MovieParams::ADDDATE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByAddDateDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByAddDateAsc);
		}
		break;
	case MovieParams::AVAILABLE:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByAvailableDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByAvailableAsc);
		}
		break;
	default:
		if (order == SortOrder::DESC) {
			std::sort(movies.begin(), movies.end(), &sortByIdDesc);
		} else {
			std::sort(movies.begin(), movies.end(), &sortByIdAsc);
		}
		break;
	}

	for (auto movie : movies) {
		std::string isAvailable = movie.getAvailable() ? "Available" : "Not available";
		std::cout << movie.getId() << ") "
			<< movie.getName() << " | "
			<< movie.getDirector() << " | "
			<< movie.getLength() << "min. | "
			<< movie.getGenre() << " | "
			<< movie.getRating() << " | "
			<< movie.getAddDate() << " | "
			<< isAvailable
			<< std::endl;
	}

	char seeDetails;
	do {
		std::cout << "Do you want to see more details [y/n]" << std::endl;
		std::cin >> seeDetails;
	} while (seeDetails != 'Y' && seeDetails != 'y' && seeDetails != 'N' && seeDetails != 'n');

	if (seeDetails == 'Y' || seeDetails == 'y') {

		int moviesAmount = movies.size();
		int movieId;

		do {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Type movie ID you wish to see details: ";
			std::cin >> movieId;

			if ((movieId > moviesAmount) || !std::cin) std::cout << "There's no movie with that ID" << std::endl;
		} while ((movieId > moviesAmount) || !std::cin);

		movieDetails(movieId);
	}
}
