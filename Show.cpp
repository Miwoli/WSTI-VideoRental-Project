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
	boost::posix_time::ptime lhsDate = boost::posix_time::from_iso_extended_string(lhs.getAddDate());
	boost::posix_time::ptime rhsDate = boost::posix_time::from_iso_extended_string(rhs.getAddDate());

	return lhsDate < rhsDate;
}

bool Show::sortByAddDateDesc(Movie lhs, Movie rhs) {
	boost::posix_time::ptime lhsDate = boost::posix_time::from_iso_extended_string(lhs.getAddDate());
	boost::posix_time::ptime rhsDate = boost::posix_time::from_iso_extended_string(rhs.getAddDate());

	return lhsDate > rhsDate;
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
		if (Validation::isLoginUsed(text)) {
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

void Show::rentMovie(User user, Movie movie) {
	char input;
	do {
		std::cin.clear();
		std::cout << "Do you want to rent this movie [y/n]" << std::endl;
		std::cin >> input;
	} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');

	if (input == 'y' || input == 'Y') {
		Rent rent = Rent();
		rent.setMovieId(movie.getId());
		rent.setUserLogin(user.getLogin());
		rent.setRentDate(Utils::dateAsString());
		rent.setExpReturnDate(Utils::dateAsString(3));

		movie.setAvailable(false);
		DB::getDB().updateMovie(movie);
		DB::getDB().createRent(rent);
	}
}

void Show::menuRentRegister() {
	Auth::getLoggedUser() ? userRents(Auth::getLoggedUser().value().getLogin()) : registerUser();
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
		<< std::endl << "Press enter to start..." << std::endl << std::endl;
	int response;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	do {
		if (Auth::isLoggedInAdmin()) {
			response = mainAdminMenu();
		} else {
			response = mainDefaultMenu();
		}
	} while (response != 9 || !std::cin);
}

void Show::movieDetails(int id) {
	if (!DB::getDB().getMovie(id)) return;
	Movie movie = DB::getDB().getMovie(id).value();
	std::string isAvailable = movie.getAvailable() ? "Available" : "Not available";

	std::cout << movie.getName() << std::endl << std::endl
		<< "Rate: " << movie.getRating() << " | " << movie.getLength() << "min. | " << isAvailable << std::endl << std::endl
		<< "Cast: " << Utils::implode(movie.getCast(), ", ") << std::endl << std::endl
		<< movie.getDescription() << std::endl << std::endl
		<< "Available since: " << movie.getAddDate() << std::endl << std::endl;

	if (Auth::getLoggedUser()
		&& movie.getAvailable()
		&& DB::getDB().userActiveRentsCount(Auth::getLoggedUser().value()) < 3
	) {
		rentMovie(Auth::getLoggedUser().value(), movie);
	}
}

void Show::addMovie() {
	Movie movie = Movie();

	std::string text;
	int intiger;
	float decimal;

	std::cout << "Name: ";
	std::getline(std::cin >> std::ws, text);
	while (Validation::isMovieNameUsed(text)) {
		std::cout << "A movie with that name already exists!" << std::endl;
		std::getline(std::cin >> std::ws, text);
	}
	movie.setName(text);
	std::cout << std::endl;

	std::cout << "Genre: ";
	std::getline(std::cin >> std::ws, text);
	movie.setGenre(text);
	std::cout << std::endl;

	std::cout << "Director: ";
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

	do {
		std::cout << "Rating (1-10, decimals with .): ";
		std::cin >> decimal;
	} while (!Validation::isDecimallBetween(decimal, 1, 10));
	movie.setRating(decimal);
	std::cout << std::endl;

	std::cout << "Cast (separated with comma, with no spaces around commas): " << std::endl;
	std::getline(std::cin >> std::ws, text);
	movie.setCast(Utils::split(text, ","));
	std::cout << std::endl;

	movie.setAddDate(Utils::dateAsString());
	movie.setAvailable(true);

	DB::getDB().createMovie(movie);
}

int Show::mainDefaultMenu() {
	std::cout << std::endl << "----- MOVIE RENTAL MAIN MENU -----" << std::endl;
	if (Auth::getLoggedUser()) {
		std::cout << "Welcome, " << Auth::getLoggedUser().value().getFirstName() << " " << Auth::getLoggedUser().value().getLastName() << "." << std::endl;
	}

	std::cout << std::endl << "Select option:" << std::endl
		<< "1) Show all movies" << std::endl
		<< "2) " << (Auth::getLoggedUser() ? "Logout" : "Login") << std::endl
		<< "3) " << (Auth::getLoggedUser() ? "Show my rents" : "Register") << std::endl
		<< "9) Exit" << std::endl;

	int input;
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

	return input;

}

int Show::mainAdminMenu() {
	std::cout << std::endl << "----- MOVIE RENTAL ADMIN PANEL -----" << std::endl;
	if (Auth::getLoggedUser()) {
		std::cout << "Welcome, " << Auth::getLoggedUser().value().getFirstName() << " " << Auth::getLoggedUser().value().getLastName() << "." << std::endl;
	}

	std::cout << std::endl << "Select option:" << std::endl
		<< "1) Show all movies" << std::endl
		<< "2) Logout" << std::endl
		<< "3) Show my rents" << std::endl
		<< "4) Add movie" << std::endl
		<< "5) Delete movie" << std::endl
		<< "9) Exit" << std::endl;

	int input;
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
	case 4:
		addMovie();
		break;
	case 5:
		removeMovie();
		break;
	default:
		break;
	}

	return input;
}

void Show::userRents(std::string login) {
	std::vector<Rent> rents = DB::getDB().selectUserRents(login);
	std::vector<Rent> returnedRents;
	std::vector<Rent> activeRents;
	std::copy_if(rents.begin(), rents.end(), std::back_inserter(returnedRents), [](Rent obj) { return obj.getReturnDate() != ""; });
	std::copy_if(rents.begin(), rents.end(), std::back_inserter(activeRents), [](Rent obj) { return obj.getReturnDate() == ""; });

	for (auto rent : returnedRents) {
		if (DB::getDB().getMovie(rent.getMovieId())) {
			std::cout << DB::getDB().getMovie(rent.getMovieId()).value().getName()
				<< " | Rent date: " << rent.getRentDate()
				<< " | Returned date: " << rent.getReturnDate() << std::endl;
		}
	}

	std::cout << "-------------------------------------------" << std::endl << std::endl;

	int i = 1;
	for (auto rent : activeRents) {
		if (DB::getDB().getMovie(rent.getMovieId())) {
			std::cout << i << ") " << DB::getDB().getMovie(rent.getMovieId()).value().getName()
				<< " | Rent date: " << rent.getRentDate()
				<< " | Return before: " << rent.getExpReturnDate() << std::endl;
			i++;
		}
	}

	if (rents.size() > 0) {
		char input;
		do {
			std::cin.clear();
			std::cout << "Do you want to return a movie? [y/n]" << std::endl;
			std::cin >> input;
		} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');
		if (input == 'Y' || input == 'y') {
			int movieId;
			do {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Type movie ID you wish to return: ";
				std::cin >> movieId;

				if ((movieId > rents.size() || movieId <= 0) || !std::cin) std::cout << "There's no movie with that ID" << std::endl;
			} while ((movieId > rents.size() || movieId <= 0) || !std::cin);

			movieId--;
			Movie updatedMovie = DB::getDB().getMovie(rents[movieId].getMovieId()).value();
			updatedMovie.setAvailable(true);
			DB::getDB().updateMovie(updatedMovie);
			Rent updatedRent = rents[movieId];
			updatedRent.setReturnDate(Utils::dateAsString());
			DB::getDB().updateRent(updatedRent);
		}
	}
}

void Show::removeMovie() {
	std::vector<Movie> movies = DB::getDB().selectMovies();

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


	int moviesAmount = movies.size();
	int movieId;

	do {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Type in movie ID you want to remove" << std::endl;

		std::cin >> movieId;

		if ((movieId > moviesAmount || movieId <= 0) || !std::cin) std::cout << "There's no movie with that ID" << std::endl;
	} while ((movieId > moviesAmount || movieId <= 0) || !std::cin);

	movieId--;

	if (Validation::isMovieRent(movies[movieId])) {
		std::cout << "Cannot delete movie, that is rent by somebody!" << std::endl;
	} else {
		DB::getDB().removeMovie(movies[movieId]);
	}
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

			if ((movieId > moviesAmount || movieId <=0) || !std::cin) std::cout << "There's no movie with that ID" << std::endl;
		} while ((movieId > moviesAmount || movieId <= 0) || !std::cin);

		movieDetails(movieId);
	}
}
